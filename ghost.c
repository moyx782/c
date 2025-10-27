#include "ghost.h"
int get_ghost_positions(struct Position *positions, int max_positions)
{
    int found = 0;
    for (int r = 0; r < 25; r++)
    {
        for (int c = 0; c < 35; c++)
        {
            if (map[r][c] == 'G')
            {
                if (positions != NULL && found < max_positions)
                {
                    positions[found].i = r; // hang
                    positions[found].j = c; // lie
                }
                found++;
            }
        }
    }
    return found; // 地图上鬼的总数
}
int get_ghost_direction(int seed)
{
    if (seed == 0)
        srand((unsigned int)time(NULL));
    else
        srand(seed);
    return rand() % 4; // 返回0-3的随机方向
}
int try_direction(struct Position pos, int direction)
{
    int n_i = pos.i; // new row
    int n_j = pos.j; // new col

    if (direction == 0)
        n_i--; // 行-1
    else if (direction == 1)
        n_i++; // 行+1
    else if (direction == 2)
        n_j--; // 列-1
    else if (direction == 3)
        n_j++; // 列+1
    else
        return 0; // 无效方向

    // 边界与碰撞检测
    if (n_i < 0 || n_i >= 25 || n_j < 0 || n_j >= 35 || map[n_i][n_j] == '#')
    {
        return 0; // 无效移动
    }

    return 1; // 可以移动
}
int ghost_directions[4] = {0, 1, 2, 3}; // 上下左右