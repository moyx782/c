#include "ghost.h"

// 在单一翻译单元中定义全局数据，避免头文件重复定义导致的链接错误
char start[5][5] = {
    {'#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#'}}; // 结束符
// 默认空地图（大小与 ghost.c 中边界检查一致）
char map[25][35] = {0};

/*
1.侦测ghost位置
2.利用随机数生成ghost的移动方向
3.判别是否可移动
4.更新ghost的位置
5.返回ghost坐标值

*/
// 返回地图上所有鬼的数量，并把至多 max_positions 个位置写入 positions 数组。
// 如果 positions 为 NULL，则仅返回总数。
// struct Position 假设在 ghost.h 中定义为:
//     struct Position { int row; int col; };
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
                    positions[found].row = r;
                    positions[found].col = c;
                }
                found++;
            }
        }
    }
    return found; // 地图上鬼的总数（可能大于 max_positions）
}