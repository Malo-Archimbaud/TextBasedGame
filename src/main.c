#include "lib.h"

int main(void)
{
    Player_t player = { 8, 1, 20, 5, 2, 0 };

    Labyrinth_t Labyrinth = 
{   'w', 'w', 'w', 'w', 'w', 'w', 'p', 'w', 'w', 'w',
    'w', 'b', 'e', 'p', 'w', 'w', 'f', 'p', 'b', 'w',
    'w', 'w', 'w', 'p', 'p', 'b', 'p', 'w', 'b', 'w',
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
        printf("\n\nIn which direction do you want to move?\n 1 = UP\n 2 = DOWN\n 3 = LEFT\n 4 = RIGHT\n\n");
        direction = getInput();

        movePlayer(&Labyrinth, &player, direction);

        printLab(&Labyrinth);
    } while (player.position.x != 0 && player.health != 0);

    if (player.health <= 0)
    {
        printf("\nYou died!\n");
    }
    else
    {
        printf("\nYou won!\nYou managed to escape with %d gold\n", player.money);
    }

    return 0;
}