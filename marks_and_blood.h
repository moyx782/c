#ifndef MARKS_AND_BLOOD_H
#define MARKS_AND_BLOOD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "map.h"

typedef struct Pos
{
    int row; // 行号（从上到下）
    int col; // 列号（从左到右）
} Pos;

typedef struct Entity
{
    Pos current_pos; // 当前位置
    Pos start_pos;   // 初始位置（重生用）
    int dir_row;     // 行方向：-1(上)、1(下)、0(无垂直移动)
    int dir_col;     // 列方向：-1(左)、1(右)、0(无水平移动)
    char type;       // 实体类型：'P'(Pac-Man)、'G'(幽灵)
} Entity;

typedef struct Game // 游戏状态结构体：集中管理得分、血量及所有游戏数据
{
    int map_rows;          // 地图行数（最大25）
    int map_cols;          // 地图列数（最大40）
    char map[15][20];      // 游戏地图（2D字符数组）
    Entity pacman;         // Pac-Man实体
    Entity ghosts[4];      // 幽灵数组（最多4个）
    int ghost_count;       // 实际幽灵数量（1-4）
    int score;             // 当前得分
    int lives;             // 剩余血量（初始3）
    int remaining_pellets; // 剩余 pellets 数量（判断胜利条件）
    unsigned int rng_seed; // 随机数种子（保证确定性）
    int game_over;         // 游戏结束标志：0(运行中)、1(胜利)、2(失败)
} Game;
void init_game(Game *game, unsigned int seed, int ghost_num);
void update_map_entities(Game *game);
void render_game(const Game *game);
void init_game(Game *game, unsigned int seed, int ghost_num);
void update_map_entities(Game *game);
void render_game(const Game *game);
void update_map_entities(Game *game);
void render_game(const Game *game);

#endif // MARKS_AND_BLOOD_H