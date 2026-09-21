#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include "Platform.h"
#include "DropSpeedController.h"
#include "ColorRenderer.h"
#include "Blocks.h"
#include "BlockTypes.h"
#include "Board.h"
#include "Bag7.h"

using namespace std;

// Kích thước lấy từ hằng số của lớp Board, không dùng #define nữa
const int H = Board::ROWS;
const int W = Board::COLS;

// Bàn cờ chính 20x12 (với 2 cột viền và 10 cột trong sân chơi chuẩn Tetris)
Board board;

// Khối đang rơi. Dùng con trỏ lớp cha để gọi được hàm xoay riêng của từng loại
// khối (đa hình). Con trỏ này do main sở hữu nên phải tự xoá khi thay khối.
Blocks *current = 0;
int holdBlock = -1;
bool canHold = true;
int nextQueue[4];

// Nguồn phát khối: mỗi túi có đủ 7 loại nên không bị trùng liên tục như rand() % 7
Bag7 bag;

bool canMove(int dx, int dy, const Blocks &piece)
{
    return board.canPlace(piece, dx, dy);
}

bool canMove(int dx, int dy)
{
    return board.canPlace(*current, dx, dy);
}

void rotate()
{
    // ĐA HÌNH: clone() trả về bản sao đúng loại khối, rotate() xoay theo kiểu
    // riêng của loại đó. Chỗ này không cần biết đang cầm khối gì.
    Blocks *turned = current->clone();
    turned->rotate();

    // Wall kick: thử các độ lệch 0, -1, 1, -2, 2
    int kick[5] = {0, -1, 1, -2, 2};
    for (int k = 0; k < 5; k++)
    {
        if (canMove(kick[k], 0, *turned))
        {
            turned->move(kick[k], 0);
            delete current;      // nhận bản đã xoay, bỏ bản cũ
            current = turned;
            return;
        }
    }

    delete turned;               // không đặt vừa chỗ nào thì bỏ bản sao
}

int getGhostY()
{
    int gy = current->getY();
    while (canMove(0, gy - current->getY() + 1))
    {
        gy++;
    }
    return gy;
}

void initQueue()
{
    for (int i = 0; i < 4; i++)
    {
        nextQueue[i] = bag.next();
    }
}

void spawn(int blockId = -1)
{
    int type;
    if (blockId == -1)
    {
        type = nextQueue[0];
        for (int i = 0; i < 3; i++)
        {
            nextQueue[i] = nextQueue[i + 1];
        }
        nextQueue[3] = bag.next();
    }
    else
    {
        type = blockId;
    }

    // Tạo đúng lớp con tương ứng với loại khối
    delete current;
    current = createBlock(type, 4, 0);
    canHold = true;
}

void holdPiece()
{
    if (!canHold) return;
    board.erase(*current);
    if (holdBlock == -1)
    {
        holdBlock = current->getType();
        spawn(-1);
    }
    else
    {
        int temp = holdBlock;
        holdBlock = current->getType();
        spawn(temp);
    }

    // Đặt sau spawn(), vì spawn() bật lại canHold cho khối mới. Nếu đặt trước
    // thì mỗi khối giữ được bao nhiêu lần cũng được, sai luật.
    canHold = false;
}

DropSpeedController speedController;
bool isGamePaused = false;

