#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "Blocks.h"
#include "Board.h"
#include "ColorRenderer.h"
#include "DropSpeedController.h"

/**
 * @brief Lớp lo toàn bộ việc vẽ màn hình: sân chơi và các khung thông tin.
 *
 * TÍNH TRỪU TƯỢNG: phần còn lại của game chỉ gọi draw() và các hàm show...(),
 * không cần biết vẽ bằng ký tự gì, màu gì, đặt con trỏ ra sao.
 *
 * TÍNH HỢP THÀNH: Renderer sở hữu một ColorRenderer (cửa sổ console). Mọi lệnh vẽ
 * ghi vào bộ đệm của nó, cuối mỗi hàm mới đẩy ra màn hình một lần.
 *
 * Các tham số đều là tham chiếu const: Renderer chỉ đọc để vẽ, không sửa bàn cờ
 * hay khối của người chơi.
 */
class Renderer
{
public:
    void draw(const Board &board, const Blocks &current, int ghostY, int holdBlock,
              const int nextQueue[], const DropSpeedController &stats, int bestScore);

    // In một dòng chữ tại vị trí bất kỳ
    void showMessage(int x, int y, const std::string &text, int textColor, int bgColor = 0);

    // Hai khung hiện đè lên sân chơi khi tạm dừng và khi thua
    void showPauseModal();
    void showGameOverModal(int score);

private:
    ColorRenderer console;

    // Mỗi dòng của sân chơi đi kèm một dòng của bảng trái và một dòng của bảng phải
    void drawLeftPanel(int row, int holdBlock, const DropSpeedController &stats);
    void drawRightPanel(int row, int nextBlock, int bestScore, const DropSpeedController &stats);

    // Các loại dòng dùng chung cho mọi khung; leftSide thêm khoảng cách phía sân chơi
    void panelBorder(bool leftSide);
    void panelTitle(const char *title, int color, bool leftSide);
    void panelValue(const std::string &value, int color, bool leftSide);
    void panelPieceRow(int blockType, int pieceRow, bool leftSide);
    void panelEmpty(bool leftSide);
};

#endif // RENDERER_H
