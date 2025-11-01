#include "game.h"

int main()
{
    Game game;
    initBoard(&game);
    srand(42); // Fixed seed (can be extended to command line parameter)
    gameLoop(&game);
    return 0;
}