// Hàm vẽ toàn bộ UI đẳng cấp chuẩn Tetris Web Pro Max
void draw(bool showPauseModal = false, bool showGameOverModal = false)
{
    ColorRenderer::gotoxy(0, 0);

    // Banner Header phong cách UIT Pro Max
    ColorRenderer::setColor(COLOR_CYAN);
    cout << "  ============================================================\n";
    cout << "    🎮 TETRIS PRO MAX 🎮 | UIT SS004 - NHOM HIDDEN GEM\n";
    cout << "  ============================================================\n";
    ColorRenderer::resetColor();

    // Tính toán bóng khối rơi (Ghost piece)
    int ghostY = getGhostY();

    char displayBoard[H][W];
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            displayBoard[r][c] = board.at(r, c);

    // Vẽ ghost piece (nếu chưa chạm đất)
    if (ghostY > current->getY())
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int c = current->getX() + j;
                if (current->isFilled(i, j) && ghostY + i < H - 1 && c > 0 && c < W - 1)
                {
                    if (displayBoard[ghostY + i][c] == ' ')
                        displayBoard[ghostY + i][c] = '+';
                }
            }
        }
    }

    // Vẽ khối hiện tại
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int r = current->getY() + i, c = current->getX() + j;
            if (current->isFilled(i, j) && r >= 0 && r < H && c >= 0 && c < W)
            {
                displayBoard[r][c] = current->at(i, j);
            }
        }
    }

    int currentHighScore = ColorRenderer::getHighScore();
    if (speedController.getScore() > currentHighScore)
        currentHighScore = speedController.getScore();

    // Dựng 20 dòng hoàn chỉnh kết hợp HUD bên trái và bên phải (Theo bản Web)
    for (int row = 0; row < H; row++)
    {
        // ================= PANEL BÊN TRÁI (HOLD, LEVEL, LINES) =================
        if (row == 0)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 1)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_YELLOW);
            cout << "HOLD (C)   ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row >= 2 && row <= 5)
        {
            // Hiển thị khối giữ trong 4 dòng
            int pi = row - 2;
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  |  ";
            ColorRenderer::resetColor();
            for (int pj = 0; pj < 4; pj++)
            {
                char ch = (holdBlock != -1) ? Blocks::shapeAt(holdBlock, pi, pj) : ' ';
                ColorRenderer::printCell(ch, false);
            }
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 6)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 8)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 9)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "LEVEL      ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row == 10)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_YELLOW);
            cout << setw(10) << left << speedController.getLevel();
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 11)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 13)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 14)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "LINES      ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row == 15)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_GREEN);
            cout << setw(10) << left << speedController.getTotalLinesCleared();
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 16)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+  ";
            ColorRenderer::resetColor();
        }
        else
        {
            cout << "                  ";
        }

        // ================= SÂN CHƠI CHÍNH (BÀN CỜ 10x20 + 2 VIỀN) =================
        for (int col = 0; col < W; col++)
        {
            bool isPlayfield = (col > 0 && col < W - 1);
            ColorRenderer::printCell(displayBoard[row][col], isPlayfield);
        }

        // ================= PANEL BÊN PHẢI (NEXT, SCORE, HIGH SCORE, SPEED) =================
        if (row == 0)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else if (row == 1)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_YELLOW);
            cout << "NEXT       ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|";
            ColorRenderer::resetColor();
        }
        else if (row >= 2 && row <= 5)
        {
            // Hiển thị khối tiếp theo trong hàng đợi
            int pi = row - 2;
            int pId = nextQueue[0];
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  |  ";
            ColorRenderer::resetColor();
            for (int pj = 0; pj < 4; pj++)
            {
                char ch = Blocks::shapeAt(pId, pi, pj);
                ColorRenderer::printCell(ch, false);
            }
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  |";
            ColorRenderer::resetColor();
        }
        else if (row == 6)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else if (row == 8)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else if (row == 9)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "SCORE      ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|";
            ColorRenderer::resetColor();
        }
        else if (row == 10)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_WHITE);
            cout << setw(10) << left << speedController.getScore();
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |";
            ColorRenderer::resetColor();
        }
        else if (row == 11)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else if (row == 13)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else if (row == 14)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "HIGH SCORE ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|";
            ColorRenderer::resetColor();
        }
        else if (row == 15)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_YELLOW);
            cout << setw(10) << left << currentHighScore;
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |";
            ColorRenderer::resetColor();
        }
        else if (row == 16)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else if (row == 18)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  | ";
            ColorRenderer::setColor(COLOR_MAGENTA);
            string spd = to_string(speedController.getDropInterval()) + "ms";
            if (speedController.getComboStreak() > 1)
                spd += " x" + to_string(speedController.getComboStreak());
            cout << setw(10) << left << spd;
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |";
            ColorRenderer::resetColor();
        }
        else if (row == 19)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else
        {
            cout << "                ";
        }

        cout << "\033[K\n";
    }

    // Modal TẠM DỪNG (P)
    if (showPauseModal)
    {
        ColorRenderer::gotoxy(20, 11);
        ColorRenderer::setColor(COLOR_BLACK, COLOR_YELLOW);
        cout << "  [!] TAM DUNG (PAUSED)  ";
        ColorRenderer::gotoxy(20, 12);
        cout << "   Nhan phim P tiep tuc  ";
        ColorRenderer::resetColor();
    }

    // Modal GAME OVER
    if (showGameOverModal)
    {
        ColorRenderer::gotoxy(20, 10);
        ColorRenderer::setColor(COLOR_WHITE, COLOR_RED);
        cout << "     GAME OVER      ";
        ColorRenderer::gotoxy(20, 11);
        ColorRenderer::setColor(COLOR_BLACK, COLOR_WHITE);
        cout << "  Diem so: " << setw(10) << left << speedController.getScore() << " ";
        ColorRenderer::gotoxy(20, 12);
        cout << "  [R]: Choi lai         ";
        ColorRenderer::gotoxy(20, 13);
        cout << "  [Q]: Thoat game       ";
        ColorRenderer::resetColor();
    }

    // Dòng hướng dẫn phím bấm phía dưới (ngắn gọn, chống tràn buffer)
    ColorRenderer::setColor(COLOR_DARK_GRAY);
    cout << "\n  [< / >] hoac [A/D]: Trai/Phai   [^/W]: Xoay    [v/S]: Xuong\033[K\n";
    cout << "  [SPACE]: Tha ngay  [C]: Giu khoi [P]: Tam dung  [Q]: Thoat\033[K\n";
    ColorRenderer::resetColor();
}

int removeLine()
{
    int clearedCount = 0;

    for (int i = H - 2; i > 0; i--)
    {
        if (board.isRowFull(i))
        {
            clearedCount++;
            board.removeRow(i);

            // Kiểm tra lại dòng hiện tại vì dòng trên vừa rơi xuống
            i++;

            draw();
            Sleep(80);
        }
    }

    return clearedCount;
}

