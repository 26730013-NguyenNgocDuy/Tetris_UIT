#include <ctime>

#include "Game.h"

int main() {
    Game game(static_cast<unsigned>(std::time(nullptr)));
    game.run();
    return 0;
}
