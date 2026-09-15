#ifndef RENDERER_H
#define RENDERER_H

#include "Board.h"
#include "Tetromino.h"

struct GameStats {
    int score;
    int lines;
    int level;
};

// Ve moi thu len man hinh.
// Chong nhap nhay: nho lai mau dang hien o tung o, lan sau CHI ve lai o nao thay doi.
class Renderer {
public:
    Renderer();

    void drawStatic();     // khung vien, nhan chu, huong dan phim - ve 1 lan
    void draw(const Board& board, const Tetromino& current,
              const Tetromino& next, const GameStats& stats);

    void drawMessage(const char* line1, const char* line2);   // chu de len giua bang choi
    void invalidate();     // quen het nhung gi da ve -> lan draw() sau ve lai toan bo

private:
    void drawCell(int row, int col, int color);
    void drawNext(const Tetromino& next);
    void drawStats(const GameStats& stats);

    int shown_[Board::HEIGHT][Board::WIDTH];
    bool nextValid_;
    PieceType shownNext_;
    bool statsValid_;
    GameStats shownStats_;
};

#endif
