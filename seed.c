#include "ghost.h"
#include <stdlib.h>
#include <time.h>

// 定义全局种子变量
unsigned int seed_value = 0;

void set_seed(unsigned int s)
{
    seed_value = s;
    if (s == 0)
    {
        srand((unsigned int)time(NULL));
    }
    else
    {
        srand(s);
    }
}

unsigned int get_seed(void)
{
    return seed_value;
}
