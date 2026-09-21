#ifndef BAG7_H
#define BAG7_H

#include "Tetromino.h"

/**
 * @brief The official Tetris randomizer: a bag with all seven pieces.
 *
 * rand() % 7 can give the same piece five times in a row and can hide a piece
 * for a long time. The bag shuffles all seven types, hands them out one by one,
 * and only refills when it is empty, so every seven pieces contain each type
 * exactly once.
 */
class Bag7
{
    int pieces[Tetromino::TYPE_COUNT];
    int position;                        // index of the next piece to hand out

public:
    Bag7();

    int next();                          // type of the next piece
    int remaining() const { return Tetromino::TYPE_COUNT - position; }

private:
    void refill();                       // put all seven types back and shuffle
};

#endif // BAG7_H
