#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Type definitions
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

// Function prototypes
void initBoard(Game *g);
void printBoard(Game *g);
void movePacman(Game *g, char input);
void moveGhosts(Game *g);
void checkCollision(Game *g);
void gameLoop(Game *g);

#endif // GAME_H
