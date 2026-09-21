#include "Blocks.h"

const int Blocks::SIZE;
const int Blocks::TYPE_COUNT;

// Bảng hình dạng gốc của bảy khối. Chữ cái cũng là mã màu mà ColorRenderer dùng,
// nên mỗi khối tự mang màu của nó.
const char Blocks::SHAPES[TYPE_COUNT][SIZE][SIZE] = {
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

Blocks::Blocks(int type, int startX, int startY)
{
    // Loại khối sai thì lấy khối I, đối tượng luôn hợp lệ ngay khi tạo ra
    if (type < 0 || type >= TYPE_COUNT)
        type = TYPE_I;

    posX = startX;
    posY = startY;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            shape[i][j] = SHAPES[type][i][j];
}

bool Blocks::isInside(int row, int col)
{
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

char Blocks::at(int row, int col) const
{
    if (!isInside(row, col))
        return ' ';
    return shape[row][col];
}

void Blocks::setPosition(int newX, int newY)
{
    posX = newX;
    posY = newY;
}

void Blocks::move(int dx, int dy)
{
    posX += dx;
    posY += dy;
}

void Blocks::turnClockwise()
{
    char turned[SIZE][SIZE];

    // Xoay 90 độ theo chiều kim đồng hồ trong ô vuông 4x4
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            turned[i][j] = shape[SIZE - 1 - j][i];

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            shape[i][j] = turned[i][j];
}

char Blocks::shapeAt(int type, int row, int col)
{
    if (type < 0 || type >= TYPE_COUNT || !isInside(row, col))
        return ' ';
    return SHAPES[type][row][col];
}
