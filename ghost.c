#include "ghost.h"
int try_direction(struct Position pos, int direction)
{
    int newRow = pos.row;
    int newCol = pos.col;

    if (direction == 0)
        newRow--; // 行-1
    else if (direction == 1)
        newRow++; // 行+1
    else if (direction == 2)
        newCol--; // 列-1
    else if (direction == 3)
        newCol++; // 列+1
    else
        return 0; // 无效方向

    // 边界与碰撞检测
    if (newRow < 0 || newRow >= 25 || newCol < 0 || newCol >= 35 || map[newRow][newCol] == '#')
    {
        return 0;
    }

    return 1; // 可以移动
}
int ghost_directions[4] = {0, 1, 2, 3}; // 上下左右