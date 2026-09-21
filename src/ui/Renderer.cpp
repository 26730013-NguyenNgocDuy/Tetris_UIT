#include "Renderer.h"

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

namespace
{
    // Kích thước sân chơi lấy từ lớp Board
    const int H = Board::ROWS;
    const int W = Board::COLS;

    // Bố cục hai bảng thông tin, tính theo dòng của sân chơi.
    // Khung khối (GIỮ bên trái, TIẾP THEO bên phải): viền, tiêu đề, 4 dòng hình, viền
    const int PIECE_BOX_TOP = 0;
    const int PIECE_ROWS = 4;
    // Khung số (LEVEL / SCORE rồi LINES / HIGH SCORE): viền, tiêu đề, giá trị, viền
    const int FIRST_STAT_TOP = 8;
    const int SECOND_STAT_TOP = 13;
    const int STAT_BOX_HEIGHT = 4;
    // Dòng tốc độ rơi ở cuối bảng phải, ngay dưới là viền
    const int SPEED_ROW = 18;

    // Vị trí hai khung hiện đè lên sân chơi
    const int MODAL_X = 20;
    const int PAUSE_Y = 11;
    const int GAME_OVER_Y = 10;

    // Chiều rộng chữ trong khung
    const int TITLE_WIDTH = 11;
    const int VALUE_WIDTH = 10;

    // Dòng 'row' là dòng thứ mấy của khung bắt đầu ở 'top' (cao 'height' dòng)
    enum BoxLine { OUTSIDE, BORDER, TITLE, CONTENT };

    BoxLine lineOfBox(int row, int top, int height)
    {
        if (row == top || row == top + height - 1)
            return BORDER;
        if (row == top + 1)
            return TITLE;
        if (row > top + 1 && row < top + height - 1)
            return CONTENT;
        return OUTSIDE;
    }

    const int PIECE_BOX_HEIGHT = PIECE_ROWS + 3;
}

// ------------------------------------------------------------ các loại dòng của khung
void Renderer::panelBorder(bool leftSide)
{
    console.setColor(COLOR_DARK_CYAN);
    console.out() << "  +------------+" << (leftSide ? "  " : "");
    console.resetColor();
}

void Renderer::panelTitle(const char *title, int color, bool leftSide)
{
    console.setColor(COLOR_DARK_CYAN);
    console.out() << "  | ";
    console.setColor(color);
    console.out() << setw(TITLE_WIDTH) << left << title;
    console.setColor(COLOR_DARK_CYAN);
    console.out() << "|" << (leftSide ? "  " : "");
    console.resetColor();
}

void Renderer::panelValue(const string &value, int color, bool leftSide)
{
    console.setColor(COLOR_DARK_CYAN);
    console.out() << "  | ";
    console.setColor(color);
    console.out() << setw(VALUE_WIDTH) << left << value;
    console.setColor(COLOR_DARK_CYAN);
    console.out() << " |" << (leftSide ? "  " : "");
    console.resetColor();
}

void Renderer::panelPieceRow(int blockType, int pieceRow, bool leftSide)
{
    console.setColor(COLOR_DARK_CYAN);
    console.out() << "  |  ";
    console.resetColor();

    // Loại khối -1 (chưa giữ gì) cho ra toàn ô trống
    for (int col = 0; col < Blocks::SIZE; col++)
        console.printCell(Blocks::shapeAt(blockType, pieceRow, col), false);

    console.setColor(COLOR_DARK_CYAN);
    console.out() << "  |" << (leftSide ? "  " : "");
    console.resetColor();
}

void Renderer::panelEmpty(bool leftSide)
{
    console.out() << "                " << (leftSide ? "  " : "");
}

// ------------------------------------------------------------ hai bảng thông tin
static string toText(int number)
{
    ostringstream s;
    s << number;
    return s.str();
}

void Renderer::drawLeftPanel(int row, int holdBlock, const DropSpeedController &stats)
{
    const bool LEFT = true;

    switch (lineOfBox(row, PIECE_BOX_TOP, PIECE_BOX_HEIGHT))
    {
    case BORDER:  panelBorder(LEFT); return;
    case TITLE:   panelTitle("HOLD (C)", COLOR_YELLOW, LEFT); return;
    case CONTENT: panelPieceRow(holdBlock, row - PIECE_BOX_TOP - 2, LEFT); return;
    default: break;
    }

    switch (lineOfBox(row, FIRST_STAT_TOP, STAT_BOX_HEIGHT))
    {
    case BORDER:  panelBorder(LEFT); return;
    case TITLE:   panelTitle("LEVEL", COLOR_CYAN, LEFT); return;
    case CONTENT: panelValue(toText(stats.getLevel()), COLOR_YELLOW, LEFT); return;
    default: break;
    }

    switch (lineOfBox(row, SECOND_STAT_TOP, STAT_BOX_HEIGHT))
    {
    case BORDER:  panelBorder(LEFT); return;
    case TITLE:   panelTitle("LINES", COLOR_CYAN, LEFT); return;
    case CONTENT: panelValue(toText(stats.getTotalLinesCleared()), COLOR_GREEN, LEFT); return;
    default: break;
    }

    panelEmpty(LEFT);
}