// Hàm đọc phím thông minh hỗ trợ cả ký tự thường (A/D/W/S) lẫn phím Mũi Tên (Arrow Keys)
int readInputKey()
{
    int c = getch();
#ifdef _WIN32
    if (c == 0 || c == 224 || c == -32)
    {
        int ext = getch();
        if (ext == 72) return 'w';      // Mũi tên Lên -> Xoay khối
        if (ext == 80) return 's';      // Mũi tên Xuống -> Rơi nhanh (Soft drop)
        if (ext == 75) return 'a';      // Mũi tên Trái -> Di chuyển sang trái
        if (ext == 77) return 'd';      // Mũi tên Phải -> Di chuyển sang phải
    }
#else
    if (c == 27) // ANSI Escape Sequence cho phím mũi tên trên Linux/macOS
    {
        if (kbhit() && getch() == '[')
        {
            int ext = getch();
            if (ext == 'A') return 'w'; // Up
            if (ext == 'B') return 's'; // Down
            if (ext == 'D') return 'a'; // Left
            if (ext == 'C') return 'd'; // Right
        }
    }
#endif
    return c;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    ColorRenderer::setupConsole();

restart_game_session:
    board.reset();
    initQueue();
    spawn(-1);
    speedController = DropSpeedController();
    isGamePaused = false;

    const int TICK_MS = 25; // 40 FPS, cực kỳ nhạy phím (<25ms response time)
    int dropTimer = 0;

    // Gắn khối ban đầu vào bàn cờ và vẽ frame khởi động
    board.place(*current);
    draw();

    while (1)
    {
        bool moved = false;

        // 1. Đọc phím liên tục không nghẽn luồng (Non-blocking input)
        while (kbhit())
        {
            int c = readInputKey();

            if (c == 'p' || c == 'P')
            {
                isGamePaused = !isGamePaused;
                draw(isGamePaused, false);
                continue;
            }

            if (isGamePaused)
            {
                if (c == 'q' || c == 'Q')
                    goto game_quit;
                continue;
            }

            board.erase(*current);

            if ((c == 'a' || c == 'A') && canMove(-1, 0))
            {
                current->move(-1, 0);
                moved = true;
            }
            else if ((c == 'd' || c == 'D') && canMove(1, 0))
            {
                current->move(1, 0);
                moved = true;
            }
            else if (c == 's' || c == 'S') // Soft drop
            {
                if (canMove(0, 1))
                {
                    current->move(0, 1);
                    dropTimer = 0;
                    moved = true;
                }
            }
            else if (c == 'w' || c == 'W')
            {
                rotate();
                moved = true;
            }
            else if (c == 'c' || c == 'C')
            {
                holdPiece();
                moved = true;
            }
            else if (c == ' ') // Hard drop
            {
                while (canMove(0, 1))
                {
                    current->move(0, 1);
                }
                moved = true;
                dropTimer = speedController.getDropInterval();
            }
            else if (c == 'q' || c == 'Q')
            {
                board.place(*current);
                goto game_quit;
            }

            board.place(*current);
        }

        if (isGamePaused)
        {
            Sleep(TICK_MS);
            continue;
        }

        // 2. Xử lý rơi tự nhiên theo bộ điều tốc
        dropTimer += TICK_MS;
        if (dropTimer >= speedController.getDropInterval())
        {
            dropTimer = 0;
            board.erase(*current);

            if (canMove(0, 1))
            {
                current->move(0, 1);
                moved = true;
                board.place(*current);
            }
            else
            {
                // Khối đã chạm đáy -> Khóa vào bàn cờ
                board.place(*current);

                // Xóa hàng đầy nếu có
                int cleared = removeLine();

                // Cập nhật gia tốc rơi và combo streak
                if (cleared > 0)
                    speedController.onLinesCleared(cleared);
                else
                    speedController.resetCombo();

                // Sinh khối mới
                spawn(-1);

                // Kiểm tra thua cuộc (Game Over)
                if (!canMove(0, 0))
                {
                    ColorRenderer::setHighScore(speedController.getScore());
                    draw(false, true); // Hiện Modal Game Over

                    // Vòng lặp chờ bấm R để chơi lại hoặc Q để thoát
                    while (1)
                    {
                        char endKey = getch();
                        if (endKey == 'r' || endKey == 'R')
                        {
                            goto restart_game_session;
                        }
                        if (endKey == 'q' || endKey == 'Q')
                        {
                            goto game_quit;
                        }
                    }
                }

                board.place(*current);
                moved = true;
            }
        }

        // 3. Chỉ vẽ lại khi có dịch chuyển (tối ưu hóa I/O console, mượt mà 100%)
        if (moved)
        {
            draw();
        }

        Sleep(TICK_MS);
    }

game_quit:
    ColorRenderer::setHighScore(speedController.getScore());
    delete current;
    current = 0;
    ColorRenderer::gotoxy(0, 26);
    cout << "\nCam on ban da trai nghiem Tetris Pro Max!\n";

    return 0;
}