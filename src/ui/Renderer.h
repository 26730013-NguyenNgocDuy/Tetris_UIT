#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "Board.h"
#include "DropSpeedController.h"
#include "Blocks.h"

/**
 * @brief Lớp lo toàn bộ việc vẽ màn hình: sân chơi và ba khung thông tin.
 *
 * TÍNH TRỪU TƯỢNG: phần còn lại của game chỉ gọi draw() và showMessage(), không
 * cần biết vẽ bằng ký tự gì, màu gì, đặt con trỏ ra sao. Muốn đổi cách vẽ sau này
 * (ví dụ dùng màu RGB 24-bit) thì chỉ sửa trong lớp này.
 *
 * Các tham số đều là tham chiếu const: Renderer chỉ đọc để vẽ, không sửa bàn cờ
 * hay khối của người chơi.
 */
class Renderer
{
public:
    Renderer();   // chuẩn bị console: ẩn con trỏ, xoá màn hình

    void draw(const Board &board, const Blocks &current, int ghostY,
              int holdBlock, const int nextQueue[], const DropSpeedController &stats);

    // In một dòng chữ tại vị trí bất kỳ
    void showMessage(int x, int y, const std::string &text, int textColor, int bgColor = 0);

    // Hai khung hiện đè lên sân chơi khi tạm dừng và khi thua
    void showPauseModal();
    void showGameOverModal(int score);
};

#endif // RENDERER_H
