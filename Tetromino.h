#ifndef TETROMINO_H
#define TETROMINO_H

/**
 * @brief One falling piece: its shape, its type and its position on the board.
 *
 * The shape is kept private. Other classes read it through isFilled() and at(),
 * so nobody can change a piece by writing into the array directly.
 */
class Tetromino
{
    char shape[4][4];       // ' ' = empty cell, otherwise the piece letter
    int type;               // 0..6, index in the shape table
    int posX, posY;         // top left corner of the 4x4 box on the board

public:
    static const int SIZE = 4;
    static const int TYPE_COUNT = 7;

    explicit Tetromino(int pieceType = 0, int startX = 4, int startY = 0);

    int getType() const { return type; }
    int getX() const { return posX; }
    int getY() const { return posY; }

    char at(int row, int col) const;
    bool isFilled(int row, int col) const { return at(row, col) != ' '; }

    void setPosition(int newX, int newY);
    void move(int dx, int dy);

    // Returns a rotated copy; the original piece is not changed, so the caller
    // can test the copy first and only keep it when it fits on the board.
    Tetromino rotated() const;

    // Shape of any type without creating a piece, used to draw HOLD and NEXT
    static char shapeAt(int pieceType, int row, int col);

private:
    static bool isInside(int row, int col);
    static const char SHAPES[TYPE_COUNT][SIZE][SIZE];
};

#endif // TETROMINO_H
