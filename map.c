#include "map.h"  // 包含我们自己的头文件

// 简单地图数据
static char JIANDAN_DITU[19][20] = {
    "###################",
    "#.........#.......#",
    "#.###.#.#.#.#.###.#", 
    "#P................#",
    "#.#.#.#.###.#.#.#.#",
    "#.....#.....#.....#",
    "#####.# ### #.#####",
    "    #.#     #.#    ",
    "#####.# ### #.#####",
    "#.........#.......#", 
    "#.###.#.#.#.#.###.#",
    "#...#.........#...#",
    "###.#.#.###.#.#.###",
    "#.....#.....#.....#",
    "#.#########.#####.#",
    "#.................#",
    "###################"
};

// 高级地图数据  
static char GAOJI_DITU[23][37] = {
    "####################################",
    "#............##............##......#",
    "#.####.#####.##.#####.####.##.###.#",
    "#O#  # #   #  #  #   #  # #   #  #O#", 
    "#.#  # # # ## ## ## # #  # ## #  #.#",
    "#.#  #   #    #     #  #     #  #.#",
    "#O#  ####### # ######  # ##### #O#  ",
    "#.####.#..........#..........#.####.#",
    "#......#...G......#......G...#......#", 
    "#.####.#..........#..........#.####.#",
    "#O#  # ##### ###### ###### ##### #O#",
    "#.#  # #       P        #      # #.#",
    "#.#  # # ## ## ## ## ## ## ## # #.#", 
    "#O#  # # #  #  #  #  #  #  # # #O#  ",
    "#.####.###.##.##.##.##.##.###.####.#",
    "#..........................#.......#",
    "#####.####.##.######.##.####.#####  ", 
    "#   #.#    #  #    #  #    #.#   #  ",
    "#   #.# ####  # ####  #### #.#   #  ",
    "#   #.# #     #    #     # #.#   #  ",
    "#   #.# # ############## # #.#   #  ",
    "#     .# #              # #.      # ",
    "####################################"
};

// 初始化地图函数
void chushihua_ditu(Ditu* ditu, DituNandu nandu) {
    // 清空整个地图结构体
    memset(ditu, 0, sizeof(Ditu));
    // 设置地图难度
    ditu->nandu = nandu;
    
    if (nandu == JIANDAN) {
        // 初始化简单地图
        ditu->hangshu = 19;
        ditu->lieshu = 19;
        ditu->you_shuiguo = 0;  // 简单地图没有水果
        
        for (int i = 0; i < ditu->hangshu; i++) {
            for (int j = 0; j < ditu->lieshu; j++) {
                // 复制地图数据
                ditu->ditu[i][j] = JIANDAN_DITU[i][j];
                
                // 统计豆子
                if (JIANDAN_DITU[i][j] == DOUZI) {
                    ditu->zong_douzishu++;
                } 
                // 记录Pac-Man起始位置
                else if (JIANDAN_DITU[i][j] == PACMAN_QISHI) {
                    ditu->pacman_qishi_hang = i;
                    ditu->pacman_qishi_lie = j;
                    ditu->ditu[i][j] = KONGBAI;  // 清空起始位置
                } 
                // 记录幽灵起始位置
                else if (JIANDAN_DITU[i][j] == YOULING_QISHI) {
                    if (ditu->youling_shuliang < 4) {
                        ditu->youling_qishi_hang[ditu->youling_shuliang] = i;
                        ditu->youling_qishi_lie[ditu->youling_shuliang] = j;
                        ditu->youling_shuliang++;
                        ditu->ditu[i][j] = KONGBAI;  // 清空起始位置
                    }
                }
            }
        }
        
    } else {
        // 初始化高级地图
        ditu->hangshu = 23;
        ditu->lieshu = 36;
        ditu->you_shuiguo = 1;  // 高级地图有水果
        
        for (int i = 0; i < ditu->hangshu; i++) {
            for (int j = 0; j < ditu->lieshu; j++) {
                // 复制地图数据
                ditu->ditu[i][j] = GAOJI_DITU[i][j];
                
                // 统计普通豆子
                if (GAOJI_DITU[i][j] == DOUZI) {
                    ditu->zong_douzishu++;
                } 
                // 统计能量豆
                else if (GAOJI_DITU[i][j] == NENGLIANG_DOU) {
                    ditu->zong_douzishu++;
                    ditu->nengliangdoushu++;
                } 
                // 记录Pac-Man起始位置
                else if (GAOJI_DITU[i][j] == PACMAN_QISHI) {
                    ditu->pacman_qishi_hang = i;
                    ditu->pacman_qishi_lie = j;
                    ditu->ditu[i][j] = KONGBAI;
                } 
                // 记录幽灵起始位置
                else if (GAOJI_DITU[i][j] == YOULING_QISHI) {
                    if (ditu->youling_shuliang < 4) {
                        ditu->youling_qishi_hang[ditu->youling_shuliang] = i;
                        ditu->youling_qishi_lie[ditu->youling_shuliang] = j;
                        ditu->youling_shuliang++;
                        ditu->ditu[i][j] = KONGBAI;
                    }
                }
            }
        }
    }
    
    // 设置剩余豆子数
    ditu->shengyu_douzishu = ditu->zong_douzishu;
}

