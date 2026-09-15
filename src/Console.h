#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

// 16 mau cua console Windows.
enum Color {
    BLACK = 0,     DARK_BLUE = 1,    DARK_GREEN = 2,   DARK_CYAN = 3,
    DARK_RED = 4,  DARK_MAGENTA = 5, DARK_YELLOW = 6,  GRAY = 7,
    DARK_GRAY = 8, BLUE = 9,         GREEN = 10,       CYAN = 11,
    RED = 12,      MAGENTA = 13,     YELLOW = 14,      WHITE = 15
};

// Gom toan bo lenh Windows API vao mot cho.
// Cac lop khac chi goi Console::..., khong ai phai include <windows.h>.
class Console {
public:
    static void init(const char* title);   // goi 1 lan khi mo game
    static void restore();                 // goi 1 lan khi thoat game
    static void clear();

    static void write(int x, int y, const std::string& text, int color);
    static void sleepMs(int ms);

private:
    static void* handle_;        // HANDLE cua man hinh console
    static unsigned oldCodePage_;
};

#endif
