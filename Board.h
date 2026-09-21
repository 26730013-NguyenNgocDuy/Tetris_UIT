#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"

/**
 * @brief The playing field: the wall and every locked cell.
 *
 * The grid is private. Everything outside reads it through at() and changes it
 * through set(), so no other file can touch the array by hand.
 */
class Board
{
public:
    // Kept as class constants instead of #define, so the size belongs to the class
    static const int ROWS = 20;
    static const int COLS = 12;
    static const char WALL = '#';
    static const char EMPTY = ' ';

    Board();

    // Builds the wall around an empty field
    void reset();

    char at(int row, int col) const;
    bool isEmpty(int row, int col) const { return at(row, col) == EMPTY; }
    void set(int row, int col, char value);

    // True when the piece, moved by (dx, dy), still fits inside the walls and
    // does not touch a cell that is already taken.
    bool canPlace(const Tetromino &piece, int dx, int dy) const;

    // Writes the piece into the grid, or clears the cells it stands on
    void place(const Tetromino &piece);
    void erase(const Tetromino &piece);

    // Line clearing is split in two so the caller can show an effect in between
    bool isRowFull(int row) const;
    void removeRow(int row);

private:
    char grid[ROWS][COLS];

    static bool isInside(int row, int col);
};

#endif // BOARD_H
