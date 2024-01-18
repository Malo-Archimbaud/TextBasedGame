#include "lib.h"

int main(void)
{
    Player_t player = { 8, 1, 20, 5, 2 };

    Labyrinth_t Labyrinth = 
{   W, W, W, W, W, W, P, W, W, W,
    W, B, E, P, W, W, F, P, B, W,
    W, W, W, P, T, W, W, W, B, W,
    W, B, P, E, W, W, W, W, P, W,
    W, T, W, P, E, B, P, W, P, W,
    W, B, W, W, P, W, B, P, E, W,
    W, E, P, W, P, W, T, W, P, W,
    W, W, E, P, E, P, E, W, P, W,
    W, C, P, W, W, W, P, T, B, W,
    W, W, W, W, W, W, W, W, W, W };

    int direction;

    printLab(&Labyrinth);

    do 
    {
        printf("\nIn which direction do you want to move?\n 0 = UP\n 1 = DOWN\n 2 = LEFT\n 3 = RIGHT\n");
        scanf("%d", &direction);

        movePlayer(&Labyrinth, &player, direction);

        printLab(&Labyrinth);
    } while (player.position.x != 0 && player.health != 0);
    return 0;
}