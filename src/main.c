#include "lib.h"

int main(void)
{
    Player_t player = { 8, 1, 20, 5, 2 };

    Labyrinth_t Labyrinth = 
{   'w', 'w', 'w', 'w', 'w', 'w', 'p', 'w', 'w', 'w',
    'w', 'b', 'e', 'p', 'w', 'w', 'f', 'p', 'b', 'w',
    'w', 'w', 'w', 'p', 't', 'w', 'w', 'w', 'b', 'w',
    'w', 'b', 'p', 'e', 'w', 'w', 'w', 'w', 'p', 'w',
    'w', 't', 'w', 'p', 'e', 'b', 'p', 'w', 'p', 'w',
    'w', 'b', 'w', 'w', 'p', 'w', 'b', 'p', 'e', 'w',
    'w', 'e', 'p', 'w', 'p', 'w', 't', 'w', 'p', 'w',
    'w', 'w', 'e', 'p', 'e', 'p', 'e', 'w', 'p', 'w',
    'w', 'c', 'b', 'w', 'w', 'w', 'p', 't', 'b', 'w',
    'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w' };

    int direction;

    printLab(&Labyrinth);

    do 
    {
        checkWhatTile(&Labyrinth, &player);

        printf("\n\nIn which direction do you want to move?\n 0 = UP\n 1 = DOWN\n 2 = LEFT\n 3 = RIGHT\n\n");
        scanf("%d", &direction);

        movePlayer(&Labyrinth, &player, direction);

        printLab(&Labyrinth);
    } while (player.position.x != 0 && player.health != 0);

    return 0;
}