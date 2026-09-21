#include "Game.h"

#include "ColorRenderer.h"
#include "GameState.h"
#include "Platform.h"

#include <iostream>

using namespace std;

Game::Game()
{
    holdType = -1;
    canHold = true;
    running = true;
    over = false;
    pending = 0;

    board.reset();
    fillQueue();
    spawn();

    // Ván mới bắt đầu ở trạng thái đang chơi
    state = new PlayingState(this);
}

Game::~Game()
{
    // Game sở hữu trạng thái nên phải tự dọn. Hàm huỷ của GameState là hàm ảo
    // nên lệnh delete này gọi đúng hàm huỷ của lớp con.
    delete state;
    delete pending;
}

void Game::setState(GameState *newState)
{
    delete pending;        // phòng trường hợp đổi trạng thái hai lần trong một nhịp
    pending = newState;
}

void Game::fillQueue()
{
    for (int i = 0; i < 4; i++)
        nextQueue[i] = bag.next();
}

void Game::spawn(int type)
{
    if (type == -1)
    {
        // Lấy khối đầu hàng đợi, dồn ba khối còn lại lên, bổ sung khối mới từ túi
        type = nextQueue[0];
        for (int i = 0; i < 3; i++)
            nextQueue[i] = nextQueue[i + 1];
        nextQueue[3] = bag.next();
    }

    current = Tetromino(type, 4, 0);
    canHold = true;
}

int Game::ghostRow() const
{
    // Thả thử khối xuống tới khi không xuống được nữa
    int row = current.getY();
    while (board.canPlace(current, 0, row - current.getY() + 1))
        row++;
    return row;
}

void Game::moveLeft()
{
    if (canMove(-1, 0))
        current.move(-1, 0);
}

void Game::moveRight()
{
    if (canMove(1, 0))
        current.move(1, 0);
}

void Game::softDrop()
{
    if (canMove(0, 1))
    {
        current.move(0, 1);
        speed.addDropScore(1);
    }
}

void Game::rotatePiece()
{
    // Xoay trên bản sao, thử lệch sang hai bên khi khối đang sát tường
    Tetromino turned = current.rotated();
    int kick[5] = {0, -1, 1, -2, 2};

    for (int k = 0; k < 5; k++)
    {
        if (board.canPlace(turned, kick[k], 0))
        {
            turned.move(kick[k], 0);
            current = turned;
            return;
        }
    }
}

void Game::hold()
{
    if (!canHold)
        return;

    canHold = false;

    if (holdType == -1)
    {
        holdType = current.getType();
        spawn();
    }
    else
    {
        int keep = holdType;
        holdType = current.getType();
        spawn(keep);
    }
}

void Game::hardDrop()
{
    int distance = 0;
    while (canMove(0, 1))
    {
        current.move(0, 1);
        distance++;
    }
    speed.addDropScore(distance * 2);
}

int Game::clearFullRows()
{
    int cleared = 0;

    for (int row = Board::ROWS - 2; row > 0; row--)
    {
        if (board.isRowFull(row))
        {
            cleared++;
            board.removeRow(row);

            // Xét lại chính dòng này vì dòng trên vừa rơi xuống
            row++;

            drawPlayfield();
            Sleep(120);
        }
    }

    return cleared;
}

void Game::applyGravity()
{
    if (canMove(0, 1))
    {
        current.move(0, 1);
        return;
    }

    // Chạm đáy: chốt khối vào bàn cờ, xoá hàng đầy, tính điểm
    board.place(current);

    int cleared = clearFullRows();
    if (cleared > 0)
        speed.onLinesCleared(cleared);
    else
        speed.resetCombo();

    spawn();

    // Khối mới không có chỗ đặt nghĩa là thua
    if (!canMove(0, 0))
        over = true;
}

void Game::drawPlayfield()
{
    // Khối đang rơi KHÔNG nằm trong bàn cờ, nó chỉ được vẽ đè lên khi hiển thị.
    // Nhờ vậy tính bóng mờ không bị khối va vào chính nó, và lúc thua cũng không
    // xoá nhầm gạch cũ ở chỗ khối mới đè lên.
    renderer.draw(board, current, ghostRow(), holdType, nextQueue, speed);
}

void Game::restart()
{
    board.reset();
    speed.reset();
    holdType = -1;
    canHold = true;
    over = false;
    fillQueue();
    spawn();
}

void Game::run()
{
    while (running)
    {
        // ĐA HÌNH: ba lệnh dưới đây giống nhau ở mọi trạng thái, nhưng chạy ra
        // việc khác nhau tuỳ đang chơi, đang tạm dừng hay đã thua
        state->handle(input.poll());
        state->update();

        if (running)
            state->draw();

        int nhip = state->tickMs();

        // Hết nhịp mới đổi trạng thái, lúc này không còn ai đang dùng trạng thái cũ
        if (pending != 0)
        {
            delete state;
            state = pending;
            pending = 0;
        }

        if (running)
            Sleep(nhip);
    }

    ColorRenderer::gotoxy(0, 23);
    cout << "\nNhan phim bat ky de thoat...";
    getch();
}
