#include <stdio.h>
#include <stdlib.h>
#include "ghost.h"

int main(int argc, char **argv)
{
    unsigned int s = 0;
    if (argc > 1)
    {
        s = (unsigned int)atoi(argv[1]);
    }

    set_seed(s);
    unsigned int used = get_seed();
    if (used == 0)
        printf("Using time-based seed (non-deterministic)\n");
    else
        printf("Using seed: %u\n", used);

    printf("10 random directions (rand() %% 4):\n");
    for (int i = 0; i < 10; i++)
    {
        int d = rand() % 4;
        printf("%d ", d);
    }
    printf("\n");

    return 0;
}
