#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <string>

/**
 * @brief Điểm cao nhất, lưu trong file để lần sau mở game vẫn còn.
 *
 * Trước đây việc này nằm trong ColorRenderer (lớp lo màu sắc), và file được mở
 * ra đọc ở MỖI lần vẽ màn hình. Nay tách thành lớp riêng: chỉ đọc file một lần
 * khi tạo đối tượng, sau đó giữ điểm trong bộ nhớ.
 */
class HighScore
{
public:
    explicit HighScore(const std::string &file = "highscore.dat");

    int getBest() const { return best; }

    // Điểm mới cao hơn kỷ lục thì cập nhật và ghi ra file
    void submit(int score);

private:
    std::string fileName;
    int best;
};

#endif // HIGH_SCORE_H
