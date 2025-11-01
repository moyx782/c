// 玩家移动逻辑
#include "marks and blood.h"
void movePacman(Game *g, char input)
{
    int dr = 0, dc = 0;
    switch (toupper(input))
    {
    case 'W':
        dr = -1;
        break;
    case 'S':
        dr = 1;
        break;
    case 'A':
        dc = -1;
        break;
    case 'D':
        dc = 1;
        break;
    default:
        return;
    }

    int nr = g->pacman.pos.r + dr;
    int nc = g->pacman.pos.c + dc;
    if (g->board[nr][nc] != '#')
    { // 非墙壁才能移动
        g->pacman.pos.r = nr;
        g->pacman.pos.c = nc;
        if (g->board[nr][nc] == '.')
        {
            g->board[nr][nc] = ' ';
            g->score += 10;
            g->foodLeft--;
        }
    }
}

// 主游戏循环
void gameLoop(Game *g)
{
    char input;
    while (g->lives > 0 && g->foodLeft > 0)
    {
        printBoard(g);
        printf("Move (W/A/S/D, Q to quit): ");
        if (scanf(" %c", &input) != 1)
            break;
        if (toupper(input) == 'Q')
            break;

        movePacman(g, input);
        moveGhosts(g);
        checkCollision(g);
    }

    printBoard(g);
    if (g->foodLeft == 0)
        printf("🎉 You win! Final score: %d\n", g->score);
    else
        printf("Game Over! Final score: %d\n", g->score);
}

int main()
{
    Game game;
    initBoard(&game);
    srand(42); // 固定种子
    gameLoop(&game);
    return 0;
}