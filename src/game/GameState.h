#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Input.h"

class Game;

/**
 * @brief Lớp cơ sở TRỪU TƯỢNG cho các trạng thái của game.
 *
 * Game có ba trạng thái: đang chơi, tạm dừng, thua cuộc. Cùng một lệnh
 * state->update() nhưng mỗi trạng thái làm một việc khác nhau, đó là TÍNH ĐA HÌNH.
 *
 * Ba phương thức dưới đây là THUẦN ẢO (= 0) nên không tạo được đối tượng
 * GameState, chỉ tạo được lớp con. Lớp con buộc phải định nghĩa lại cả ba.
 *
 * Hàm huỷ bỏ phải là hàm ẢO: Game giữ con trỏ GameState*, khi xoá qua con trỏ
 * lớp cha thì hàm huỷ của lớp con mới được gọi đúng.
 */
class GameState
{
protected:
    Game *game;   // LIÊN KẾT chứ không sở hữu: trạng thái không xoá Game

public:
    GameState(Game *owner) : game(owner) { }
    virtual ~GameState() { }

    virtual void handle(Action action) = 0;   // xử lý phím người chơi bấm
    virtual void update() = 0;                // cập nhật sau mỗi nhịp
    virtual void draw() = 0;                  // vẽ màn hình của trạng thái này

    // Hàm ảo có sẵn phần định nghĩa: lớp con nào cần nhịp khác thì viết lại,
    // không viết lại thì dùng 80 mili giây của lớp cha
    virtual int tickMs() const { return 80; }
};

/**
 * @brief Đang chơi: khối rơi theo nhịp, nhận đủ các phím điều khiển.
 */
class PlayingState : public GameState
{
public:
    PlayingState(Game *owner) : GameState(owner) { }

    void handle(Action action);
    void update();
    void draw();
    int tickMs() const;     // nhịp rơi lấy theo cấp độ hiện tại
};

/**
 * @brief Tạm dừng: khối đứng yên, chỉ chờ bấm P để chơi tiếp.
 */
class PausedState : public GameState
{
    bool painted;   // màn hình đứng yên nên chỉ cần vẽ một lần, tránh nháy chữ

public:
    PausedState(Game *owner) : GameState(owner), painted(false) { }

    void handle(Action action);
    void update();
    void draw();
};

/**
 * @brief Thua cuộc: hiện điểm, chờ bấm R để chơi lại.
 */
class GameOverState : public GameState
{
    bool painted;

public:
    GameOverState(Game *owner) : GameState(owner), painted(false) { }

    void handle(Action action);
    void update();
    void draw();
};

#endif // GAME_STATE_H
