#include "Bag7.h"

#include <cstdlib>

Bag7::Bag7()
{
    // Cố ý để túi rỗng lúc đầu. Biến toàn cục được tạo TRƯỚC khi main() chạy,
    // mà srand() lại gọi bên trong main(), nên nếu xáo ngay ở đây thì ván nào
    // cũng ra dãy khối giống hệt nhau. Để rỗng thì lần gọi next() đầu tiên mới xáo.
    position = Tetromino::TYPE_COUNT;
}

void Bag7::refill()
{
    for (int i = 0; i < Tetromino::TYPE_COUNT; i++)
        pieces[i] = i;

    // Xáo bài kiểu Fisher-Yates: đi từ cuối về đầu, mỗi bước đổi chỗ phần tử
    // đang xét với một phần tử ngẫu nhiên đứng trước nó
    for (int i = Tetromino::TYPE_COUNT - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int keep = pieces[i];
        pieces[i] = pieces[j];
        pieces[j] = keep;
    }

    position = 0;
}

int Bag7::next()
{
    // Hết túi thì xáo lại, nên người chơi luôn có khối để nhận
    if (position >= Tetromino::TYPE_COUNT)
        refill();

    return pieces[position++];
}
