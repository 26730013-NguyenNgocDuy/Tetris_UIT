#ifndef GAME_H
#define GAME_H

#include "Bag7.h"
#include "Board.h"
#include "DropSpeedController.h"
#include "Input.h"
#include "Renderer.h"
#include "Tetromino.h"

/**
 * @brief Lớp điều khiển ván chơi: giữ mọi thứ của game và chạy vòng lặp chính.
 *
 * TÍNH HỢP THÀNH (sở hữu): Game chứa Board, Tetromino, Bag7, DropSpeedController,
 * Renderer và Input làm thành phần. Chúng sinh ra và mất đi cùng với Game.
 *
 * Trước khi có lớp này, tất cả nằm rải rác thành biến toàn cục trong main.cpp,
 * ai cũng sửa được. Nay muốn chơi một ván là tạo một đối tượng Game.
 */
class Game
{
public:
    Game();

    void run();     // vòng lặp chính, chạy tới khi người chơi thoát

    // Các thao tác của người chơi
    void moveLeft();
    void moveRight();
    void softDrop();
    void rotatePiece();
    void hold();
    void hardDrop();

    void applyGravity();          // khối tự rơi một dòng, chạm đáy thì chốt lại
    void drawPlayfield();         // vẽ sân chơi và ba khung thông tin
    void restart();               // chơi lại từ đầu
    void quit() { running = false; }

    bool isOver() const { return over; }
    int getDropInterval() const { return speed.getDropInterval(); }

private:
    Board board;
    Tetromino current;
    Bag7 bag;
    DropSpeedController speed;
    Renderer renderer;
    Input input;

    int holdType;          // loại khối đang giữ, -1 là chưa giữ gì
    bool canHold;          // mỗi khối chỉ được giữ một lần
    int nextQueue[4];      // bốn khối sắp tới
    bool running;          // còn chạy vòng lặp hay không
    bool over;             // đã thua chưa

    // Game sở hữu các thành phần bên trên nên không cho sao chép: sao chép sẽ
    // tạo ra hai ván chơi dùng chung một bàn cờ. Khai báo mà không định nghĩa.
    Game(const Game &);
    void operator = (const Game &);

    bool canMove(int dx, int dy) const { return board.canPlace(current, dx, dy); }
    int ghostRow() const;
    void fillQueue();
    void spawn(int type = -1);
    int clearFullRows();
};

#endif // GAME_H
