#ifndef COLOR_RENDERER_H
#define COLOR_RENDERER_H

#include <iostream>
#include <windows.h>

/**
 * @brief Bảng màu Console chuẩn Windows từ repo cũ TetrisGame (UIT - SS004)
 */
enum ConsoleColor {
    COLOR_BLACK         = 0,
    COLOR_DARK_BLUE     = 1,
    COLOR_DARK_GREEN    = 2,
    COLOR_DARK_CYAN     = 3,
    COLOR_DARK_RED      = 4,
    COLOR_DARK_MAGENTA  = 5,
    COLOR_DARK_YELLOW   = 6,
    COLOR_GRAY          = 7,
    COLOR_DARK_GRAY     = 8,
    COLOR_BLUE          = 9,
    COLOR_GREEN         = 10,
    COLOR_CYAN          = 11,
    COLOR_RED           = 12,
    COLOR_MAGENTA       = 13,
    COLOR_YELLOW        = 14,
    COLOR_WHITE         = 15
};

/**
 * @brief Class OOP ColorRenderer - Quản lý màu sắc và render mượt mà (Flicker-Free)
 */
class ColorRenderer {
public:
    static void setColor(int textColor, int bgColor = 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
    }

    static void resetColor() {
        setColor(COLOR_WHITE, COLOR_BLACK);
    }

    static void gotoxy(int x, int y) {
        COORD coord;
        coord.X = static_cast<SHORT>(x);
        coord.Y = static_cast<SHORT>(y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    static void setupConsole() {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
        system("cls");
    }

    /**
     * @brief Lấy mã màu chuẩn cho từng loại khối Tetrimino từ repo cũ
     */
    static int getCharColor(char ch) {
        switch (ch) {
            case 'I': return COLOR_CYAN;         // Cyan - Khối thẳng
            case 'O': return COLOR_YELLOW;       // Vàng - Khối vuông
            case 'T': return COLOR_MAGENTA;      // Hồng tím - Khối chữ T
            case 'S': return COLOR_GREEN;        // Xanh lá - Khối chữ S
            case 'Z': return COLOR_RED;          // Đỏ - Khối chữ Z
            case 'J': return COLOR_BLUE;         // Xanh dương - Khối chữ J
            case 'L': return COLOR_DARK_YELLOW;  // Cam/Vàng sẫm - Khối chữ L
            case '#': return COLOR_DARK_CYAN;    // Xanh lơ viền tường
            default:  return COLOR_WHITE;
        }
    }

    /**
     * @brief In một ô trên bàn cờ với màu sắc và tỷ lệ vuông vức chuẩn
     * @param ch Ký tự đại diện ('I', 'O', '#', ' ', v.v.)
     * @param squareMode true: in 2 ký tự ("[]", "##", "  ") để vuông vức; false: in 1 ký tự
     */
    static void printCell(char ch, bool squareMode = true) {
        if (ch == ' ') {
            if (squareMode) std::cout << "  ";
            else std::cout << ' ';
            return;
        }

        int color = getCharColor(ch);
        setColor(color);

        if (squareMode) {
            if (ch == '#') {
                std::cout << "##";
            } else {
                std::cout << "[]";
            }
        } else {
            std::cout << ch;
        }

        resetColor();
    }
};

#endif // COLOR_RENDERER_H
