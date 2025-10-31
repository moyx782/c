#include <stdio.h>


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