#include "Tetromino.h"

// The seven standard tetrominoes. Each letter is also the color key used by
// ColorRenderer, so the piece carries its own color with it.
const char Tetromino::SHAPES[TYPE_COUNT][SIZE][SIZE] = {
    // I
    {{' ', ' ', ' ', ' '},
     {'I', 'I', 'I', 'I'},
     {' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    // O
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    // T
    {{' ', ' ', ' ', ' '},
     {' ', 'T', ' ', ' '},
     {'T', 'T', 'T', ' '},
     {' ', ' ', ' ', ' '}},
    // S
    {{' ', ' ', ' ', ' '},
     {' ', 'S', 'S', ' '},
     {'S', 'S', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    // Z
    {{' ', ' ', ' ', ' '},
     {'Z', 'Z', ' ', ' '},
     {' ', 'Z', 'Z', ' '},
     {' ', ' ', ' ', ' '}},
    // J
    {{' ', ' ', ' ', ' '},
     {'J', ' ', ' ', ' '},
     {'J', 'J', 'J', ' '},
     {' ', ' ', ' ', ' '}},
    // L
    {{' ', ' ', ' ', ' '},
     {' ', ' ', 'L', ' '},
     {'L', 'L', 'L', ' '},
     {' ', ' ', ' ', ' '}}
};

Tetromino::Tetromino(int pieceType, int startX, int startY)
{
    // Keep the type inside the table even if the caller passes a wrong number
    if (pieceType < 0 || pieceType >= TYPE_COUNT)
        pieceType = 0;

    type = pieceType;
    posX = startX;
    posY = startY;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            shape[i][j] = SHAPES[type][i][j];
}

bool Tetromino::isInside(int row, int col)
{
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

char Tetromino::at(int row, int col) const
{
    if (!isInside(row, col))
        return ' ';
    return shape[row][col];
}

void Tetromino::setPosition(int newX, int newY)
{
    posX = newX;
    posY = newY;
}

void Tetromino::move(int dx, int dy)
{
    posX += dx;
    posY += dy;
}

Tetromino Tetromino::rotated() const
{
    Tetromino copy(*this);

    // Turn 90 degrees clockwise inside the 4x4 box
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            copy.shape[i][j] = shape[SIZE - 1 - j][i];

    return copy;
}

char Tetromino::shapeAt(int pieceType, int row, int col)
{
    if (pieceType < 0 || pieceType >= TYPE_COUNT || !isInside(row, col))
        return ' ';
    return SHAPES[pieceType][row][col];
}
