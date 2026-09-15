#ifndef BAG7_H
#define BAG7_H

#include <array>
#include <random>

#include "Tetromino.h"

// "Tui 7 khoi": xao tron du 7 loai roi phat lan luot, het tui moi xao tui moi.
// Moi loai khoi xuat hien dung 1 lan trong moi 7 luot -> cong bang.
class Bag7 {
public:
    explicit Bag7(unsigned seed);
    PieceType next();

private:
    void refill();

    std::array<PieceType, PIECE_COUNT> bag_;
    int index_;
    std::mt19937 rng_;
};

#endif
