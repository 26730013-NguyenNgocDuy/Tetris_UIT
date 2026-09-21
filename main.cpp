// Tetris_UIT - do an mon Ky nang nghe nghiep (SS004)
// Toan bo logic nam trong cac lop: Game, Board, Tetromino, Bag7, Renderer, Input.
#include <cstdlib>
#include <ctime>

#include "Game.h"

int main()
{
    // Gieo số ngẫu nhiên một lần, trước khi Game tạo túi khối đầu tiên
    srand(static_cast<unsigned int>(time(0)));

    Game game;
    game.run();

    return 0;
}
