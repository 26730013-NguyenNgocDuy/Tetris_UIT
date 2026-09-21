#ifndef BLOCKS_H
#define BLOCKS_H

/**
 * @brief Lớp cơ sở TRỪU TƯỢNG cho một khối Tetris.
 *
 * Đề bài tuần 3 yêu cầu đổi struct Blocks { char shape[4][4]; } thành lớp và
 * dùng ĐA HÌNH để xoay. Mỗi loại khối xoay một kiểu khác nhau:
 *   - khối O là hình vuông, xoay thì vẫn y như cũ,
 *   - khối I chỉ có hai trạng thái: nằm ngang và dựng đứng,
 *   - năm khối còn lại có bốn trạng thái, xoay 90 độ mỗi lần.
 *
 * rotate() và clone() là THUẦN ẢO nên không tạo được đối tượng Blocks, chỉ tạo
 * được lớp con. Hàm huỷ bỏ là hàm ẢO vì Game giữ con trỏ Blocks* trỏ tới lớp con.
 */
class Blocks
{
public:
    static const int SIZE = 4;
    static const int TYPE_COUNT = 7;

    // Số thứ tự của từng loại, giữ đúng thứ tự cũ để Bag7 và bảng màu không đổi
    static const int TYPE_I = 0;
    static const int TYPE_O = 1;
    static const int TYPE_T = 2;
    static const int TYPE_S = 3;
    static const int TYPE_Z = 4;
    static const int TYPE_J = 5;
    static const int TYPE_L = 6;

    virtual ~Blocks() { }

    // Mỗi lớp con tự định nghĩa cách xoay của mình
    virtual void rotate() = 0;

    // Tạo bản sao đúng kiểu thật của khối. Nhờ hàm này, bên gọi xoay thử trên
    // bản sao rồi mới quyết định giữ hay bỏ, mà không cần biết đó là khối gì.
    virtual Blocks *clone() const = 0;

    virtual int getType() const = 0;

    int getX() const { return posX; }
    int getY() const { return posY; }
    char at(int row, int col) const;
    bool isFilled(int row, int col) const { return at(row, col) != ' '; }

    void setPosition(int newX, int newY);
    void move(int dx, int dy);

    // Hình dạng gốc của một loại khối, dùng để vẽ khung GIỮ và TIẾP THEO
    static char shapeAt(int type, int row, int col);

protected:
    char shape[SIZE][SIZE];   // ' ' là ô trống, còn lại là chữ cái của khối
    int posX, posY;           // góc trên trái của ô vuông 4x4 trên bàn cờ

    // Lớp con gọi hàm này để lấy hình dạng gốc theo loại khối
    Blocks(int type, int startX, int startY);

    // Phép xoay 90 độ dùng chung, lớp con nào cần thì gọi lại
    void turnClockwise();

    static bool isInside(int row, int col);
    static const char SHAPES[TYPE_COUNT][SIZE][SIZE];
};

#endif // BLOCKS_H
