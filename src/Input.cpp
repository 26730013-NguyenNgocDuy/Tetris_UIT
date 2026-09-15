#include "Input.h"

#include <conio.h>

namespace {
const int KEY_UP = 72, KEY_DOWN = 80, KEY_LEFT = 75, KEY_RIGHT = 77;
const int KEY_ESC = 27, KEY_SPACE = 32;
}

bool Input::poll(Command& cmd) {
    while (_kbhit()) {
        int key = _getch();

        // Phim mui ten tra ve HAI ma: 0 hoac 224, sau do moi la ma that.
        if (key == 0 || key == 224) {
            switch (_getch()) {
                case KEY_LEFT:  cmd = Command::Left;     return true;
                case KEY_RIGHT: cmd = Command::Right;    return true;
                case KEY_UP:    cmd = Command::Rotate;   return true;
                case KEY_DOWN:  cmd = Command::SoftDrop; return true;
                default:        continue;                // phim dac biet khac: bo qua
            }
        }

        switch (key) {
            case 'a': case 'A': cmd = Command::Left;     return true;
            case 'd': case 'D': cmd = Command::Right;    return true;
            case 'w': case 'W': cmd = Command::Rotate;   return true;
            case 's': case 'S': cmd = Command::SoftDrop; return true;
            case KEY_SPACE:     cmd = Command::HardDrop; return true;
            case 'p': case 'P': cmd = Command::Pause;    return true;
            case 'r': case 'R': cmd = Command::Restart;  return true;
            case KEY_ESC:       cmd = Command::Quit;     return true;
            default:            break;                   // phim la: doc tiep
        }
    }
    return false;
}
