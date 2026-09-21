#include "Tetromino.h"

// Bảng hình dạng 7 khối chuẩn. Chữ cái cũng là mã màu mà ColorRenderer dùng,
// nên mỗi khối tự mang màu của nó. Bảng để riêng tư nên chỉ lớp này đọc được.
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
    // Hàm thiết lập tự kiểm tra dữ liệu: loại khối sai thì đưa về 0, nên đối
    // tượng luôn ở trạng thái hợp lệ ngay khi vừa tạo ra
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

    // Xoay 90 độ theo chiều kim đồng hồ trong ô vuông 4x4
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
