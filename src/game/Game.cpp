#include "Game.h"

#include "BlockTypes.h"
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
    current = 0;
    dropTimer = 0;
    changed = true;

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
    delete current;
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

    // Xoá khối cũ rồi tạo khối mới đúng lớp con tương ứng với loại
    delete current;
    current = createBlock(type, 4, 0);
    canHold = true;
}

int Game::ghostRow() const
{
    // Thả thử khối xuống tới khi không xuống được nữa
    int row = current->getY();
    while (board.canPlace(*current, 0, row - current->getY() + 1))
        row++;
    return row;
}

void Game::moveLeft()
{
    if (canMove(-1, 0))
    {
        current->move(-1, 0);
        changed = true;
    }
}

void Game::moveRight()
{
    if (canMove(1, 0))
    {
        current->move(1, 0);
        changed = true;
    }
}

void Game::softDrop()
{
    // Chỉ cộng điểm khi xoá được hàng, nên rơi nhanh không được cộng điểm
    if (canMove(0, 1))
    {
        current->move(0, 1);
        dropTimer = 0;
        changed = true;
    }
}

void Game::rotatePiece()
{
    // ĐA HÌNH: clone() trả về bản sao đúng loại khối, rotate() xoay theo kiểu
    // riêng của loại đó. Chỗ này không cần biết đang cầm khối gì.
    Blocks *turned = current->clone();
    turned->rotate();

    int kick[5] = {0, -1, 1, -2, 2};

    for (int k = 0; k < 5; k++)
    {
        if (board.canPlace(*turned, kick[k], 0))
        {
            turned->move(kick[k], 0);
            delete current;          // nhận bản đã xoay, bỏ bản cũ
            current = turned;
            changed = true;
            return;
        }
    }

    delete turned;                   // không chỗ nào đặt vừa thì bỏ bản sao
}

void Game::hold()
{
    if (!canHold)
        return;

    if (holdType == -1)
    {
        holdType = current->getType();
        spawn();
    }
    else
    {
        int keep = holdType;
        holdType = current->getType();
        spawn(keep);
    }

    // Đặt sau spawn(), vì spawn() bật lại canHold cho khối mới. Nếu đặt trước
    // thì mỗi khối giữ được bao nhiêu lần cũng được, sai luật.
    canHold = false;
    changed = true;
}

void Game::hardDrop()
{
    while (canMove(0, 1))
        current->move(0, 1);

    // Đồng hồ rơi đầy ngay, nên nhịp kế tiếp khối được chốt lại
    dropTimer = speed.getDropInterval();
    changed = true;
}

void Game::tick()
{
    dropTimer += TICK_MS;
    if (dropTimer >= speed.getDropInterval())
    {
        dropTimer = 0;
        applyGravity();
        changed = true;
    }
}

void Game::drawIfChanged()
{
    if (!changed)
        return;
    drawPlayfield();
    changed = false;
}

void Game::saveHighScore()
{
    ColorRenderer::setHighScore(speed.getScore());
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
            Sleep(80);
        }
    }

    return cleared;
}

void Game::applyGravity()
{
    if (canMove(0, 1))
    {
        current->move(0, 1);
        return;
    }

    // Chạm đáy: chốt khối vào bàn cờ, xoá hàng đầy, tính điểm
    board.place(*current);

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
    renderer.draw(board, *current, ghostRow(), holdType, nextQueue, speed);
}

void Game::restart()
{
    board.reset();
    speed.reset();
    holdType = -1;
    canHold = true;
    over = false;
    dropTimer = 0;
    changed = true;
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

    saveHighScore();
    ColorRenderer::gotoxy(0, 26);
    cout << "\nCam on ban da trai nghiem Tetris Pro Max!\n";
}
