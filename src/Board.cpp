#include "Board.h"

const int Board::WIDTH;
const int Board::HEIGHT;
const int Board::EMPTY;

Board::Board() {
    reset();
}

void Board::reset() {
    for (int r = 0; r < HEIGHT; ++r)
        for (int c = 0; c < WIDTH; ++c)
            grid_[r][c] = EMPTY;
}

bool Board::collides(const Tetromino& piece) const {
    std::array<Point, 4> cells = piece.cells();
    for (int i = 0; i < 4; ++i) {
        const Point& p = cells[i];
        if (p.x < 0 || p.x >= WIDTH) return true;   // cham tuong trai / phai
        if (p.y >= HEIGHT)           return true;   // cham day
        if (p.y >= 0 && grid_[p.y][p.x] != EMPTY) return true;
    }
    return false;
}

bool Board::lock(const Tetromino& piece) {
    bool insideBoard = true;
    std::array<Point, 4> cells = piece.cells();
    for (int i = 0; i < 4; ++i) {
        const Point& p = cells[i];
        if (p.y < 0) { insideBoard = false; continue; }
        grid_[p.y][p.x] = piece.color();
    }
    return insideBoard;
}

// TODO (SV2): viet ham xoa hang.
//   1. Duyet tu hang DUOI CUNG len tren.
//   2. Hang nao du 10 o (khong co o EMPTY) -> xoa: dich tat ca hang phia tren xuong 1 hang,
//      hang tren cung thanh hang trong.
//   3. Sau khi xoa, KIEM TRA LAI chinh hang do (vi hang phia tren vua roi xuong).
//   4. Tra ve so hang da xoa. Game::onLinesCleared() se dung so nay de cong diem.
int Board::removeFullLines() {
    int cleared = 0;
    int r = HEIGHT - 1;
    while (r >= 0) {
        bool full = true;
        for (int c = 0; c < WIDTH; ++c) {
            if (grid_[r][c] == EMPTY) { full = false; break; }
        }

        if (!full) {
            --r;                                  // hang chua day -> xet hang phia tren
            continue;
        }

        // Dich tat ca hang phia tren xuong 1 hang
        for (int y = r; y > 0; --y)
            for (int c = 0; c < WIDTH; ++c)
                grid_[y][c] = grid_[y - 1][c];

        // Hang tren cung thanh hang trong
        for (int c = 0; c < WIDTH; ++c)
            grid_[0][c] = EMPTY;

        ++cleared;
        // Khong giam r: kiem tra lai chinh hang nay vi hang phia tren vua roi xuong
    }
    return cleared;
}
