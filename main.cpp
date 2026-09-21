#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include "Platform.h"
#include "DropSpeedController.h"
#include "ColorRenderer.h"
#include "Tetromino.h"
#include "Board.h"
#include "Bag7.h"
#include "Renderer.h"
#include "Input.h"

using namespace std;

// Kích thước lấy từ hằng số của lớp Board, không dùng #define nữa
const int H = Board::ROWS;
const int W = Board::COLS;

// Bàn cờ chính 20x12 (với 2 cột viền và 10 cột trong sân chơi chuẩn Tetris)
Board board;

// Khối đang rơi: hình dạng, loại và vị trí đều nằm trong đối tượng này
Tetromino current;
int holdBlock = -1;
bool canHold = true;
int nextQueue[4];

// Nguồn phát khối: mỗi túi có đủ 7 loại nên không bị trùng liên tục như rand() % 7
Bag7 bag;

bool canMove(int dx, int dy, const Tetromino &piece)
{
    return board.canPlace(piece, dx, dy);
}

bool canMove(int dx, int dy)
{
    return board.canPlace(current, dx, dy);
}

void rotate()
{
    // Xoay trên một bản sao, chỉ nhận khi bản sao đặt vừa vào bàn cờ
    Tetromino turned = current.rotated();

    // Wall kick: thử các độ lệch 0, -1, 1, -2, 2
    int kick[5] = {0, -1, 1, -2, 2};
    for (int k = 0; k < 5; k++)
    {
        if (canMove(kick[k], 0, turned))
        {
            turned.move(kick[k], 0);
            current = turned;
            return;
        }
    }
}

int getGhostY()
{
    int gy = current.getY();
    while (canMove(0, gy - current.getY() + 1))
    {
        gy++;
    }
    return gy;
}

void initQueue()
{
    for (int i = 0; i < 4; i++)
    {
        nextQueue[i] = bag.next();
    }
}

void spawn(int blockId = -1)
{
    int type;
    if (blockId == -1)
    {
        type = nextQueue[0];
        for (int i = 0; i < 3; i++)
        {
            nextQueue[i] = nextQueue[i + 1];
        }
        nextQueue[3] = bag.next();
    }
    else
    {
        type = blockId;
    }

    current = Tetromino(type, 4, 0);
    canHold = true;
}

void holdPiece()
{
    if (!canHold) return;
    canHold = false;
    board.erase(current);
    if (holdBlock == -1)
    {
        holdBlock = current.getType();
        spawn(-1);
    }
    else
    {
        int temp = holdBlock;
        holdBlock = current.getType();
        spawn(temp);
    }
}

DropSpeedController speedController;

// Hàm vẽ toàn bộ UI chuẩn báo cáo 3.3
Renderer renderer;
Input input;

// Ve man hinh: tinh vi tri bong khoi roi roi giao cho Renderer
void draw()
{
    renderer.draw(board, current, getGhostY(), holdBlock, nextQueue, speedController);
}

int removeLine()
{
    int clearedCount = 0;

    for (int i = H - 2; i > 0; i--)
    {
        if (board.isRowFull(i))
        {
            clearedCount++;
            board.removeRow(i);

            // Kiểm tra lại dòng hiện tại vì dòng trên vừa rơi xuống
            i++;

            draw();
            Sleep(120);
        }
    }

    return clearedCount;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    ColorRenderer::setupConsole();

    board.reset();
    initQueue();
    spawn(-1);

    while (1)
    {
        board.erase(current);

        // Đọc phím qua lớp Input: nhận về hành động chứ không phải ký tự
        Action action = input.poll();

        if (action == ACTION_LEFT && canMove(-1, 0))
            current.move(-1, 0);

        if (action == ACTION_RIGHT && canMove(1, 0))
            current.move(1, 0);

        if (action == ACTION_SOFT_DROP && canMove(0, 1))
        {
            current.move(0, 1);
            speedController.addDropScore(1);
        }

        if (action == ACTION_ROTATE)
            rotate();

        if (action == ACTION_HOLD)
            holdPiece();

        if (action == ACTION_HARD_DROP)
        {
            int dropDist = 0;
            while (canMove(0, 1))
            {
                current.move(0, 1);
                dropDist++;
            }
            speedController.addDropScore(dropDist * 2);
        }

        if (action == ACTION_QUIT)
            break;

        if (canMove(0, 1))
        {
            current.move(0, 1);
        }
        else
        {
            // Block đã chạm đáy
            board.place(current);

            // Xóa line
            int cleared = removeLine();

            // Tăng tốc độ nếu có line bị xóa, hoặc reset combo nếu không ăn line
            if (cleared > 0)
                speedController.onLinesCleared(cleared);
            else
                speedController.resetCombo();

            // Spawn block mới
            spawn(-1);

            // Kiểm tra GameOver
            if (!canMove(0, 0))
            {
                draw();
                ColorRenderer::gotoxy(18, 10);
                ColorRenderer::setColor(COLOR_RED, COLOR_WHITE);
                cout << "   GAME OVER!   ";
                ColorRenderer::resetColor();
                break;
            }
        }

        board.place(current);

        draw();

        Sleep(speedController.getDropInterval());
    }

    ColorRenderer::gotoxy(0, 23);
    cout << "\nNhan phim bat ky de thoat...";
    getch();

    return 0;
}