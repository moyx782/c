#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// 初始化游戏状态（包含得分、血量、 pellets 计数）
// 参数：game - 游戏状态指针；seed - 随机数种子；ghost_num - 幽灵数量（1-4）
void init_game(Game* game, unsigned int seed, int ghost_num) {
    // 1. 初始化地图（固定测试地图，可根据需求修改）
    const char init_map[][] = {
       
    };
    game->map_rows = ;
    game->map_cols = ;

    // 复制地图到游戏状态，并统计 pellets 数量、记录实体初始位置
    game->remaining_pellets = 0;
    for (int i = 0; i < game->map_rows; i++) {
        for (int j = 0; j < game->map_cols; j++) {
            game->map[i][j] = init_map[i][j];
            // 统计普通 pellets（.）数量
            if (game->map[i][j] == '.') {
                game->remaining_pellets++;
            }
            // 记录Pac-Man初始位置
            else if (game->map[i][j] == 'P') {
                game->pacman.current_pos = (Pos){i, j};
                game->pacman.start_pos = (Pos){i, j};
                game->pacman.dir_row = 0;
                game->pacman.dir_col = 0;
                game->pacman.type = 'P';
            }
            // 记录幽灵初始位置（最多4个）
            else if (game->map[i][j] == 'G' && game->ghost_count < ghost_num) {
                game->ghosts[game->ghost_count].current_pos = (Pos){i, j};
                game->ghosts[game->ghost_count].start_pos = (Pos){i, j};
                game->ghosts[game->ghost_count].dir_row = 0;
                game->ghosts[game->ghost_count].dir_col = 0;
                game->ghosts[game->ghost_count].type = 'G';
                game->ghost_count++;
            }
        }
    }

    // 2. 初始化得分与血量
    game->score = 0;          // 初始得分0
    game->lives = 3;          // 初始血量3
    game->rng_seed = seed;    // 设置随机数种子（保证可复现）
    game->game_over = 0;      // 游戏初始为运行中
    srand(seed);              // 初始化随机数生成器
}
3. 得分更新函数（吃 Pellets 逻辑）
c
运行
// 处理Pac-Man吃Pellets逻辑，更新得分和剩余Pellets数量
// 参数：game - 游戏状态指针
void handle_pellet_eat(Game* game) {
    Pos pac_pos = game->pacman.current_pos;
    // 检查当前位置是否为普通Pellets（.）
    if (game->map[pac_pos.row][pac_pos.col] == '.') {
        game->score += 10;                          // 吃一个Pellets得10分
        game->map[pac_pos.row][pac_pos.col] = ' ';  // 清除地图上的Pellets
        game->remaining_pellets--;                  // 减少剩余Pellets数量
        
        // 检查是否吃完所有Pellets（胜利条件）
        if (game->remaining_pellets <= 0) {
            game->game_over = 1;  // 1表示游戏胜利
        }
    }
}

// 处理Pac-Man吃Pellets逻辑，更新得分和剩余Pellets数量
// 参数：game - 游戏状态指针
void handle_pellet_eat(Game* game) {
    Pos pac_pos = game->pacman.current_pos;
    // 检查当前位置是否为普通Pellets（.）
    if (game->map[pac_pos.row][pac_pos.col] == '.') {
        game->score += 10;                          // 吃一个Pellets得10分
        game->map[pac_pos.row][pac_pos.col] = ' ';  // 清除地图上的Pellets
        game->remaining_pellets--;                  // 减少剩余Pellets数量
        
        // 检查是否吃完所有Pellets（胜利条件）
        if (game->remaining_pellets <= 0) {
            game->game_over = 1;  // 1表示游戏胜利
        }
    }
}


// 检查Pac-Man与幽灵的碰撞，处理血量减少和重生
// 参数：game - 游戏状态指针
void check_ghost_collision(Game* game) {
    Pos pac_pos = game->pacman.current_pos;
    // 遍历所有幽灵，检查是否与Pac-Man位置重叠
    for (int i = 0; i < game->ghost_count; i++) {
        Pos ghost_pos = game->ghosts[i].current_pos;
        if (pac_pos.row == ghost_pos.row && pac_pos.col == ghost_pos.col) {
            // 碰撞发生：减少血量
            game->lives--;
            printf("\n【碰撞警告】碰到幽灵！剩余血量：%d\n", game->lives);
            
            // 检查血量是否为0（失败条件）
            if (game->lives <= 0) {
                game->game_over = 2;  // 2表示游戏失败
                return;
            }
            
            // 血量未耗尽：实体重生（回到初始位置）
            game->pacman.current_pos = game->pacman.start_pos;  // Pac-Man重生
            game->pacman.dir_row = 0;
            game->pacman.dir_col = 0;
            
            // 所有幽灵回到初始位置
            for (int j = 0; j < game->ghost_count; j++) {
                game->ghosts[j].current_pos = game->ghosts[j].start_pos;
                game->ghosts[j].dir_row = 0;
                game->ghosts[j].dir_col = 0;
            }
            
            // 重生后更新地图显示（避免实体残留）
            update_map_entities(game);
            return;  // 一次碰撞只处理一次，避免重复扣血
        }
    }
}

// 更新地图上的实体位置（避免重生后残留旧位置）
// 参数：game - 游戏状态指针
void update_map_entities(Game* game) {
    // 1. 清除地图上所有旧的实体标记（P和G）
    for (int i = 0; i < game->map_rows; i++) {
        for (int j = 0; j < game->map_cols; j++) {
            if (game->map[i][j] == 'P' || game->map[i][j] == 'G') {
                game->map[i][j] = ' ';  // 实体位置重置为空白
            }
        }
    }

    // 2. 重新在地图上标记实体当前位置
    Pos pac_pos = game->pacman.current_pos;
    game->map[pac_pos.row][pac_pos.col] = 'P';  // 标记Pac-Man位置
    
    for (int i = 0; i < game->ghost_count; i++) {
        Pos ghost_pos = game->ghosts[i].current_pos;
        game->map[ghost_pos.row][ghost_pos.col] = 'G';  // 标记幽灵位置
    }
}
// 渲染游戏界面（包含地图、得分、血量等状态）
// 参数：game - 游戏状态指针；
void render_game(const Game* game, ) {
    // 清屏（兼容大多数终端，比system("clear")更轻量）
    printf("\033[H\033[J");
    
    // 1. 打印地图
    for (int i = 0; i < game->map_rows; i++) {
        printf("%s\n", game->map[i]);
    }
    
    // 2. 打印游戏状态（得分、血量、剩余Pellets、帧数）
    printf("\n=====================================");
    printf("\n  得分 (Score): %d", game->score);
    printf("\n  剩余血量 (Lives): %d", game->lives);
    printf("\n  剩余Pellets: %d", game->remaining_pellets);
    printf("\n  操作：W(上) A(左) S(下) D(右) Q(退出)");
    printf("\n=====================================\n");
    
    // 3. 打印游戏结束信息（如果游戏结束）
    if (game->game_over == 1) {
        printf("\n【游戏胜利】恭喜！你吃完了所有Pellets！\n");
    } else if (game->game_over == 2) {
        printf("\n【游戏失败】血量耗尽！最终得分：%d\n", game->score);
    }
}