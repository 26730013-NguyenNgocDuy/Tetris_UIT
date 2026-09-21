#include "Board.h"

const int Board::ROWS;
const int Board::COLS;
const char Board::WALL;
const char Board::EMPTY;

Board::Board()
{
    reset();
}

void Board::reset()
{
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
        {
            bool onEdge = (r == 0 || r == ROWS - 1 || c == 0 || c == COLS - 1);
            grid[r][c] = onEdge ? WALL : EMPTY;
        }
}

bool Board::isInside(int row, int col)
{
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

char Board::at(int row, int col) const
{
    if (!isInside(row, col))
        return WALL;            // outside the field counts as wall
    return grid[row][col];
}

void Board::set(int row, int col, char value)
{
    if (isInside(row, col))
        grid[row][col] = value;
}
