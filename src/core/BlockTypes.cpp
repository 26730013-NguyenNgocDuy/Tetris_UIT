#include "BlockTypes.h"

void BlockI::rotate()
{
    // Hai trạng thái cố định: nằm ngang ở dòng 1, dựng đứng ở cột 1
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            shape[i][j] = ' ';

    if (vertical)
        for (int j = 0; j < SIZE; j++)
            shape[1][j] = 'I';        // về lại nằm ngang
    else
        for (int i = 0; i < SIZE; i++)
            shape[i][1] = 'I';        // dựng đứng

    vertical = !vertical;
}

Blocks *createBlock(int type, int x, int y)
{
    switch (type)
    {
    case Blocks::TYPE_O: return new BlockO(x, y);
    case Blocks::TYPE_T: return new BlockT(x, y);
    case Blocks::TYPE_S: return new BlockS(x, y);
    case Blocks::TYPE_Z: return new BlockZ(x, y);
    case Blocks::TYPE_J: return new BlockJ(x, y);
    case Blocks::TYPE_L: return new BlockL(x, y);
    default:             return new BlockI(x, y);
    }
}
