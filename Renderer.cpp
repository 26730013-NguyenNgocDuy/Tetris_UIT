#include "Renderer.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "ColorRenderer.h"

using namespace std;

// Kich thuoc lay tu lop Board
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

void Renderer::draw(const Board &board, const Tetromino &current, int ghostY,
                    int holdBlock, const int nextQueue[], const DropSpeedController &stats)
{
    ColorRenderer::gotoxy(0, 0);

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
                char ch = (holdBlock != -1) ? Tetromino::shapeAt(holdBlock, pi, pj) : ' ';
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
            cout << setw(10) << left << stats.getScore();
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
            cout << setw(10) << left << stats.getLevel();
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
            cout << setw(10) << left << stats.getTotalLinesCleared();
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
            string speedStr = to_string(stats.getDropInterval()) + "ms";
            if (stats.getComboStreak() > 1)
            {
                speedStr += " x" + to_string(stats.getComboStreak());
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
                char ch = Tetromino::shapeAt(pId, blockRow, pj);
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
    cout << "\n[A/D]: Trai/Phai  [W]: Xoay  [S]: Roi nhanh  [SPACE]: Tha ngay  [C]: Giu"
            "  [P]: Tam dung  [R]: Choi lai  [Q]: Thoat\n";
    ColorRenderer::resetColor();
}
