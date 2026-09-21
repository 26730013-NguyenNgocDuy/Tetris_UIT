#include "Input.h"

#include "Platform.h"

Action Input::poll()
{
    if (!kbhit())
        return ACTION_NONE;

    char key = getch();

    switch (key)
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
