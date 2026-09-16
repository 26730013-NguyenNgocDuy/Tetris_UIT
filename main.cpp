#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
char cur[4][4];
char blocks[][4][4] = {
    {{' ', ' ', ' ', ' '},
     {'I', 'I', 'I', 'I'},
     {' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'T', ' ', ' '},
     {'T', 'T', 'T', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'S', 'S', ' '},
     {'S', 'S', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'Z', 'Z', ' ', ' '},
     {' ', 'Z', 'Z', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'J', ' ', ' ', ' '},
     {'J', 'J', 'J', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', ' ', 'L', ' '},
     {'L', 'L', 'L', ' '},
     {' ', ' ', ' ', ' '}}};
bool canMove(int dx, int dy)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
            {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W - 1 || yt < 1 || yt >= H - 1)
                    return false;
                if (board[yt][xt] != ' ')
                    return false;
            }
    return true;
}
void rotate()
{
    char old[4][4], tmp[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            old[i][j] = cur[i][j];
            tmp[i][j] = cur[3 - j][i];
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = tmp[i][j];

    int kick[5] = {0, -1, 1, -2, 2};
    for (int k = 0; k < 5; k++)
        if (canMove(kick[k], 0))
        {
            x += kick[k];
            return;
        }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = old[i][j];
}

void spawn()
{
    b = rand() % 7;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cur[i][j] = blocks[b][i][j];
    x = 5;
    y = 1;
}

void block2Board()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
                board[y + i][x + j] = cur[i][j];
}
void boardDelBlock()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (cur[i][j] != ' ')
                board[y + i][x + j] = ' ';
}
void initBoard()
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}
void draw()
{
    system("cls");

    for (int i = 0; i < H; i++, cout << endl)
        for (int j = 0; j < W; j++)
            cout << board[i][j];
}
void removeLine()
{
    int i, j;
    for (i = H - 2; i > 0; i--)
    {
        for (j = 0; j < W; j++)
            if (board[i][j] == ' ')
                break;
        if (j == W)
        {
            for (int ii = i; ii > 1; ii--)
                for (int jj = 1; jj < W - 1; jj++)
                    board[ii][jj] = board[ii - 1][jj];
            for (int jj = 1; jj < W - 1; jj++)
                board[1][jj] = ' ';
            i++;
            draw();
            _sleep(200);
        }
    }
}

int main()
{
    srand(time(0));
    initBoard();
    spawn();
    while (1)
    {
        boardDelBlock();
        if (kbhit())
        {
            char c = getch();
            if (c == 'a' && canMove(-1, 0))
                x--;
            if (c == 'd' && canMove(1, 0))
                x++;
            if (c == 's' && canMove(0, 1))
                y++;
            if (c == 'w')
                rotate();
            if (c == 'q')
                break;
        }
        if (canMove(0, 1))
            y++;
        else
        {
            block2Board();
            removeLine();
            spawn();
        }
        block2Board();
        draw();
        _sleep(500);
    }
    return 0;
}
