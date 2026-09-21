#include "Input.h"

#include "Platform.h"

// Đọc một phím, đổi phím mũi tên thành phím chữ tương ứng (lên = W, xuống = S,
// trái = A, phải = D) để phần dưới chỉ phải xét một kiểu.
static int readKey()
{
    int c = getch();
#ifdef _WIN32
    // Trên Windows, phím mũi tên gửi hai mã: mã báo 0 hoặc 224, rồi mã hướng
    if (c == 0 || c == 224 || c == -32)
    {
        int ext = getch();
        if (ext == 72) return 'w';
        if (ext == 80) return 's';
        if (ext == 75) return 'a';
        if (ext == 77) return 'd';
    }
#else
    // Trên macOS / Linux, phím mũi tên là chuỗi ESC [ A/B/C/D
    if (c == 27)
    {
        if (kbhit() && getch() == '[')
        {
            int ext = getch();
            if (ext == 'A') return 'w';
            if (ext == 'B') return 's';
            if (ext == 'D') return 'a';
            if (ext == 'C') return 'd';
        }
    }
#endif
    return c;
}

Action Input::poll()
{
    if (!kbhit())
        return ACTION_NONE;

    switch (readKey())
    {
    case 'a': case 'A': return ACTION_LEFT;
    case 'd': case 'D': return ACTION_RIGHT;
    case 's': case 'S': return ACTION_SOFT_DROP;
    case 'w': case 'W': return ACTION_ROTATE;
    case 'c': case 'C': return ACTION_HOLD;
    case ' ':           return ACTION_HARD_DROP;
    case 'p': case 'P': return ACTION_PAUSE;
    case 'r': case 'R': return ACTION_RESTART;
    case 'q': case 'Q': return ACTION_QUIT;
    default:            return ACTION_NONE;
    }
}
