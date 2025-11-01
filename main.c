#include "map.h"
#include "ghost.h"
#include "game.h"
#include "ghost.h"
#include "marks and blood.h"

/*
1. 初始化地图
2. 初始化游戏状态
3. 主游戏循环--
4. 处理用户输入
5. 更新游戏状态

*/
int main()
{
    Ditu ditu;
    chushihua_ditu(&ditu, JIANDAN); // 初始化地图
    get_ghost_positions(ditu.ditu); // 提取幽灵位置
    Game game;
    init_game(&game, 1234, 1); // 初始化游戏状态
    // 主游戏循环（简化版）
    gameLoop(&game);
    movePacman(Game * g, char input); // 人物移动
    moveGhosts(Game * g);             // 幽灵移动
    heckCollision(Game * g);          // 检查碰撞状态
    render_game(const Game *game);    // 渲染游戏
    return 0;
}
