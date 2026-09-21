#include "Game.h"

#include "ColorRenderer.h"
#include "Platform.h"

#include <iostream>

using namespace std;

Game::Game()
{
    holdType = -1;
    canHold = true;
    running = true;
    over = false;

    board.reset();
    fillQueue();
    spawn();
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
    board.erase(current);

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
    // Nhấc khối ra khỏi bàn cờ để tính bóng mờ, xong đặt lại chỗ cũ
    board.erase(current);
    int ghost = ghostRow();
    board.place(current);

    renderer.draw(board, current, ghost, holdType, nextQueue, speed);
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
        board.erase(current);

        Action action = input.poll();

        switch (action)
        {
        case ACTION_LEFT:      moveLeft();    break;
        case ACTION_RIGHT:     moveRight();   break;
        case ACTION_SOFT_DROP: softDrop();    break;
        case ACTION_ROTATE:    rotatePiece(); break;
        case ACTION_HOLD:      hold();        break;
        case ACTION_HARD_DROP: hardDrop();    break;
        case ACTION_QUIT:      running = false; break;
        default: break;
        }

        if (!running)
            break;

        applyGravity();

        if (over)
        {
            drawPlayfield();
            renderer.showMessage(18, 10, "   GAME OVER!   ", COLOR_RED, COLOR_WHITE);
            break;
        }

        board.place(current);
        drawPlayfield();

        Sleep(speed.getDropInterval());
    }

    ColorRenderer::gotoxy(0, 23);
    cout << "\nNhan phim bat ky de thoat...";
    getch();
}
