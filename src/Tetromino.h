#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>

enum class PieceType { I, O, T, S, Z, J, L };
const int PIECE_COUNT = 7;

struct Point {
    int x;   // cot
    int y;   // hang (tang dan khi di XUONG)
};

// Mot khoi gom 4 o, nam trong mot khung vuong rieng (2x2, 3x3 hoac 4x4).
// Khoi KHONG tu sua minh: moved() va rotatedCW() tra ve BAN SAO.
// Game thu ban sao do tren Board truoc, hop le thi moi nhan.
class Tetromino {
public:
    Tetromino();
    explicit Tetromino(PieceType type);

    PieceType type() const { return type_; }
    int color() const;
    int boxSize() const { return box_; }

    std::array<Point, 4> cells() const;                            // toa do tren bang choi
    const std::array<Point, 4>& localCells() const { return local_; } // toa do trong khung

    Tetromino moved(int dx, int dy) const;
    Tetromino rotatedCW() const;

    void placeAtSpawn(int boardWidth);

private:
    PieceType type_;
    std::array<Point, 4> local_;
    int box_;
    int x_;
    int y_;
};

#endif
