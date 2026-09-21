#ifndef PLATFORM_H
#define PLATFORM_H

/**
 * @brief Lớp tương thích đa nền tảng
 *
 * - Windows: dùng trực tiếp <conio.h> và <windows.h> như cũ.
 * - macOS / Linux: tự cài đặt kbhit(), getch(), Sleep() bằng termios.
 */

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

#else

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

namespace platform_detail {

inline termios &originalTermios()
{
    static termios t;
    return t;
}

inline void restoreTerminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &originalTermios());
    // Hiện lại con trỏ và reset màu
    std::cout << "\033[0m\033[?25h" << std::flush;
}

inline void onSignal(int sig)
{
    restoreTerminal();
    std::signal(sig, SIG_DFL);
    std::raise(sig);
}

// Tắt chế độ canonical và echo để đọc từng phím ngay lập tức
struct RawTerminal
{
    RawTerminal()
    {
        tcgetattr(STDIN_FILENO, &originalTermios());
        termios raw = originalTermios();
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_cc[VMIN] = 1;
        raw.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);

        std::atexit(restoreTerminal);
        std::signal(SIGINT, onSignal);
        std::signal(SIGTERM, onSignal);
    }
};

inline void ensureRawTerminal()
{
    static RawTerminal raw;
}

} // namespace platform_detail

inline int kbhit()
{
    platform_detail::ensureRawTerminal();
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    timeval tv = {0, 0};
    return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
}

inline int getch()
{
    platform_detail::ensureRawTerminal();
    std::cout << std::flush;
    unsigned char c = 0;
    if (read(STDIN_FILENO, &c, 1) != 1)
        return -1;
    return c;
}

inline void Sleep(unsigned int ms)
{
    std::cout << std::flush;
    usleep(ms * 1000);
}

#endif // _WIN32

#endif // PLATFORM_H
