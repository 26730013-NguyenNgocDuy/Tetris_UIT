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
    canHold = false;
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
}

DropSpeedController speedController;

// Hàm vẽ toàn bộ UI chuẩn báo cáo 3.3
void draw()
{
    ColorRenderer::gotoxy(0, 0);

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

    // Dựng 20 dòng hoàn chỉnh kết hợp HUD bên trái và bên phải
    for (int row = 0; row < H; row++)
    {
        // ================= KHUNG BÊN TRÁI =================
        // Dòng 0: Header GIỮ
        if (row == 0)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "+------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 1)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_YELLOW);
            cout << "GIU (C)    ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row >= 2 && row <= 5)
        {
            // Hiển thị khối giữ trong 4 dòng
            int pi = row - 2;
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
            for (int pj = 0; pj < 4; pj++)
            {
                char ch = (holdBlock != -1) ? Blocks::shapeAt(holdBlock, pi, pj) : ' ';
                ColorRenderer::printCell(ch);
            }
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 6)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "+------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 10)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "+------------+  ";
            ColorRenderer::resetColor();
        }
        else if (row == 11)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "DIEM       ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row == 12)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_WHITE);
            cout << setw(10) << left << speedController.getScore();
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 13)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "CAP DO     ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row == 14)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_YELLOW);
            cout << setw(10) << left << speedController.getLevel();
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 15)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "SO HANG    ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row == 16)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_GREEN);
            cout << setw(10) << left << speedController.getTotalLinesCleared();
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 17)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_CYAN);
            cout << "NHIP ROI   ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|  ";
            ColorRenderer::resetColor();
        }
        else if (row == 18)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "| ";
            ColorRenderer::setColor(COLOR_MAGENTA);
            string speedStr = to_string(speedController.getDropInterval()) + "ms";
            if (speedController.getComboStreak() > 1)
            {
                speedStr += " x" + to_string(speedController.getComboStreak());
            }
            cout << setw(10) << left << speedStr;
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << " |  ";
            ColorRenderer::resetColor();
        }
        else if (row == 19)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "+------------+  ";
            ColorRenderer::resetColor();
        }
        else
        {
            cout << "                ";
        }

        // ================= SÂN CHƠI CHÍNH (BÀN CỜ) =================
        for (int col = 0; col < W; col++)
        {
            ColorRenderer::printCell(displayBoard[row][col]);
        }

        // ================= KHUNG BÊN PHẢI (TIẾP THEO) =================
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
            cout << "TIEP THEO  ";
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "|";
            ColorRenderer::resetColor();
        }
        else if (row >= 2 && row <= 17)
        {
            // Hiển thị 4 khối tiếp theo trong hàng đợi (mỗi khối chiếm 4 dòng)
            int blockIdx = (row - 2) / 4;
            int blockRow = (row - 2) % 4;
            int pId = nextQueue[blockIdx];

            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  |  ";
            ColorRenderer::resetColor();
            for (int pj = 0; pj < 4; pj++)
            {
                char ch = Blocks::shapeAt(pId, blockRow, pj);
                ColorRenderer::printCell(ch);
            }
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  |";
            ColorRenderer::resetColor();
        }
        else if (row == 18)
        {
            ColorRenderer::setColor(COLOR_DARK_CYAN);
            cout << "  +------------+";
            ColorRenderer::resetColor();
        }
        else
        {
            cout << "                ";
        }

        cout << "\n";
    }

    // Dòng hướng dẫn phím bấm phía dưới
    ColorRenderer::setColor(COLOR_DARK_GRAY);
    cout << "\n[A/D]: Trai/Phai  [W]: Xoay  [S]: Roi nhanh  [SPACE]: Tha ngay  [C]: Giu  [Q]: Thoat\n";
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
            Sleep(120);
        }
    }

    return clearedCount;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    ColorRenderer::setupConsole();

    board.reset();
    initQueue();
    spawn(-1);

    while (1)
    {
        board.erase(*current);

        if (kbhit())
        {
            char c = getch();

            if (c == 'a' && canMove(-1, 0))
                current->move(-1, 0);

            if (c == 'd' && canMove(1, 0))
                current->move(1, 0);

            if (c == 's')
            {
                if (canMove(0, 1))
                {
                    current->move(0, 1);
                    speedController.addDropScore(1);
                }
            }

            if (c == 'w')
                rotate();

            if (c == 'c' || c == 'C')
                holdPiece();

            if (c == ' ') // Hard drop
            {
                int dropDist = 0;
                while (canMove(0, 1))
                {
                    current->move(0, 1);
                    dropDist++;
                }
                speedController.addDropScore(dropDist * 2);
            }

            if (c == 'q')
                break;
        }

        if (canMove(0, 1))
        {
            current->move(0, 1);
        }
        else
        {
            // Block đã chạm đáy
            board.place(*current);

            // Xóa line
            int cleared = removeLine();

            // Tăng tốc độ nếu có line bị xóa, hoặc reset combo nếu không ăn line
            if (cleared > 0)
                speedController.onLinesCleared(cleared);
            else
                speedController.resetCombo();

            // Spawn block mới
            spawn(-1);

            // Kiểm tra GameOver
            if (!canMove(0, 0))
            {
                draw();
                ColorRenderer::gotoxy(18, 10);
                ColorRenderer::setColor(COLOR_RED, COLOR_WHITE);
                cout << "   GAME OVER!   ";
                ColorRenderer::resetColor();
                break;
            }
        }

        board.place(*current);

        draw();

        Sleep(speedController.getDropInterval());
    }

    ColorRenderer::gotoxy(0, 23);
    cout << "\nNhan phim bat ky de thoat...";
    getch();

    return 0;
}