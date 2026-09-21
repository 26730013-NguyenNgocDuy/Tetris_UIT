#include "GameState.h"

#include "ColorRenderer.h"
#include "Game.h"

// ---------------------------------------------------------------- Đang chơi
void PlayingState::handle(Action action)
{
    switch (action)
    {
    case ACTION_LEFT:      game->moveLeft();    break;
    case ACTION_RIGHT:     game->moveRight();   break;
    case ACTION_SOFT_DROP: game->softDrop();    break;
    case ACTION_ROTATE:    game->rotatePiece(); break;
    case ACTION_HOLD:      game->hold();        break;
    case ACTION_HARD_DROP: game->hardDrop();    break;
    case ACTION_PAUSE:     game->setState(new PausedState(game)); break;
    case ACTION_QUIT:      game->quit();        break;
    default: break;
    }
}

void PlayingState::update()
{
    game->applyGravity();

    // Khối mới không còn chỗ đặt thì chuyển sang trạng thái thua cuộc
    if (game->isOver())
        game->setState(new GameOverState(game));
}

void PlayingState::draw()
{
    game->drawPlayfield();
}

int PlayingState::tickMs() const
{
    return game->getDropInterval();
}

// ---------------------------------------------------------------- Tạm dừng
void PausedState::handle(Action action)
{
    if (action == ACTION_PAUSE)
        game->setState(new PlayingState(game));   // bấm P lần nữa để chơi tiếp

    if (action == ACTION_QUIT)
        game->quit();
}

void PausedState::update()
{
    // Tạm dừng thì không có gì thay đổi, khối đứng yên
}

void PausedState::draw()
{
    if (painted)
        return;

    game->drawPlayfield();
    game->getRenderer().showMessage(18, 10, "  TAM DUNG (P)  ", COLOR_BLACK, COLOR_YELLOW);
    painted = true;
}

// ---------------------------------------------------------------- Thua cuộc
void GameOverState::handle(Action action)
{
    if (action == ACTION_RESTART)
    {
        game->restart();
        game->setState(new PlayingState(game));
    }

    if (action == ACTION_QUIT)
        game->quit();
}

void GameOverState::update()
{
    // Đã thua thì khối không rơi nữa, chỉ chờ người chơi bấm R hoặc Q
}

void GameOverState::draw()
{
    if (painted)
        return;

    game->drawPlayfield();
    game->getRenderer().showMessage(18, 10, "   GAME OVER!   ", COLOR_RED, COLOR_WHITE);
    game->getRenderer().showMessage(14, 12, "  R: choi lai    Q: thoat  ", COLOR_WHITE);
    painted = true;
}
