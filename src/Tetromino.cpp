#include "Tetromino.h"
#include "Console.h"

namespace {

struct ShapeData {
    int box;
    Point cells[4];
    int color;
};

// Huong xuat phat cua 7 khoi, theo thu tu enum PieceType: I O T S Z J L.
const ShapeData SHAPES[PIECE_COUNT] = {
    { 4, { {0, 1}, {1, 1}, {2, 1}, {3, 1} }, CYAN        },   // I
    { 2, { {0, 0}, {1, 0}, {0, 1}, {1, 1} }, YELLOW      },   // O
    { 3, { {1, 0}, {0, 1}, {1, 1}, {2, 1} }, MAGENTA     },   // T
    { 3, { {1, 0}, {2, 0}, {0, 1}, {1, 1} }, GREEN       },   // S
    { 3, { {0, 0}, {1, 0}, {1, 1}, {2, 1} }, RED         },   // Z
    { 3, { {0, 0}, {0, 1}, {1, 1}, {2, 1} }, BLUE        },   // J
    { 3, { {2, 0}, {0, 1}, {1, 1}, {2, 1} }, DARK_YELLOW },   // L (console khong co mau cam)
};

const ShapeData& shapeOf(PieceType type) {
    return SHAPES[static_cast<int>(type)];
}

}  // namespace

Tetromino::Tetromino() : Tetromino(PieceType::I) {}

Tetromino::Tetromino(PieceType type) : type_(type), box_(shapeOf(type).box), x_(0), y_(0) {
    for (int i = 0; i < 4; ++i) local_[i] = shapeOf(type).cells[i];
}

int Tetromino::color() const {
    return shapeOf(type_).color;
}

std::array<Point, 4> Tetromino::cells() const {
    std::array<Point, 4> result;
    for (int i = 0; i < 4; ++i) {
        result[i].x = x_ + local_[i].x;
        result[i].y = y_ + local_[i].y;
    }
    return result;
}

Tetromino Tetromino::moved(int dx, int dy) const {
    Tetromino copy = *this;
    copy.x_ += dx;
    copy.y_ += dy;
    return copy;
}

// Xoay 90 do theo chieu kim dong ho quanh tam khung:  (x, y) -> (box - 1 - y, x)
Tetromino Tetromino::rotatedCW() const {
    Tetromino copy = *this;
    for (int i = 0; i < 4; ++i) {
        copy.local_[i].x = box_ - 1 - local_[i].y;
        copy.local_[i].y = local_[i].x;
    }
    return copy;
}

void Tetromino::placeAtSpawn(int boardWidth) {
    x_ = (boardWidth - box_) / 2;
    y_ = (type_ == PieceType::I) ? -1 : 0;   // khoi I nam o hang 1 cua khung -> dua len 1 hang
}
