#ifndef BAG7_H
#define BAG7_H

#include "Tetromino.h"

/**
 * @brief Cách random chuẩn của Tetris: một túi chứa đủ bảy loại khối.
 *
 * rand() % 7 có thể cho ra cùng một khối năm lần liên tiếp, và cũng có thể giấu
 * một loại khối rất lâu không ra. Túi này xáo đủ bảy loại, phát lần lượt từng
 * khối, hết túi mới xáo lại. Nhờ vậy cứ bảy khối liên tiếp là có đủ bảy loại,
 * mỗi loại đúng một lần.
 *
 * TÍNH ĐÓNG GÓI: mảng pieces và vị trí đang phát đều riêng tư. Bên ngoài chỉ gọi
 * next() để xin khối kế tiếp, không cần biết túi xáo kiểu gì.
 */
class Bag7
{
public:
    Bag7();

    int next();                          // loại khối kế tiếp
    int remaining() const { return Tetromino::TYPE_COUNT - position; }

private:
    int pieces[Tetromino::TYPE_COUNT];   // bảy loại khối đã xáo
    int position;                        // vị trí khối sắp phát

    void refill();                       // bỏ lại đủ bảy loại rồi xáo
};

#endif // BAG7_H
