#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"

// Bang choi 10 x 20. Moi o luu MAU cua khoi da khoa, hoac EMPTY neu trong.
class Board {
public:
    static const int WIDTH  = 10;
    static const int HEIGHT = 20;
    static const int EMPTY  = -1;

    Board();
    void reset();

    // Khoi co de len tuong, day, hoac o da co khong?
    // O nam PHIA TREN mep bang (y < 0) duoc phep, vi khoi moi sinh ra o do.
    bool collides(const Tetromino& piece) const;

    // Ghi 4 o cua khoi vao bang. Tra ve false neu co o nam tren mep bang (thua).
    bool lock(const Tetromino& piece);

    // Xoa cac hang day, tra ve so hang da xoa.
    int removeFullLines();

    int colorAt(int row, int col) const { return grid_[row][col]; }

private:
    int grid_[HEIGHT][WIDTH];
};

#endif
