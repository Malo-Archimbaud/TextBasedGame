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

    menu(&Labyrinth, &player);

    printLab(&Labyrinth);

    int input;
    do 
    {
        printf("\n\nWhat do you want to do?\n");
        printf(" 1 = Go up\n 2 = go down\n 3 = go left\n 4 = go right\n 5 = display stats\n 9 = save and quit\n");
        input = getInput();

        action(&Labyrinth, &player, input);

        printLab(&Labyrinth);
    } while (player.position.x != 0 && player.health > 0);

    if (player.health <= 0)
    {
        printf("\nYou couldn't escape the labyrinth, leaving %d gold behind you\n", player.money);
    }
    else
    {
        printf("\nYou won!\nYou managed to escape with %d gold\n", player.money);
    }

    return 0;
}