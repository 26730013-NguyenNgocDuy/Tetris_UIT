#ifndef COLOR_RENDERER_H
#define COLOR_RENDERER_H

#include <iostream>
#include <windows.h>
#include <string>

/**
 * @brief Bảng màu Console chuẩn Windows
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
 * @brief Class OOP ColorRenderer - Quản lý màu sắc và render giao diện chuẩn hình mẫu báo cáo 3.3
 * 
 * Thành phần giao diện:
 * 1: Khung bàn chơi chính (10x20 tiêu chuẩn)
 * 2: Khối gạch đang rơi (Active Tetrimino)
 * 3: Ghost Piece (Bóng khối rơi dự đoán vị trí tiếp đất)
 * 4: Khung "GIỮ" (Hold Piece)
 * 5: Khung "TIẾP THEO" (Next Pieces)
 * 6: Khung thông số "ĐIỂM", "CẤP ĐỘ", "SỐ HÀNG"
 */
class ColorRenderer {
public:
    static void setColor(int textColor, int bgColor = COLOR_BLACK) {
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
     * @brief Màu sắc chuẩn của từng khối Tetrimino theo quy chuẩn Tetris quốc tế
     */
    static int getCharColor(char ch) {
        switch (ch) {
            case 'I': return COLOR_CYAN;         // Cyan - Khối dài I
            case 'O': return COLOR_YELLOW;       // Vàng - Khối vuông O
            case 'T': return COLOR_MAGENTA;      // Tím hồng - Khối chữ T
            case 'S': return COLOR_GREEN;        // Xanh lá - Khối chữ S
            case 'Z': return COLOR_RED;          // Đỏ - Khối chữ Z
            case 'J': return COLOR_BLUE;         // Xanh dương - Khối chữ J
            case 'L': return COLOR_DARK_YELLOW;  // Cam/Vàng sẫm - Khối chữ L
            case '#': return COLOR_DARK_CYAN;    // Viền tường
            case '+': return COLOR_DARK_GRAY;    // Ghost piece (bóng dự đoán tiếp đất)
            default:  return COLOR_WHITE;
        }
    }

    /**
     * @brief In 1 ô tế bào với màu sắc và tỷ lệ vuông vức 1:1
     */
    static void printCell(char ch) {
        if (ch == ' ') {
            std::cout << "  ";
            return;
        }

        if (ch == '+') {
            // Ghost piece: đường nét thanh dự đoán vị trí rơi
            setColor(COLOR_DARK_GRAY);
            std::cout << "::";
            resetColor();
            return;
        }

        int color = getCharColor(ch);
        setColor(color);

        if (ch == '#') {
            std::cout << "##";
        } else {
            std::cout << "[]";
        }

        resetColor();
    }
};

#endif // COLOR_RENDERER_H
