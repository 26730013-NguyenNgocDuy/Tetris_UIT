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

void Board::place(const Tetromino &piece)
{
    for (int i = 0; i < Tetromino::SIZE; i++)
        for (int j = 0; j < Tetromino::SIZE; j++)
            if (piece.isFilled(i, j))
                set(piece.getY() + i, piece.getX() + j, piece.at(i, j));
}

void Board::erase(const Tetromino &piece)
{
    for (int i = 0; i < Tetromino::SIZE; i++)
        for (int j = 0; j < Tetromino::SIZE; j++)
            if (piece.isFilled(i, j))
                set(piece.getY() + i, piece.getX() + j, EMPTY);
}

bool Board::isRowFull(int row) const
{
    for (int c = 1; c < COLS - 1; c++)
        if (isEmpty(row, c))
            return false;
    return true;
}

void Board::removeRow(int row)
{
    // Every row above slides down one line, the top row becomes empty
    for (int r = row; r > 1; r--)
        for (int c = 1; c < COLS - 1; c++)
            grid[r][c] = grid[r - 1][c];

    for (int c = 1; c < COLS - 1; c++)
        grid[1][c] = EMPTY;
}

bool Board::canPlace(const Tetromino &piece, int dx, int dy) const
{
    for (int i = 0; i < Tetromino::SIZE; i++)
        for (int j = 0; j < Tetromino::SIZE; j++)
        {
            if (!piece.isFilled(i, j))
                continue;

            int r = piece.getY() + i + dy;
            int c = piece.getX() + j + dx;

            if (c < 1 || c >= COLS - 1 || r >= ROWS - 1)
                return false;

            // Rows above the top are still free, a new piece falls in from there
            if (r >= 0 && !isEmpty(r, c))
                return false;
        }
    return true;
}
