#include "Bag7.h"

#include <cstdlib>

Bag7::Bag7()
{
    // Start with an empty bag on purpose. A Bag7 built before main() runs would
    // otherwise shuffle before srand() is called, and every game would begin
    // with the same pieces. The first next() fills the bag instead.
    position = Tetromino::TYPE_COUNT;
}

void Bag7::refill()
{
    for (int i = 0; i < Tetromino::TYPE_COUNT; i++)
        pieces[i] = i;

    // Fisher-Yates shuffle: walk from the end and swap with a random earlier slot
    for (int i = Tetromino::TYPE_COUNT - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int keep = pieces[i];
        pieces[i] = pieces[j];
        pieces[j] = keep;
    }

    position = 0;
}

int Bag7::next()
{
    if (position >= Tetromino::TYPE_COUNT)
        refill();

    return pieces[position++];
}
