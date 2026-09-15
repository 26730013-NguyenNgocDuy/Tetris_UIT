#include "Bag7.h"

#include <algorithm>

Bag7::Bag7(unsigned seed) : index_(PIECE_COUNT), rng_(seed) {
    for (int i = 0; i < PIECE_COUNT; ++i) bag_[i] = static_cast<PieceType>(i);
}

PieceType Bag7::next() {
    if (index_ == PIECE_COUNT) refill();
    return bag_[index_++];
}

void Bag7::refill() {
    std::shuffle(bag_.begin(), bag_.end(), rng_);
    index_ = 0;
}
