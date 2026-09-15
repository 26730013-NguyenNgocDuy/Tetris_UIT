#include "Console.h"

#include <windows.h>

void*    Console::handle_      = INVALID_HANDLE_VALUE;
unsigned Console::oldCodePage_ = 0;

static HANDLE out(void* h) { return static_cast<HANDLE>(h); }

void Console::init(const char* title) {
    // "CONOUT$" luon la man hinh console, ke ca khi stdout bi chuyen huong.
    handle_ = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE,
                          FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    oldCodePage_ = GetConsoleOutputCP();
    SetConsoleOutputCP(437);             // bang ma 437 co ky tu khoi dac (char)219
    SetConsoleTitleA(title);

    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = FALSE;             // an con tro nhap nhay
    SetConsoleCursorInfo(out(handle_), &cursor);

    clear();
}

void Console::restore() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 20;
    cursor.bVisible = TRUE;
    SetConsoleCursorInfo(out(handle_), &cursor);

    write(0, 23, "", GRAY);
    SetConsoleOutputCP(oldCodePage_);
    CloseHandle(out(handle_));
}

void Console::clear() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(out(handle_), &info)) return;

    DWORD size = static_cast<DWORD>(info.dwSize.X) * info.dwSize.Y;
    DWORD written = 0;
    COORD home = { 0, 0 };
    FillConsoleOutputCharacterA(out(handle_), ' ', size, home, &written);
    FillConsoleOutputAttribute(out(handle_), GRAY, size, home, &written);
    SetConsoleCursorPosition(out(handle_), home);
}

void Console::sleepMs(int ms) {
    Sleep(static_cast<DWORD>(ms));
}

void Console::write(int x, int y, const std::string& text, int color) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(out(handle_), pos);
    SetConsoleTextAttribute(out(handle_), static_cast<WORD>(color));

    DWORD written = 0;
    WriteConsoleA(out(handle_), text.c_str(), static_cast<DWORD>(text.size()), &written, NULL);
}
