#ifndef GHOST_H
#define GHOST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAP_ROWS 25
#define MAP_COLS 35
#define MAX_GHOSTS 10
struct Position
{
    int i; // hang
    int j; // lie
};
struct Ghost
{
    struct Position pos;
    int direction; // 0-up 1-down 2-left 3-right
};
struct Ghost ghost[MAX_GHOSTS];
// #include "map.h"
// 全局种子值（通过 set_seed 初始化），在 seed.c 中定义
extern unsigned int seed_value;
extern char map[MAP_ROWS][MAP_COLS];

// 设置随机种子：如果传入 0 则使用 time(NULL) 作为种子（非确定性），
// 否则使用传入的值以便可复现。
void set_seed(unsigned int s);

int get_ghost_positions(char map[25][35]);
void move_ghost(struct Ghost *ghost);
int return_ghost_next_position(struct Position pos); // final（最终返回值）

/*
统一吃豆人地图大小要求20*20
rand(seed)
初始化地图
提取地图大小25*35
设定ghost的初始位置)(地图手动设置)需要手动填写坐标初始
侦测ghost位置
不与wall重合

*/
#endif // GHOST_H
