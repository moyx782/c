
#include "ghost.h"
int ghost_number;
int get_ghost_positions(char map[MAX_ROWS][MAX_COLS])
{
    struct Position positions[MAX_GHOSTS];
    int found = 0;
    for (int r = 0; r < MAX_ROWS; r++)
    {
        for (int c = 0; c < MAX_COLS; c++)
        {
            if (map[r][c] == 'G')
            {
                if (positions != NULL && found < MAX_GHOSTS)
                {
                    positions[found].i = r; // hang
                    positions[found].j = c; // lie
                    // 读取到（i,j）处存在一个position[found]幽灵def as  ghost[found]
                    ghost[found].pos = positions[found];
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
    return rand() % 4; // 返回0-3的随机方向(0-up 1-down 2-left 3-right)
}
int try_direction(struct Position *pos, int direction)
{
    int n_i = pos->i; // new row
    int n_j = pos->j; // new col
                      /*
                  
                                     0
                                     |
                                     |
                                     |
                           2---------+----------3
                                     |
                                     |
                                     1
                  
                  
                  
                  
                      */
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
    if (n_i < 0 || n_i >= 25 || n_j < 0 || n_j >= 35 || map[15][20] == '#')
    {
        return 0; // 无效移动
        // retry();
    }
    return 1; // 可以移动
}

void move_ghost(struct Ghost *ghost)
{
try_again:
    int moved = 0;
    int direction = get_ghost_direction(seed_value); // 假设 seed_value 是全局或可见的
    if (try_direction(&ghost->pos, direction))
    {
        ghost->direction = direction;
        moved = 1;
    }
    else
    {
        goto try_again;
    }
    if (moved)
    {
        int old_i = ghost->pos.i;
        int old_j = ghost->pos.j;

        if (ghost->direction == 0)
            ghost->pos.i--;
        else if (ghost->direction == 1)
            ghost->pos.i++;
        else if (ghost->direction == 2)
            ghost->pos.j--;
        else if (ghost->direction == 3)
            ghost->pos.j++;
    }
}

void move_all_the_ghosts()
{
    ghost_number = get_ghost_positions(0);
    for (int i = 0; i < ghost_number; i++)
    {
        move_ghost(&ghost[i]);
    }
}
