#ifndef COLOR_RENDERER_H
#define COLOR_RENDERER_H

#include <iostream>
#include <string>
#include "Platform.h"

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
#ifdef _WIN32
    // Lấy handle một lần thay vì gọi GetStdHandle ở mỗi lần đổi màu
    static HANDLE outHandle() {
        static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        return h;
    }

    // Màu đang áp dụng; -1 nghĩa là chưa xác định
    static int &currentAttribute() {
        static int attr = -1;
        return attr;
    }

    static void setColor(int textColor, int bgColor = COLOR_BLACK) {
        int attr = (bgColor << 4) | textColor;

        // Bỏ qua nếu màu không đổi: mỗi lần gọi API là một lần chuyển vào kernel
        if (attr == currentAttribute())
            return;

        // Console API có hiệu lực ngay, còn cout thì có bộ đệm.
        // Phải đẩy hết ký tự của màu cũ ra trước khi đổi màu.
        std::cout << std::flush;
        SetConsoleTextAttribute(outHandle(), attr);
        currentAttribute() = attr;
    }

    static void resetColor() {
        setColor(COLOR_WHITE, COLOR_BLACK);
    }

    static void gotoxy(int x, int y) {
        // Tương tự setColor: đẩy bộ đệm ra trước khi dời con trỏ
        std::cout << std::flush;
        COORD coord;
        coord.X = static_cast<SHORT>(x);
        coord.Y = static_cast<SHORT>(y);
        SetConsoleCursorPosition(outHandle(), coord);
    }

    static void setupConsole() {
        HANDLE consoleHandle = outHandle();
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
        system("cls");
        currentAttribute() = -1;
    }
#else
    // macOS / Linux: dùng mã màu ANSI thay cho Windows Console API
    static void setColor(int textColor, int bgColor = COLOR_BLACK) {
        // Thứ tự bit màu của Windows (B,G,R) khác ANSI (R,G,B)
        static const int winToAnsi[8] = {0, 4, 2, 6, 1, 5, 3, 7};
        int fg = (textColor & 8 ? 90 : 30) + winToAnsi[textColor & 7];
        std::cout << "\033[" << fg;
        if (bgColor == COLOR_BLACK)
            std::cout << ";49";  // Giữ nền mặc định của terminal
        else
            std::cout << ";" << (bgColor & 8 ? 100 : 40) + winToAnsi[bgColor & 7];
        std::cout << "m";
    }

    static void resetColor() {
        std::cout << "\033[0m";
    }

    static void gotoxy(int x, int y) {
        std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
    }

    static void setupConsole() {
        // Xóa màn hình và ẩn con trỏ
        std::cout << "\033[2J\033[H\033[?25l" << std::flush;
    }
#endif

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
