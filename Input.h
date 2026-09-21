#ifndef INPUT_H
#define INPUT_H

/**
 * @brief Các hành động người chơi có thể ra lệnh.
 *
 * Nhờ kiểu liệt kê này, phần xử lý game nói theo ý nghĩa (ACTION_ROTATE) chứ
 * không so sánh ký tự ('w') nữa. Muốn đổi phím, hoặc thêm phím mũi tên, chỉ sửa
 * trong lớp Input, phần còn lại của game không phải sửa dòng nào.
 */
enum Action
{
    ACTION_NONE,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_SOFT_DROP,
    ACTION_ROTATE,
    ACTION_HOLD,
    ACTION_HARD_DROP,
    ACTION_PAUSE,
    ACTION_RESTART,
    ACTION_QUIT
};

/**
 * @brief Lớp đọc bàn phím.
 *
 * TÍNH TRỪU TƯỢNG: bên ngoài chỉ gọi poll() và nhận về một hành động, không cần
 * biết bàn phím được đọc bằng kbhit() hay cách nào khác.
 */
class Input
{
public:
    // Không có phím nào đang bấm thì trả về ACTION_NONE, không chờ người chơi
    Action poll();
};

#endif // INPUT_H
