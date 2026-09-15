#include "Renderer.h"
#include "Console.h"

#include <string>

namespace {

// Vi tri tren man hinh (don vi: ky tu).
const int BOARD_X = 4;                               // cot ky tu cua o [.][0]
const int BOARD_Y = 1;                               // hang ky tu cua o [0][.]
const int CELL_W  = 2;                               // moi o = 2 ky tu -> trong VUONG
const int PANEL_X = BOARD_X + Board::WIDTH * CELL_W + 4;

const char BLOCK      = static_cast<char>(219);      // khoi dac  (bang ma 437)
const char DOT        = static_cast<char>(250);      // cham nho cho o trong
const char V_LINE     = static_cast<char>(186);
const char H_LINE     = static_cast<char>(205);
const char TOP_LEFT   = static_cast<char>(201);
const char TOP_RIGHT  = static_cast<char>(187);
const char BOT_LEFT   = static_cast<char>(200);
const char BOT_RIGHT  = static_cast<char>(188);

std::string centered(const std::string& text, int width) {
    int left = (width - static_cast<int>(text.size())) / 2;
    if (left < 0) left = 0;
    std::string line(left, ' ');
    line += text;
    line.resize(width, ' ');
    return line;
}

std::string padNumber(int value) {
    std::string s = std::to_string(value);
    while (s.size() < 8) s += ' ';                   // xoa chu so cu con sot
    return s;
}

}  // namespace

Renderer::Renderer() {
    invalidate();
}

void Renderer::invalidate() {
    for (int r = 0; r < Board::HEIGHT; ++r)
        for (int c = 0; c < Board::WIDTH; ++c)
            shown_[r][c] = -2;                       // -2: chac chan khac moi mau that
    nextValid_ = false;
    statsValid_ = false;
}

void Renderer::drawStatic() {
    const int innerW = Board::WIDTH * CELL_W;

    Console::write(BOARD_X - 1, BOARD_Y - 1,
                   TOP_LEFT + std::string(innerW, H_LINE) + TOP_RIGHT, GRAY);
    for (int r = 0; r < Board::HEIGHT; ++r) {
        Console::write(BOARD_X - 1, BOARD_Y + r, std::string(1, V_LINE), GRAY);
        Console::write(BOARD_X + innerW, BOARD_Y + r, std::string(1, V_LINE), GRAY);
    }
    Console::write(BOARD_X - 1, BOARD_Y + Board::HEIGHT,
                   BOT_LEFT + std::string(innerW, H_LINE) + BOT_RIGHT, GRAY);

    Console::write(PANEL_X, 1,  "NEXT",  WHITE);
    Console::write(PANEL_X, 8,  "SCORE", WHITE);
    Console::write(PANEL_X, 11, "LINES", WHITE);
    Console::write(PANEL_X, 14, "LEVEL", WHITE);

    Console::write(PANEL_X, 17, "Left/Right  move",   DARK_GRAY);
    Console::write(PANEL_X, 18, "Up          rotate", DARK_GRAY);
    Console::write(PANEL_X, 19, "Down        soft drop", DARK_GRAY);
    Console::write(PANEL_X, 20, "Space       hard drop", DARK_GRAY);
    Console::write(PANEL_X, 21, "P pause   Esc quit",  DARK_GRAY);
}

void Renderer::draw(const Board& board, const Tetromino& current,
                    const Tetromino& next, const GameStats& stats) {
    // 1. Ghep bang choi + khoi dang roi thanh 1 "khung hinh".
    int view[Board::HEIGHT][Board::WIDTH];
    for (int r = 0; r < Board::HEIGHT; ++r)
        for (int c = 0; c < Board::WIDTH; ++c)
            view[r][c] = board.colorAt(r, c);

    std::array<Point, 4> cells = current.cells();
    for (int i = 0; i < 4; ++i)
        if (cells[i].y >= 0) view[cells[i].y][cells[i].x] = current.color();

    // 2. Chi ve lai nhung o khac voi lan truoc.
    for (int r = 0; r < Board::HEIGHT; ++r)
        for (int c = 0; c < Board::WIDTH; ++c)
            if (view[r][c] != shown_[r][c]) {
                drawCell(r, c, view[r][c]);
                shown_[r][c] = view[r][c];
            }

    if (!nextValid_ || next.type() != shownNext_) drawNext(next);

    if (!statsValid_ || stats.score != shownStats_.score ||
        stats.lines != shownStats_.lines || stats.level != shownStats_.level)
        drawStats(stats);
}

void Renderer::drawCell(int row, int col, int color) {
    int x = BOARD_X + col * CELL_W;
    int y = BOARD_Y + row;
    if (color == Board::EMPTY)
        Console::write(x, y, std::string(1, DOT) + ' ', DARK_GRAY);
    else
        Console::write(x, y, std::string(CELL_W, BLOCK), color);
}

void Renderer::drawNext(const Tetromino& next) {
    for (int r = 0; r < 4; ++r)                      // xoa khung 4x4 cu
        Console::write(PANEL_X, 3 + r, std::string(4 * CELL_W, ' '), BLACK);

    const std::array<Point, 4>& cells = next.localCells();
    for (int i = 0; i < 4; ++i)
        Console::write(PANEL_X + cells[i].x * CELL_W, 3 + cells[i].y,
                       std::string(CELL_W, BLOCK), next.color());

    shownNext_ = next.type();
    nextValid_ = true;
}

void Renderer::drawStats(const GameStats& stats) {
    Console::write(PANEL_X, 9,  padNumber(stats.score), YELLOW);
    Console::write(PANEL_X, 12, padNumber(stats.lines), YELLOW);
    Console::write(PANEL_X, 15, padNumber(stats.level), YELLOW);
    shownStats_ = stats;
    statsValid_ = true;
}

void Renderer::drawMessage(const char* line1, const char* line2) {
    const int innerW = Board::WIDTH * CELL_W;
    int y = BOARD_Y + Board::HEIGHT / 2 - 2;

    Console::write(BOARD_X, y,     std::string(innerW, ' '), WHITE);
    Console::write(BOARD_X, y + 1, centered(line1, innerW),  WHITE);
    Console::write(BOARD_X, y + 2, centered(line2, innerW),  GRAY);
    Console::write(BOARD_X, y + 3, std::string(innerW, ' '), WHITE);

    // Cac o bi chu de len da thay doi -> lan draw() sau phai ve lai ca bang.
    for (int r = 0; r < Board::HEIGHT; ++r)
        for (int c = 0; c < Board::WIDTH; ++c)
            shown_[r][c] = -2;
}
