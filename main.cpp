#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <vector>
#include <iomanip>
#include "DropSpeedController.h"
#include "ColorRenderer.h"

using namespace std;

#define H 20
#define W 12

// Bàn cờ chính 20x12 (với 2 cột viền và 10 cột trong sân chơi chuẩn Tetris)
char board[H][W] = {};

int x, y, b;
int holdBlock = -1;
bool canHold = true;
int nextQueue[4];

// Định nghĩa 7 loại khối Tetrimino (4x4)
char blocks[7][4][4] = {
    // 0: Khối I
    {{' ', ' ', ' ', ' '},
     {'I', 'I', 'I', 'I'},
     {' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    // 1: Khối O
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    // 2: Khối T
    {{' ', ' ', ' ', ' '},
     {' ', 'T', ' ', ' '},
     {'T', 'T', 'T', ' '},
     {' ', ' ', ' ', ' '}},
    // 3: Khối S
    {{' ', ' ', ' ', ' '},
     {' ', 'S', 'S', ' '},
     {'S', 'S', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    // 4: Khối Z
    {{' ', ' ', ' ', ' '},
     {'Z', 'Z', ' ', ' '},
     {' ', 'Z', 'Z', ' '},
     {' ', ' ', ' ', ' '}},
    // 5: Khối J
    {{' ', ' ', ' ', ' '},
     {'J', ' ', ' ', ' '},
     {'J', 'J', 'J', ' '},
     {' ', ' ', ' ', ' '}},
    // 6: Khối L
    {{' ', ' ', ' ', ' '},
     {' ', ' ', 'L', ' '},
     {'L', 'L', 'L', ' '},
     {' ', ' ', ' ', ' '}}
};

char cur[4][4];

bool canMove(int dx, int dy, char piece[4][4], int px, int py)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (piece[i][j] != ' ')
            {
                int xt = px + j + dx;
                int yt = py + i + dy;
                if (xt < 1 || xt >= W - 1 || yt >= H - 1)
                    return false;
                if (yt >= 0 && board[yt][xt] != ' ')
                    return false;
            }
        }
    }
    return true;
}

bool canMove(int dx, int dy)
{
    return canMove(dx, dy, cur, x, y);
}

void rotate()
{
    char old[4][4], tmp[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            old[i][j] = cur[i][j];
            tmp[i][j] = cur[3 - j][i];
        }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = tmp[i][j];

    // Wall kick
    int kick[5] = {0, -1, 1, -2, 2};
    for (int k = 0; k < 5; k++)
    {
        if (canMove(kick[k], 0))
        {
            x += kick[k];
            return;
        }
    }

    // Nếu không xoay được thì khôi phục hình dạng cũ
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = old[i][j];
}

void block2Board()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
                if (y + i >= 0 && y + i < H && x + j >= 0 && x + j < W)
                    board[y + i][x + j] = cur[i][j];
}

void boardDelBlock()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
                if (y + i >= 0 && y + i < H && x + j >= 0 && x + j < W)
                    board[y + i][x + j] = ' ';
}

void initBoard()
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}

int getGhostY()
{
    int gy = y;
    while (canMove(0, gy - y + 1))
    {
        gy++;
    }
    return gy;
}

void initQueue()
{
    for (int i = 0; i < 4; i++)
    {
        nextQueue[i] = rand() % 7;
    }
}

void spawnPiece(int blockId = -1)
{
    if (blockId == -1)
    {
        b = nextQueue[0];
        for (int i = 0; i < 3; i++)
        {
            nextQueue[i] = nextQueue[i + 1];
        }
        nextQueue[3] = rand() % 7;
    }
    else
    {
        b = blockId;
    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = blocks[b][i][j];

    x = 4;
    y = 0;
    canHold = true;
}

void holdPiece()
{
    if (!canHold) return;
    canHold = false;
    boardDelBlock();
    if (holdBlock == -1)
    {
        holdBlock = b;
        spawnPiece(-1);
    }
    else
    {
        int temp = holdBlock;
        holdBlock = b;
        spawnPiece(temp);
    }
}

int removeLine(void (*drawCallback)())
{
    int clearedCount = 0;
    for (int i = H - 2; i > 0; i--)
    {
        int j;
        for (j = 1; j < W - 1; j++)
            if (board[i][j] == ' ')
                break;
        if (j == W - 1)
        {
            clearedCount++;
            for (int ii = i; ii > 1; ii--)
                for (int jj = 1; jj < W - 1; jj++)
                    board[ii][jj] = board[ii - 1][jj];
            for (int jj = 1; jj < W - 1; jj++)
                board[1][jj] = ' ';
            i++;
            if (drawCallback)
            {
                drawCallback();
                Sleep(120);
            }
        }
    }
    return clearedCount;
}

DropSpeedController speedController;

// Hàm vẽ toàn bộ UI chuẩn báo cáo 3.3
void drawUI()
{
    ColorRenderer::gotoxy(0, 0);

    // Tính toán bóng khối rơi (Ghost piece)
    int ghostY = getGhostY();

    char displayBoard[H][W];
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            displayBoard[r][c] = board[r][c];

    // Vẽ ghost piece (nếu chưa chạm đất)
    if (ghostY > y)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (cur[i][j] != ' ' && ghostY + i < H - 1 && x + j > 0 && x + j < W - 1)
                {
                    if (displayBoard[ghostY + i][x + j] == ' ')
                        displayBoard[ghostY + i][x + j] = '+';
                }
            }
        }
    }

    // Vẽ khối hiện tại
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (cur[i][j] != ' ' && y + i >= 0 && y + i < H && x + j >= 0 && x + j < W)
            {
                displayBoard[y + i][x + j] = cur[i][j];
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
                char ch = (holdBlock != -1) ? blocks[holdBlock][pi][pj] : ' ';
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
                char ch = blocks[pId][blockRow][pj];
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

void triggerDrawCallback()
{
    drawUI();
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    ColorRenderer::setupConsole();
    initBoard();
    initQueue();
    spawnPiece(-1);

    while (1)
    {
        if (kbhit())
        {
            char c = getch();
            if (c == 'a' && canMove(-1, 0))
                x--;
            else if (c == 'd' && canMove(1, 0))
                x++;
            else if (c == 's')
            {
                if (canMove(0, 1))
                {
                    y++;
                    speedController.addDropScore(1);
                }
            }
            else if (c == 'w')
            {
                rotate();
            }
            else if (c == 'c' || c == 'C')
            {
                holdPiece();
            }
            else if (c == ' ') // Hard drop
            {
                int dropDist = 0;
                while (canMove(0, 1))
                {
                    y++;
                    dropDist++;
                }
                speedController.addDropScore(dropDist * 2);
            }
            else if (c == 'q')
            {
                break;
            }
        }

        if (canMove(0, 1))
        {
            y++;
        }
        else
        {
            block2Board();
            int cleared = removeLine(triggerDrawCallback);
            if (cleared > 0)
            {
                speedController.onLinesCleared(cleared);
            }

            spawnPiece(-1);

            // Kiểm tra GameOver
            if (!canMove(0, 0))
            {
                drawUI();
                ColorRenderer::gotoxy(18, 10);
                ColorRenderer::setColor(COLOR_RED, COLOR_WHITE);
                cout << "   GAME OVER!   ";
                ColorRenderer::resetColor();
                break;
            }
        }

        drawUI();
        Sleep(speedController.getDropInterval());
    }

    ColorRenderer::gotoxy(0, 23);
    cout << "\nNhan phim bat ky de thoat...";
    getch();
    return 0;
}