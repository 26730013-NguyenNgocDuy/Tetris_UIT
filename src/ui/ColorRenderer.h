#ifndef COLOR_RENDERER_H
#define COLOR_RENDERER_H

#include <iostream>
#include <string>
#include <fstream>
#include "Platform.h"

/**
 * @brief Bảng màu Console chuẩn Windows và ANSI
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
 * @brief Class OOP ColorRenderer - Quản lý màu sắc và giao diện chuẩn Tetris Web Pro
 */
class ColorRenderer {
public:
#ifdef _WIN32
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
        // Thiết lập mã UTF-8 cho Windows Console để hiển thị khối và viền mượt mà
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);

        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
        system("cls");
    }
#else
    // macOS / Linux: dùng mã màu ANSI thay cho Windows Console API
    static void setColor(int textColor, int bgColor = COLOR_BLACK) {
        static const int winToAnsi[8] = {0, 4, 2, 6, 1, 5, 3, 7};
        int fg = (textColor & 8 ? 90 : 30) + winToAnsi[textColor & 7];
        std::cout << "\033[" << fg;
        if (bgColor == COLOR_BLACK)
            std::cout << ";49";
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
        std::cout << "\033[2J\033[H\033[?25l" << std::flush;
    }
#endif

    /**
     * @brief Màu sắc chuẩn của từng khối Tetrimino theo quy chuẩn Tetris Guidelines (giống Web)
     */
    static int getCharColor(char ch) {
        switch (ch) {
            case 'I': return COLOR_CYAN;         // I: Cyan (#06b6d4)
            case 'O': return COLOR_YELLOW;       // O: Yellow (#eab308)
            case 'T': return COLOR_MAGENTA;      // T: Purple/Magenta (#a855f7)
            case 'S': return COLOR_GREEN;        // S: Green (#22c55e)
            case 'Z': return COLOR_RED;          // Z: Red (#ef4444)
            case 'J': return COLOR_BLUE;         // J: Blue (#3b82f6)
            case 'L': return COLOR_DARK_YELLOW;  // L: Orange (#f97316)
            case '#': return COLOR_DARK_CYAN;    // Viền tường
            case '+': return COLOR_DARK_GRAY;    // Ghost piece (bóng mờ)
            default:  return COLOR_WHITE;
        }
    }

    /**
     * @brief In 1 ô tế bào với tỷ lệ 1:1 chuẩn xác theo giao diện Web
     * @param ch Ký tự đại diện cho ô (I, O, T, S, Z, J, L, #, +, ' ')
     * @param isPlayfield True nếu ô nằm trong lòng sân chơi (để vẽ lưới chấm mờ)
     */
    static void printCell(char ch, bool isPlayfield = false) {
        if (ch == ' ') {
            if (isPlayfield) {
                // Lưới sân chơi chấm mờ như đường grid của canvas Web
                setColor(COLOR_DARK_GRAY);
                std::cout << " .";
                resetColor();
            } else {
                std::cout << "  ";
            }
            return;
        }

        if (ch == '+') {
            // Ghost piece: đổ bóng dạng lưới thanh lịch dự đoán vị trí rơi
            setColor(COLOR_DARK_GRAY);
            std::cout << "::";
            resetColor();
            return;
        }

        if (ch == '#') {
            setColor(COLOR_DARK_CYAN);
            std::cout << "[]";
            resetColor();
            return;
        }

        int color = getCharColor(ch);
        setColor(color);
        // Khối vuông rực rỡ vuông vức 1:1
        std::cout << "[]";
        resetColor();
    }

    /**
     * @brief Quản lý High Score (Đọc và ghi file highscore.dat giống localStorage của Web)
     */
    static int getHighScore() {
        std::ifstream file("highscore.dat");
        int hs = 0;
        if (file >> hs) {
            return hs;
        }
        return 0;
    }

    static void setHighScore(int newScore) {
        int currentHs = getHighScore();
        if (newScore > currentHs) {
            std::ofstream file("highscore.dat");
            if (file) {
                file << newScore;
            }
        }
    }
};

#endif // COLOR_RENDERER_H
