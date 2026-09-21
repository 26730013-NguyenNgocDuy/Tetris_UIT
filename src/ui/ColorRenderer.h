#ifndef COLOR_RENDERER_H
#define COLOR_RENDERER_H

#include <ostream>
#include <sstream>

/**
 * @brief Bảng màu 16 màu của console (giữ số thứ tự như Windows Console)
 */
enum ConsoleColor {
    COLOR_BLACK         = 0,
    COLOR_DARK_BLUE     = 1,
    COLOR_DARK_GREEN    = 2,
    COLOR_DARK_CYAN     = 3,
    COLOR_DARK_RED      = 4,
    COLOR_DARK_MAGENTA  = 5,
    COLOR_DARK_YELLOW   = 6,
    COLOR_GRAY          = 7,
    COLOR_DARK_GRAY     = 8,
    COLOR_BLUE          = 9,
    COLOR_GREEN         = 10,
    COLOR_CYAN          = 11,
    COLOR_RED           = 12,
    COLOR_MAGENTA       = 13,
    COLOR_YELLOW        = 14,
    COLOR_WHITE         = 15
};

/**
 * @brief Đối tượng giữ cửa sổ console: màu, vị trí con trỏ và một khung hình đệm.
 *
 * Trước đây mọi hàm đều static và mỗi lần đổi màu là một lần gọi Windows API,
 * nên một lần vẽ màn hình mất khoảng 26 ms (hàng trăm lần gọi lẻ). Nay mọi lệnh
 * vẽ chỉ ghi vào bộ đệm frame dưới dạng mã ANSI, rồi flush() đẩy cả khung hình
 * ra màn hình trong MỘT lần ghi. Cách này chạy giống nhau trên Windows 10+,
 * macOS và Linux nên không còn phải viết hai phiên bản như trước.
 *
 * TÍNH ĐÓNG GÓI: bộ đệm là dữ liệu riêng tư; bên ngoài chỉ gọi setColor(),
 * gotoxy(), printCell(), out() và flush().
 */
class ColorRenderer
{
public:
    ColorRenderer();    // bật chế độ màu ANSI, UTF-8, ẩn con trỏ, xoá màn hình
    ~ColorRenderer();   // trả lại màu mặc định và hiện lại con trỏ

    void setColor(int textColor, int bgColor = COLOR_BLACK);
    void resetColor();
    void gotoxy(int x, int y);

    // In một ô 2 ký tự: gạch, tường, bóng mờ, hoặc ô trống có chấm lưới
    void printCell(char ch, bool isPlayfield = false);

    // Luồng ghi chữ vào khung hình, dùng như cout: console.out() << "abc";
    std::ostream &out() { return frame; }

    // Đẩy toàn bộ khung hình ra màn hình trong một lần ghi, rồi làm rỗng bộ đệm
    void flush();

    // Màu chuẩn của từng loại khối, không phụ thuộc đối tượng nào
    static int getCharColor(char ch);

private:
    std::ostringstream frame;

    // Chỉ có một cửa sổ console, không cho sao chép đối tượng này
    ColorRenderer(const ColorRenderer &);
    void operator = (const ColorRenderer &);
};

#endif // COLOR_RENDERER_H
