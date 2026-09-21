#ifndef BOARD_H
#define BOARD_H

#include "Blocks.h"

/**
 * @brief Sân chơi: phần tường bao quanh và mọi ô gạch đã nằm yên.
 *
 * TÍNH ĐÓNG GÓI: mảng grid để riêng tư. Trước khi refactor, mọi hàm trong
 * main.cpp đều ghi thẳng vào mảng board[H][W], sai một chỗ là hỏng cả bàn cờ mà
 * rất khó tìm. Nay muốn đọc phải gọi at(), muốn ghi phải gọi set(), và set() tự
 * bỏ qua toạ độ nằm ngoài lưới nên không ghi tràn được.
 *
 * TÍNH TRỪU TƯỢNG: bên ngoài chỉ hỏi "khối này đặt vừa không" qua canPlace(),
 * "hàng này đầy chưa" qua isRowFull(), mà không cần biết lưới lưu kiểu gì.
 */
class Board
{
public:
    // Hằng số của lớp, thay cho #define H 20 và #define W 12 ở code cũ.
    // Kích thước thuộc về bàn cờ nên đặt ngay trong lớp bàn cờ.
    static const int ROWS = 20;
    static const int COLS = 12;
    static const char WALL = '#';    // ký tự tường
    static const char EMPTY = ' ';   // ký tự ô trống

    Board();

    // Dựng lại tường bao quanh, bên trong để trống
    void reset();

    // Các hàm chỉ đọc đều là const
    char at(int row, int col) const;
    bool isEmpty(int row, int col) const { return at(row, col) == EMPTY; }
    void set(int row, int col, char value);

    // Khối dịch đi (dx, dy) thì có còn nằm trong tường và không chạm ô đã có
    // gạch hay không
    bool canPlace(const Blocks &piece, int dx, int dy) const;

    // Ghi khối vào lưới, hoặc xoá các ô mà khối đang chiếm
    void place(const Blocks &piece);
    void erase(const Blocks &piece);

    // Xoá hàng tách làm hai bước để bên gọi chèn được hiệu ứng nháy ở giữa
    bool isRowFull(int row) const;
    void removeRow(int row);

private:
    char grid[ROWS][COLS];

    static bool isInside(int row, int col);
};

#endif // BOARD_H