void Renderer::drawRightPanel(int row, int nextBlock, int bestScore, const DropSpeedController &stats)
{
    const bool RIGHT = false;

    switch (lineOfBox(row, PIECE_BOX_TOP, PIECE_BOX_HEIGHT))
    {
    case BORDER:  panelBorder(RIGHT); return;
    case TITLE:   panelTitle("NEXT", COLOR_YELLOW, RIGHT); return;
    case CONTENT: panelPieceRow(nextBlock, row - PIECE_BOX_TOP - 2, RIGHT); return;
    default: break;
    }

    switch (lineOfBox(row, FIRST_STAT_TOP, STAT_BOX_HEIGHT))
    {
    case BORDER:  panelBorder(RIGHT); return;
    case TITLE:   panelTitle("SCORE", COLOR_CYAN, RIGHT); return;
    case CONTENT: panelValue(toText(stats.getScore()), COLOR_WHITE, RIGHT); return;
    default: break;
    }

    switch (lineOfBox(row, SECOND_STAT_TOP, STAT_BOX_HEIGHT))
    {
    case BORDER:  panelBorder(RIGHT); return;
    case TITLE:   panelTitle("HIGH SCORE", COLOR_CYAN, RIGHT); return;
    case CONTENT: panelValue(toText(bestScore), COLOR_YELLOW, RIGHT); return;
    default: break;
    }

    if (row == SPEED_ROW)
    {
        // Tốc độ rơi hiện tại, kèm số combo nếu đang ăn hàng liên tiếp
        string speed = toText(stats.getDropInterval()) + "ms";
        if (stats.getComboStreak() > 1)
            speed += " x" + toText(stats.getComboStreak());
        panelValue(speed, COLOR_MAGENTA, RIGHT);
        return;
    }
    if (row == SPEED_ROW + 1)
    {
        panelBorder(RIGHT);
        return;
    }

    panelEmpty(RIGHT);
}

// ------------------------------------------------------------ vẽ cả màn hình
void Renderer::draw(const Board &board, const Blocks &current, int ghostY, int holdBlock,
                    const int nextQueue[], const DropSpeedController &stats, int bestScore)
{
    ostream &out = console.out();
    console.gotoxy(0, 0);

    // Banner phía trên
    console.setColor(COLOR_CYAN);
    out << "  ============================================================\n";
    out << "    🎮 TETRIS PRO MAX 🎮 | UIT SS004 - NHOM HIDDEN GEM\n";
    out << "  ============================================================\n";
    console.resetColor();

    // Chép bàn cờ ra một bản tạm để vẽ thêm bóng mờ và khối đang rơi lên trên
    char displayBoard[H][W];
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            displayBoard[r][c] = board.at(r, c);

    // Bóng mờ: chỗ khối sẽ rơi tới (chỉ vẽ khi khối chưa chạm đất)
    if (ghostY > current.getY())
    {
        for (int i = 0; i < Blocks::SIZE; i++)
            for (int j = 0; j < Blocks::SIZE; j++)
            {
                int c = current.getX() + j;
                if (current.isFilled(i, j) && ghostY + i < H - 1 && c > 0 && c < W - 1
                    && displayBoard[ghostY + i][c] == ' ')
                    displayBoard[ghostY + i][c] = '+';
            }
    }

    // Khối đang rơi
    for (int i = 0; i < Blocks::SIZE; i++)
        for (int j = 0; j < Blocks::SIZE; j++)
        {
            int r = current.getY() + i, c = current.getX() + j;
            if (current.isFilled(i, j) && r >= 0 && r < H && c >= 0 && c < W)
                displayBoard[r][c] = current.at(i, j);
        }

    // Điểm cao hiển thị không bao giờ thấp hơn điểm đang chơi
    if (stats.getScore() > bestScore)
        bestScore = stats.getScore();

    // Mỗi dòng: bảng trái, sân chơi, bảng phải
    for (int row = 0; row < H; row++)
    {
        drawLeftPanel(row, holdBlock, stats);

        for (int col = 0; col < W; col++)
        {
            bool isPlayfield = (col > 0 && col < W - 1);
            console.printCell(displayBoard[row][col], isPlayfield);
        }

        drawRightPanel(row, nextQueue[0], bestScore, stats);
        out << "\033[K\n";   // xoá phần thừa của dòng cũ bên phải
    }

    // Dòng hướng dẫn phím bấm phía dưới
    console.setColor(COLOR_DARK_GRAY);
    out << "\n  [< / >] hoac [A/D]: Trai/Phai   [^/W]: Xoay    [v/S]: Xuong\033[K\n";
    out << "  [SPACE]: Tha ngay  [C]: Giu khoi [P]: Tam dung  [Q]: Thoat\033[K\n";
    console.resetColor();

    console.flush();   // cả khung hình ra màn hình trong một lần ghi
}

void Renderer::showMessage(int x, int y, const string &text, int textColor, int bgColor)
{
    console.gotoxy(x, y);
    console.setColor(textColor, bgColor);
    console.out() << text;
    console.resetColor();
    console.flush();
}

void Renderer::showPauseModal()
{
    console.setColor(COLOR_BLACK, COLOR_YELLOW);
    console.gotoxy(MODAL_X, PAUSE_Y);
    console.out() << "  [!] TAM DUNG (PAUSED)  ";
    console.gotoxy(MODAL_X, PAUSE_Y + 1);
    console.out() << "   Nhan phim P tiep tuc  ";
    console.resetColor();
    console.flush();
}

void Renderer::showGameOverModal(int score)
{
    console.gotoxy(MODAL_X, GAME_OVER_Y);
    console.setColor(COLOR_WHITE, COLOR_RED);
    console.out() << "     GAME OVER      ";
    console.gotoxy(MODAL_X, GAME_OVER_Y + 1);
    console.setColor(COLOR_BLACK, COLOR_WHITE);
    console.out() << "  Diem so: " << setw(VALUE_WIDTH) << left << score << " ";
    console.gotoxy(MODAL_X, GAME_OVER_Y + 2);
    console.out() << "  [R]: Choi lai         ";
    console.gotoxy(MODAL_X, GAME_OVER_Y + 3);
    console.out() << "  [Q]: Thoat game       ";
    console.resetColor();
    console.flush();
}
