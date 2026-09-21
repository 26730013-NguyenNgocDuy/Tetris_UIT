#ifndef BLOCK_TYPES_H
#define BLOCK_TYPES_H

#include "Blocks.h"

/**
 * @brief Bảy loại khối, mỗi loại là một lớp con của Blocks.
 *
 * ĐA HÌNH: cùng một lệnh piece->rotate() nhưng chạy ra ba kiểu khác nhau:
 *   - BlockO không đổi gì (hình vuông xoay vẫn thế),
 *   - BlockI đổi qua lại giữa nằm ngang và dựng đứng,
 *   - năm loại còn lại xoay 90 độ, đủ bốn trạng thái.
 *
 * Nơi gọi chỉ cầm con trỏ Blocks*, không cần biết đang là khối gì.
 */

// Khối I: chỉ có hai trạng thái. Xoay hai lần phải về đúng hình ban đầu, nên
// không dùng phép xoay 90 độ chung được.
class BlockI : public Blocks
{
    bool vertical;

public:
    BlockI(int x = 4, int y = 0) : Blocks(TYPE_I, x, y), vertical(false) { }

    void rotate();
    Blocks *clone() const { return new BlockI(*this); }
    int getType() const { return TYPE_I; }
};

// Khối O là hình vuông: xoay không làm gì cả
class BlockO : public Blocks
{
public:
    BlockO(int x = 4, int y = 0) : Blocks(TYPE_O, x, y) { }

    void rotate() { }
    Blocks *clone() const { return new BlockO(*this); }
    int getType() const { return TYPE_O; }
};

class BlockT : public Blocks
{
public:
    BlockT(int x = 4, int y = 0) : Blocks(TYPE_T, x, y) { }

    void rotate() { turnClockwise(); }
    Blocks *clone() const { return new BlockT(*this); }
    int getType() const { return TYPE_T; }
};

class BlockS : public Blocks
{
public:
    BlockS(int x = 4, int y = 0) : Blocks(TYPE_S, x, y) { }

    void rotate() { turnClockwise(); }
    Blocks *clone() const { return new BlockS(*this); }
    int getType() const { return TYPE_S; }
};

class BlockZ : public Blocks
{
public:
    BlockZ(int x = 4, int y = 0) : Blocks(TYPE_Z, x, y) { }

    void rotate() { turnClockwise(); }
    Blocks *clone() const { return new BlockZ(*this); }
    int getType() const { return TYPE_Z; }
};

class BlockJ : public Blocks
{
public:
    BlockJ(int x = 4, int y = 0) : Blocks(TYPE_J, x, y) { }

    void rotate() { turnClockwise(); }
    Blocks *clone() const { return new BlockJ(*this); }
    int getType() const { return TYPE_J; }
};

class BlockL : public Blocks
{
public:
    BlockL(int x = 4, int y = 0) : Blocks(TYPE_L, x, y) { }

    void rotate() { turnClockwise(); }
    Blocks *clone() const { return new BlockL(*this); }
    int getType() const { return TYPE_L; }
};

// Tạo khối theo số thứ tự loại. Đây là chỗ duy nhất trong game biết bảy lớp con,
// mọi nơi khác chỉ làm việc với con trỏ Blocks*.
Blocks *createBlock(int type, int x = 4, int y = 0);

#endif // BLOCK_TYPES_H
