#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// #include "map.h"
// 全局种子值（通过 set_seed 初始化），在 seed.c 中定义
extern unsigned int seed_value;
extern char map[25][35];

// 设置随机种子：如果传入 0 则使用 time(NULL) 作为种子（非确定性），
// 否则使用传入的值以便可复现。
void set_seed(unsigned int s);
unsigned int get_seed(void);

struct Position
{
    int row;
    int col;
};
struct Ghost
{
    struct Position pos;
    int direction;
};
int try_direction(struct Position pos, int direction); // use rand(seed)%4 to generate random number
int move_ghost(struct Ghost *ghost);
/*
统一吃豆人地图大小要求20*20
rand(seed)
初始化地图
提取地图大小25*35
设定ghost的初始位置)(地图手动设置)需要手动填写坐标初始
侦测ghost位置
不与wall重合

*/