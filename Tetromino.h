#ifndef TETROMINO_H
#define TETROMINO_H

/**
 * @brief Một khối đang rơi: hình dạng, loại khối và vị trí trên bàn cờ.
 *
 * TÍNH ĐÓNG GÓI: mảng shape để ở phần riêng tư (private). Các file khác muốn biết
 * ô nào có gạch thì gọi isFilled() hoặc at(), không ai ghi thẳng vào mảng được,
 * nên hình khối không bao giờ bị sửa sai từ bên ngoài.
 *
 * Trước khi refactor, một khối bị xé thành 4 biến toàn cục rời nhau:
 * cur (hình dạng), x và y (vị trí), b (loại khối). Nay gom vào một đối tượng.
 */
class Tetromino
{
public:
    static const int SIZE = 4;         // khối nằm trong ô vuông 4x4
    static const int TYPE_COUNT = 7;   // 7 loại khối chuẩn: I O T S Z J L

    // Hàm thiết lập có tham số mặc định, tạo khối loại pieceType tại (startX, startY)
    explicit Tetromino(int pieceType = 0, int startX = 4, int startY = 0);

    // Các hàm lấy thông tin đều là const: chỉ đọc, không sửa đối tượng
    int getType() const { return type; }
    int getX() const { return posX; }
    int getY() const { return posY; }

    char at(int row, int col) const;
    bool isFilled(int row, int col) const { return at(row, col) != ' '; }

    void setPosition(int newX, int newY);
    void move(int dx, int dy);

    // Trả về một BẢN SAO đã xoay, khối gốc giữ nguyên. Nhờ vậy bên gọi thử đặt
    // bản sao vào bàn cờ, vừa thì mới nhận, không vừa thì bỏ đi mà không cần
    // lưu lại trạng thái cũ để hoàn tác như code cũ.
    Tetromino rotated() const;

    // Hàm static: gọi bằng Tetromino::shapeAt(...) mà không cần tạo đối tượng.
    // Dùng để vẽ khung GIỮ và TIẾP THEO, nơi chưa có khối thật nào đang rơi.
    static char shapeAt(int pieceType, int row, int col);

private:
    char shape[4][4];   // ' ' là ô trống, còn lại là chữ cái của khối
    int type;           // 0..6, số thứ tự trong bảng hình dạng
    int posX, posY;     // góc trên trái của ô vuông 4x4 trên bàn cờ

    static bool isInside(int row, int col);
    static const char SHAPES[TYPE_COUNT][SIZE][SIZE];
};

#endif // TETROMINO_H
