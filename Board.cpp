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
            // Hàng đầu, hàng cuối, cột đầu, cột cuối là tường
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
    // Toạ độ ngoài lưới coi như tường. Nhờ vậy canPlace() không phải viết thêm
    // câu lệnh kiểm tra biên riêng.
    if (!isInside(row, col))
        return WALL;
    return grid[row][col];
}

void Board::set(int row, int col, char value)
{
    if (isInside(row, col))
        grid[row][col] = value;
}

void Board::place(const Blocks &piece)
{
    for (int i = 0; i < Blocks::SIZE; i++)
        for (int j = 0; j < Blocks::SIZE; j++)
            if (piece.isFilled(i, j))
                set(piece.getY() + i, piece.getX() + j, piece.at(i, j));
}

void Board::erase(const Blocks &piece)
{
    for (int i = 0; i < Blocks::SIZE; i++)
        for (int j = 0; j < Blocks::SIZE; j++)
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
    // Mọi hàng phía trên tụt xuống một dòng, hàng trên cùng thành trống
    for (int r = row; r > 1; r--)
        for (int c = 1; c < COLS - 1; c++)
            grid[r][c] = grid[r - 1][c];

    for (int c = 1; c < COLS - 1; c++)
        grid[1][c] = EMPTY;
}

bool Board::canPlace(const Blocks &piece, int dx, int dy) const
{
    for (int i = 0; i < Blocks::SIZE; i++)
        for (int j = 0; j < Blocks::SIZE; j++)
        {
            if (!piece.isFilled(i, j))
                continue;

            int r = piece.getY() + i + dy;
            int c = piece.getX() + j + dx;

            if (c < 1 || c >= COLS - 1 || r >= ROWS - 1)
                return false;

            // Phía trên đỉnh bàn cờ vẫn trống, khối mới rơi vào từ đó
            if (r >= 0 && !isEmpty(r, c))
                return false;
        }
    return true;
}
