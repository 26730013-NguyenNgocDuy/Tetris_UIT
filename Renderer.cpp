#include "Renderer.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "ColorRenderer.h"

using namespace std;

// Kích thước lấy từ lớp Board
const int H = Board::ROWS;
const int W = Board::COLS;

Renderer::Renderer()
{
    ColorRenderer::setupConsole();
}

void Renderer::showMessage(int x, int y, const string &text, int textColor, int bgColor)
{
    ColorRenderer::gotoxy(x, y);
    ColorRenderer::setColor(textColor, bgColor);
    cout << text;
    ColorRenderer::resetColor();
}

void Renderer::showPauseModal()
{
    ColorRenderer::gotoxy(20, 11);
    ColorRenderer::setColor(COLOR_BLACK, COLOR_YELLOW);
    cout << "  [!] TAM DUNG (PAUSED)  ";
    ColorRenderer::gotoxy(20, 12);
    cout << "   Nhan phim P tiep tuc  ";
    ColorRenderer::resetColor();
    
}

void Renderer::showGameOverModal(int score)
{
    ColorRenderer::gotoxy(20, 10);
    ColorRenderer::setColor(COLOR_WHITE, COLOR_RED);
    cout << "     GAME OVER      ";
    ColorRenderer::gotoxy(20, 11);
    ColorRenderer::setColor(COLOR_BLACK, COLOR_WHITE);
    cout << "  Diem so: " << setw(10) << left << score << " ";
    ColorRenderer::gotoxy(20, 12);
    cout << "  [R]: Choi lai         ";
    ColorRenderer::gotoxy(20, 13);
    cout << "  [Q]: Thoat game       ";
    ColorRenderer::resetColor();
    
}

void Renderer::draw(const Board &board, const Blocks &current, int ghostY,
                    int holdBlock, const int nextQueue[], const DropSpeedController &stats)
{
    ColorRenderer::gotoxy(0, 0);

    // Banner Header phong cách UIT Pro Max
    ColorRenderer::setColor(COLOR_CYAN);
    cout << "  ============================================================\n";
    cout << "    🎮 TETRIS PRO MAX 🎮 | UIT SS004 - NHOM HIDDEN GEM\n";
    cout << "  ============================================================\n";
    ColorRenderer::resetColor();

    char displayBoard[H][W];
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            displayBoard[r][c] = board.at(r, c);

    // Vẽ ghost piece (nếu chưa chạm đất)
    if (ghostY > current.getY())
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int c = current.getX() + j;
                if (current.isFilled(i, j) && ghostY + i < H - 1 && c > 0 && c < W - 1)
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
            int r = current.getY() + i, c = current.getX() + j;
            if (current.isFilled(i, j) && r >= 0 && r < H && c >= 0 && c < W)
            {
                displayBoard[r][c] = current.at(i, j);
            }
        }
    }

    int currentHighScore = ColorRenderer::getHighScore();
    if (stats.getScore() > currentHighScore)
        currentHighScore = stats.getScore();

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
            cout << setw(10) << left << stats.getLevel();
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
            cout << setw(10) << left << stats.getTotalLinesCleared();
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
            cout << setw(10) << left << stats.getScore();
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
            string spd = to_string(stats.getDropInterval()) + "ms";
            if (stats.getComboStreak() > 1)
                spd += " x" + to_string(stats.getComboStreak());
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

    // Dòng hướng dẫn phím bấm phía dưới (ngắn gọn, chống tràn buffer)
    ColorRenderer::setColor(COLOR_DARK_GRAY);
    cout << "\n  [< / >] hoac [A/D]: Trai/Phai   [^/W]: Xoay    [v/S]: Xuong\033[K\n";
    cout << "  [SPACE]: Tha ngay  [C]: Giu khoi [P]: Tam dung  [Q]: Thoat\033[K\n";
    ColorRenderer::resetColor();
}
