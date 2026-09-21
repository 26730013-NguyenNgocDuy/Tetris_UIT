#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include "Platform.h"
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

// Định nghĩa 7 loại khối Tetrimino chuẩn quốc tế (4x4)
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

    // Wall kick: thử các độ lệch 0, -1, 1, -2, 2
    int kick[5] = {0, -1, 1, -2, 2};
    for (int k = 0; k < 5; k++)
    {
        if (canMove(kick[k], 0))
        {
            x += kick[k];
            return;
        }
    }

    // Không thể xoay -> trả lại trạng thái cũ
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
        {
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
        }
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

void spawn(int blockId = -1)
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
        spawn(-1);
    }
    else
    {
        int temp = holdBlock;
        holdBlock = b;
        spawn(temp);
    }
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
                char ch = (holdBlock != -1) ? blocks[holdBlock][pi][pj] : ' ';
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
                char ch = blocks[pId][pi][pj];
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
    cout << "\n  [A/D]: Trai/Phai   [W]: Xoay       [S]: Roi nhanh\033[K\n";
    cout << "  [SPACE]: Tha ngay  [C]: Giu khoi   [P]: Tam dung   [Q]: Thoat\033[K\n";
    ColorRenderer::resetColor();
}

int removeLine()
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

            // Kéo các dòng phía trên xuống
            for (int ii = i; ii > 1; ii--)
                for (int jj = 1; jj < W - 1; jj++)
                    board[ii][jj] = board[ii - 1][jj];

            // Xóa dòng trên cùng
            for (int jj = 1; jj < W - 1; jj++)
                board[1][jj] = ' ';

            // Kiểm tra lại dòng hiện tại
            i++;

            draw();
            Sleep(80);
        }
    }

    return clearedCount;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    ColorRenderer::setupConsole();

restart_game_session:
    initBoard();
    initQueue();
    spawn(-1);
    speedController = DropSpeedController();
    isGamePaused = false;

    const int TICK_MS = 25; // 40 FPS, cực kỳ nhạy phím (<25ms response time)
    int dropTimer = 0;

    // Gắn khối ban đầu vào bàn cờ và vẽ frame khởi động
    block2Board();
    draw();

    while (1)
    {
        bool moved = false;

        // 1. Đọc phím liên tục không nghẽn luồng (Non-blocking input)
        while (kbhit())
        {
            char c = getch();

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

            boardDelBlock();

            if ((c == 'a' || c == 'A') && canMove(-1, 0))
            {
                x--;
                moved = true;
            }
            else if ((c == 'd' || c == 'D') && canMove(1, 0))
            {
                x++;
                moved = true;
            }
            else if (c == 's' || c == 'S') // Soft drop
            {
                if (canMove(0, 1))
                {
                    y++;
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
                    y++;
                }
                moved = true;
                dropTimer = speedController.getDropInterval();
            }
            else if (c == 'q' || c == 'Q')
            {
                block2Board();
                goto game_quit;
            }

            block2Board();
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
            boardDelBlock();

            if (canMove(0, 1))
            {
                y++;
                moved = true;
                block2Board();
            }
            else
            {
                // Khối đã chạm đáy -> Khóa vào bàn cờ
                block2Board();

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

                block2Board();
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
    ColorRenderer::gotoxy(0, 26);
    cout << "\nCam on ban da trai nghiem Tetris Pro Max!\n";

    return 0;
}