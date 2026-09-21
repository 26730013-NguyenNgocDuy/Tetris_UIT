#ifndef GAME_H
#define GAME_H

#include "Bag7.h"
#include "Board.h"
#include "DropSpeedController.h"
#include "HighScore.h"
#include "Input.h"
#include "Renderer.h"
#include "Blocks.h"

class GameState;

/**
 * @brief Lớp điều khiển ván chơi: giữ mọi thứ của game và chạy vòng lặp chính.
 *
 * TÍNH HỢP THÀNH (sở hữu): Game chứa Board, khối đang rơi, Bag7, DropSpeedController,
 * Renderer, Input và HighScore làm thành phần. Chúng sinh ra và mất đi cùng với Game.
 *
 * Trước khi có lớp này, tất cả nằm rải rác thành biến toàn cục trong main.cpp,
 * ai cũng sửa được. Nay muốn chơi một ván là tạo một đối tượng Game.
 */
class Game
{
public:
    // Mỗi nhịp vòng lặp dài 25 ms (40 lần mỗi giây) nên phím phản hồi ngay
    static const int TICK_MS = 25;

    Game();
    ~Game();

    void run();     // vòng lặp chính, chạy tới khi người chơi thoát

    // Đổi trạng thái. Trạng thái cũ chỉ bị xoá ở cuối nhịp, vì hàm gọi lệnh này
    // thường chính là phương thức của trạng thái cũ, xoá ngay sẽ hỏng.
    void setState(GameState *newState);

    Renderer &getRenderer() { return renderer; }

    // Các thao tác của người chơi
    void moveLeft();
    void moveRight();
    void softDrop();
    void rotatePiece();
    void hold();
    void hardDrop();

    void tick();                  // cộng đồng hồ rơi, đủ nhịp thì cho khối rơi một dòng
    void applyGravity();          // khối tự rơi một dòng, chạm đáy thì chốt lại
    void drawPlayfield();         // vẽ sân chơi và các khung thông tin
    void drawIfChanged();         // chỉ vẽ lại khi có gì đổi, đỡ nháy màn hình
    void markChanged() { changed = true; }
    void saveHighScore();         // ghi điểm cao ra file
    void restart();               // chơi lại từ đầu
    void quit() { running = false; }

    bool isOver() const { return over; }
    int getDropInterval() const { return speed.getDropInterval(); }
    int getScore() const { return speed.getScore(); }

private:
    Board board;
    Blocks *current;       // khối đang rơi, Game sở hữu nên phải tự xoá
    Bag7 bag;
    DropSpeedController speed;
    Renderer renderer;
    Input input;
    HighScore highScore;   // đọc file điểm cao một lần lúc mở game

    int holdType;          // loại khối đang giữ, -1 là chưa giữ gì
    bool canHold;          // mỗi khối chỉ được giữ một lần
    int nextQueue[4];      // bốn khối sắp tới
    bool running;          // còn chạy vòng lặp hay không
    bool over;             // đã thua chưa
    int dropTimer;         // số mili giây đã trôi từ lần rơi trước
    bool changed;          // có gì đổi cần vẽ lại không
    bool justDropped;      // vừa thả khối bằng phím cách trong nhịp này

    GameState *state;      // trạng thái hiện tại, Game sở hữu và tự xoá
    GameState *pending;    // trạng thái sắp chuyển sang, chờ hết nhịp

    // Game sở hữu các thành phần bên trên nên không cho sao chép: sao chép sẽ
    // tạo ra hai ván chơi dùng chung một bàn cờ. Khai báo mà không định nghĩa.
    Game(const Game &);
    void operator = (const Game &);

    bool canMove(int dx, int dy) const { return board.canPlace(*current, dx, dy); }
    int ghostRow() const;
    void fillQueue();
    void spawn(int type = -1);
    int clearFullRows();
};

#endif // GAME_H
