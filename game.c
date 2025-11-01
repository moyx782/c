#include "game.h"
// 基础数据结构定义
typedef struct
{
    int r, c;
} Pos;

typedef struct
{
    Pos pos;
    Pos start;
    int dr, dc;
} Entity;

typedef struct
{
    int rows, cols;
    char board[25][40];
    Entity pacman;
    Entity ghosts[4];
    int ghostCount;
    int score;
    int lives;
    int foodLeft;
    unsigned int seed;
} Game;

// 初始化地图（示例）
void initBoard(Game *g)
{
    char temp[10][40] = {
        "########################################",
        "#............##............##..........#",
        "#.####.#####.##.#####.####.##.#######..#",
        "#.#  #.#   #.##.#   #.#  #.##.#     #..#",
        "#.#  #.#   #.##.#   #.#  #.##.#     #..#",
        "#.####.#####.##.#####.####.##.#######..#",
        "#......................................#",
        "#.####.#####.##.#####.####.##.#######..#",
        "#............##............##..........#",
        "########################################"};

    g->rows = 10;
    g->cols = 40;
    g->ghostCount = 1;
    g->score = 0;
    g->lives = 3;
    g->foodLeft = 0;

    for (int i = 0; i < g->rows; i++)
    {
        for (int j = 0; j < g->cols; j++)
        {
            g->board[i][j] = temp[i][j];
            if (temp[i][j] == '.')
                g->foodLeft++;
        }
    }

    g->pacman.pos = (Pos){1, 1};
    g->pacman.start = (Pos){1, 1};
    g->ghosts[0].pos = (Pos){5, 20};
    g->ghosts[0].start = (Pos){5, 20};
}

// 打印棋盘
void printBoard(Game *g)
{
    system("clear || cls"); // 清屏兼容 Linux/Windows
    for (int i = 0; i < g->rows; i++)
    {
        for (int j = 0; j < g->cols; j++)
        {
            if (i == g->pacman.pos.r && j == g->pacman.pos.c)
                putchar('P');
            else
            {
                int ghostHere = 0;
                for (int k = 0; k < g->ghostCount; k++)
                    if (g->ghosts[k].pos.r == i && g->ghosts[k].pos.c == j)
                    {
                        putchar('G');
                        ghostHere = 1;
                        break;
                    }
                if (!ghostHere)
                    putchar(g->board[i][j]);
            }
        }
        putchar('\n');
    }
    printf("Score: %d | Lives: %d | Food left: %d\n", g->score, g->lives, g->foodLeft);
}

// 玩家移动逻辑
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

// 幽灵随机移动（示意版）
void moveGhosts(Game *g)
{
    for (int i = 0; i < g->ghostCount; i++)
    {
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int valid[4], count = 0;

        for (int d = 0; d < 4; d++)
        {
            int nr = g->ghosts[i].pos.r + dirs[d][0];
            int nc = g->ghosts[i].pos.c + dirs[d][1];
            if (g->board[nr][nc] != '#')
                valid[count++] = d;
        }

        if (count > 0)
        {
            int choice = rand() % count;
            g->ghosts[i].pos.r += dirs[valid[choice]][0];
            g->ghosts[i].pos.c += dirs[valid[choice]][1];
        }
    }
}

// 碰撞检测与生命处理
void checkCollision(Game *g)
{
    for (int i = 0; i < g->ghostCount; i++)
    {
        if (g->ghosts[i].pos.r == g->pacman.pos.r &&
            g->ghosts[i].pos.c == g->pacman.pos.c)
        {
            printf("💀 Ghost caught you!\n");
            g->lives--;
            g->pacman.pos = g->pacman.start;
            g->ghosts[i].pos = g->ghosts[i].start;
            getchar();
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
    srand(42); // 固定种子（可扩展为命令行参数）
    gameLoop(&game);
    return 0;
}
