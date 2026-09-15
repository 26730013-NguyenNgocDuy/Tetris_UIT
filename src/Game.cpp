#include "Game.h"
#include "Console.h"

using Clock = std::chrono::steady_clock;

Game::Game(unsigned seed)
    : bag_(seed), over_(false), paused_(false), quit_(false) {
    stats_.score = 0;
    stats_.lines = 0;
    stats_.level = 1;
}

// ------------------------------------------------------------------ vong lap
void Game::run() {
    Console::init("Tetris Console");
    start();

    while (!quit_) {
        Command cmd;
        while (input_.poll(cmd)) handle(cmd);

        if (!over_ && !paused_) {
            Clock::duration waited = Clock::now() - lastFall_;
            if (waited >= std::chrono::milliseconds(fallDelayMs())) tick();
            render();
        }

        Console::sleepMs(10);   // nghi 10 ms: du muot, khong an 100% CPU
    }

    Console::restore();
}

void Game::start() {
    board_.reset();
    stats_.score = 0;
    stats_.lines = 0;
    stats_.level = 1;
    over_ = false;
    paused_ = false;

    Console::clear();
    renderer_.invalidate();
    renderer_.drawStatic();

    next_ = Tetromino(bag_.next());
    spawn();
    render();
}

void Game::render() {
    renderer_.draw(board_, current_, next_, stats_);
}

// ------------------------------------------------------------------ phim
void Game::handle(Command cmd) {
    if (cmd == Command::Quit)    { quit_ = true; return; }
    if (cmd == Command::Restart) { start();      return; }
    if (over_) return;

    if (cmd == Command::Pause) {
        paused_ = !paused_;
        if (paused_) renderer_.drawMessage("PAUSED", "P to continue");
        else         lastFall_ = Clock::now();
        return;
    }
    if (paused_) return;

    switch (cmd) {
        case Command::Left:     tryMove(-1, 0); break;
        case Command::Right:    tryMove(+1, 0); break;
        case Command::Rotate:   tryRotate();    break;
        case Command::HardDrop: hardDrop();     break;
        case Command::SoftDrop:
            if (tryMove(0, +1)) stats_.score += 1;
            else                lockAndSpawn();
            break;
        default: break;
    }
}

// ------------------------------------------------------------------ luat choi
void Game::tick() {
    if (!tryMove(0, +1)) lockAndSpawn();
    lastFall_ = Clock::now();
}

bool Game::tryMove(int dx, int dy) {
    Tetromino candidate = current_.moved(dx, dy);
    if (board_.collides(candidate)) return false;
    current_ = candidate;
    return true;
}

// Xoay; neu vuong tuong hoac vuong khoi khac thi thu day lech sang hai ben (wall kick don gian).
bool Game::tryRotate() {
    static const int KICKS[] = { 0, -1, +1, -2, +2 };
    Tetromino rotated = current_.rotatedCW();

    for (int i = 0; i < 5; ++i) {
        Tetromino candidate = rotated.moved(KICKS[i], 0);
        if (!board_.collides(candidate)) {
            current_ = candidate;
            return true;
        }
    }
    return false;
}

void Game::hardDrop() {
    int distance = 0;
    while (tryMove(0, +1)) ++distance;
    stats_.score += 2 * distance;
    lockAndSpawn();
}

void Game::lockAndSpawn() {
    bool inside = board_.lock(current_);

    int cleared = board_.removeFullLines();
    if (cleared > 0) onLinesCleared(cleared);

    if (!inside) {                                   // khoi bi khoa khi con nho ra tren mep bang
        over_ = true;
    } else {
        spawn();
    }

    if (over_) {
        render();
        renderer_.drawMessage("GAME OVER", "R restart  Esc quit");
    }
}

void Game::spawn() {
    current_ = next_;
    current_.placeAtSpawn(Board::WIDTH);
    next_ = Tetromino(bag_.next());
    lastFall_ = Clock::now();

    if (board_.collides(current_)) over_ = true;    // cho sinh khoi da bi chiem
}

// ------------------------------------------------------------------ TODO (SV5)
// Goi moi khi removeFullLines() xoa duoc it nhat 1 hang.
//   - Cong diem: 1 hang 100, 2 hang 300, 3 hang 500, 4 hang 800 (nhan voi level).
//   - Cong stats_.lines; cu du 10 hang thi stats_.level tang 1.
void Game::onLinesCleared(int count) {
    stats_.lines += count;
}

// Thoi gian (ms) khoi roi 1 o. Hien dang CO DINH.
//   - SV5: giam dan theo stats_.level, vi du 500 ms o level 1 va nhanh dan len.
int Game::fallDelayMs() const {
    return 500;
}
