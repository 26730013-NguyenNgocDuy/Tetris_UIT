#include "ColorRenderer.h"

#include <cstdio>
#include <string>

#include "Platform.h"

#ifdef _WIN32
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

ColorRenderer::ColorRenderer()
{
#ifdef _WIN32
    // UTF-8 để hiện đúng ký tự, và bật chế độ hiểu mã màu ANSI (Windows 10 trở lên)
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(out, &mode))
        SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    frame << "\033[?25l\033[2J\033[H";   // ẩn con trỏ, xoá màn hình, về góc trên
    flush();
}

ColorRenderer::~ColorRenderer()
{
    frame << "\033[0m\033[?25h";          // trả màu mặc định, hiện lại con trỏ
    flush();
}

void ColorRenderer::setColor(int textColor, int bgColor)
{
    // Đổi số màu kiểu Windows (0..15) sang mã màu ANSI
    static const int toAnsi[8] = {0, 4, 2, 6, 1, 5, 3, 7};
    int fg = (textColor & 8 ? 90 : 30) + toAnsi[textColor & 7];
    frame << "\033[" << fg << ";";
    if (bgColor == COLOR_BLACK)
        frame << "49";
    else
        frame << (bgColor & 8 ? 100 : 40) + toAnsi[bgColor & 7];
    frame << "m";
}

void ColorRenderer::resetColor()
{
    frame << "\033[0m";
}

void ColorRenderer::gotoxy(int x, int y)
{
    frame << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}

int ColorRenderer::getCharColor(char ch)
{
    switch (ch)
    {
    case 'I': return COLOR_CYAN;
    case 'O': return COLOR_YELLOW;
    case 'T': return COLOR_MAGENTA;
    case 'S': return COLOR_GREEN;
    case 'Z': return COLOR_RED;
    case 'J': return COLOR_BLUE;
    case 'L': return COLOR_DARK_YELLOW;
    case '#': return COLOR_DARK_CYAN;    // tường
    case '+': return COLOR_DARK_GRAY;    // bóng mờ
    default:  return COLOR_WHITE;
    }
}

void ColorRenderer::printCell(char ch, bool isPlayfield)
{
    if (ch == ' ')
    {
        if (isPlayfield)
        {
            // Ô trống trong sân chơi có chấm mờ làm lưới
            setColor(COLOR_DARK_GRAY);
            frame << " .";
            resetColor();
        }
        else
            frame << "  ";
        return;
    }

    setColor(getCharColor(ch));
    frame << (ch == '+' ? "::" : "[]");  // bóng mờ vẽ bằng '::', còn lại là khối vuông
    resetColor();
}

void ColorRenderer::flush()
{
    std::string text = frame.str();
    std::fwrite(text.data(), 1, text.size(), stdout);
    std::fflush(stdout);
    frame.str("");
    frame.clear();
}