// 显示地图函数
void xianshi_ditu(const Ditu* ditu) {
    for (int i = 0; i < ditu->hangshu; i++) {
        for (int j = 0; j < ditu->lieshu; j++) {
            printf("%c", ditu->ditu[i][j]);
        }
        printf("\n");
    }
}

// 检查是否是墙
int shi_qiang(const Ditu* ditu, int hang, int lie) {
    // 先检查是否超出边界
    if (hang < 0 || hang >= ditu->hangshu || lie < 0 || lie >= ditu->lieshu) {
        return 1;  // 超出边界也算墙
    }
    // 检查该位置是否是墙字符
    return ditu->ditu[hang][lie] == QIANG;
}

// 检查是否是隧道（高级功能）
int shi_suidao(const Ditu* ditu, int hang, int lie) {
    if (ditu->nandu == GAOJI) {
        // 检查是否是地图的特殊隧道位置
        if ((hang == 16 && (lie == 0 || lie == ditu->lieshu-1)) ||
            (hang == 17 && (lie == 0 || lie == ditu->lieshu-1))) {
            return 1;  // 是隧道
        }
    }
    return 0;  // 不是隧道
}

// 吃豆子函数
int chi_douzi(Ditu* ditu, int hang, int lie) {
    char weizhi = ditu->ditu[hang][lie];
    int defen = 0;
    
    if (weizhi == DOUZI) {
        // 吃掉普通豆子
        ditu->ditu[hang][lie] = KONGBAI;
        ditu->shengyu_douzishu--;
        defen = 10;
    } else if (weizhi == NENGLIANG_DOU) {
        // 吃掉能量豆
        ditu->ditu[hang][lie] = KONGBAI;
        ditu->shengyu_douzishu--;
        ditu->nengliangdoushu--;
        defen = 50;
    }
    
    return defen;
}

// 获取Pac-Man起始位置
void huoqu_pacman_qishi(const Ditu* ditu, int* hang, int* lie) {
    *hang = ditu->pacman_qishi_hang;
    *lie = ditu->pacman_qishi_lie;
}

// 获取幽灵起始位置
void huoqu_youling_qishi(const Ditu* ditu, int youling_index, int* hang, int* lie) {
    if (youling_index >= 0 && youling_index < ditu->youling_shuliang) {
        *hang = ditu->youling_qishi_hang[youling_index];
        *lie = ditu->youling_qishi_lie[youling_index];
    }
}

// 获取幽灵数量
int huoqu_youling_shuliang(const Ditu* ditu) {
    return ditu->youling_shuliang;
}

// 检查是否有能量豆
int you_nengliangdou(const Ditu* ditu) {
    return ditu->nengliangdoushu > 0;
}

// 检查是否支持水果奖励
int zhichi_shuiguo(const Ditu* ditu) {
    return ditu->you_shuiguo;
}

// 激活能量豆
int jihuo_nengliangdou(Ditu* ditu, int hang, int lie) {
    if (ditu->ditu[hang][lie] == NENGLIANG_DOU) {
        ditu->ditu[hang][lie] = KONGBAI;
        ditu->shengyu_douzishu--;
        ditu->nengliangdoushu--;
        return 1;  // 激活成功
    }
    return 0;  // 不是能量豆，激活失败
}

// 重置地图
void chongzhi_ditu(Ditu* ditu) {
    // 保存当前难度
    DituNandu nandu = ditu->nandu;
    // 重新初始化地图
    chushihua_ditu(ditu, nandu);
}