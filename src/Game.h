#ifndef GAME_H
#define GAME_H

#include <chrono>

#include "Bag7.h"
#include "Board.h"
#include "Input.h"
#include "Renderer.h"
#include "Tetromino.h"

// Nhac truong: giu cac doi tuong khac va quyet dinh luat choi.
class Game {
public:
    explicit Game(unsigned seed);

    void run();                    // vong lap that: doc phim, cho khoi roi, ve

    // Cac buoc nho cua vong lap - de public de doc code va de kiem thu tung buoc.
    void start();
    void handle(Command cmd);
    void tick();                   // trong luc: keo khoi xuong 1 o
    void render();

    bool isOver() const { return over_; }
    const Board& board() const { return board_; }
    const Tetromino& current() const { return current_; }
    const GameStats& stats() const { return stats_; }

private:
    bool tryMove(int dx, int dy);
    bool tryRotate();
    void hardDrop();
    void lockAndSpawn();
    void spawn();

    void onLinesCleared(int count);   // TODO (SV5)
    int  fallDelayMs() const;         // TODO (SV5)

    Board     board_;
    Bag7      bag_;
    Tetromino current_;
    Tetromino next_;
    Renderer  renderer_;
    Input     input_;
    GameStats stats_;

    bool over_;
    bool paused_;
    bool quit_;
    std::chrono::steady_clock::time_point lastFall_;
};

#endif
