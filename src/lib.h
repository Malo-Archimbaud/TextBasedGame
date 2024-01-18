#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum direction
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
};

typedef struct Labyrinth
{
    int labyrinthlayout[10][10];
} Labyrinth_t;

/* Simplfied layout of the maps, with just walls and paths.

w, w, w, w, w, w, ., W, w, w,
w, ., ., ., w, W, ., ., ., w,
w, w, w, ., ., w, W, w, ., w,
w, ., ., ., w, w, w, w, ., w,
w, ., w, ., ., ., ., w, ., w,
w, ., w, w, ., w, ., ., ., w,
w, ., ., w, ., w, ., w, ., w,
w, w, ., ., ., ., ., w, ., w,
w, ., ., w, w, w, ., ., ., w,
w, w, w, w, w, w, w, w, w, w
*/

typedef struct Position
{
    int x;
    int y;
} Position_t;

typedef	struct Player
{
    Position_t position;
    int health;
    int attack;
    int defense;
} Player_t;

typedef struct Enemy
{
    int health;
    int attack;
} Enemy_t;

void printLab(Labyrinth_t * Labyrinth);
void checkWhatTile(Labyrinth_t * Labyrinth, Player_t * player);
void trap(Player_t * player);
void blessing(Player_t * player);
void fight(Player_t * player, Labyrinth_t * Labyrinth);
int isWall(Labyrinth_t * Labyrinth, Player_t * player, int direction);
void movePlayer(Labyrinth_t * Labyrinth, Player_t * Player, int direction);



void printLab(Labyrinth_t * Labyrinth)
{
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        for (int j = 0; j < 10; j++)
        {
            if (Labyrinth->labyrinthlayout[i][j] == 'p')
            {
                printf(". ");
            }
            else
            {
            printf("%c ", Labyrinth->labyrinthlayout[i][j]);
            }
        }
    }
}


void checkWhatTile(Labyrinth_t * Labyrinth, Player_t * player)
{
    switch (Labyrinth->labyrinthlayout[player->position.x][player->position.y])
    {
        case 'e':
            fight(player, Labyrinth);
            break;
        case 'b':
            blessing(player);
            break;
        case 't':
            trap(player);
            break;
        case 'f':
            //return 5;
            break;
        case 'v':
            printf("You have already been here!\n");
            break;
        default:
            //return 1;
            break;
    }
}

void trap(Player_t * player)
{
    int damage = time(NULL) % 5 + 1;
    player->health = player->health - (damage - player->defense);
    printf("\n\nYou stepped on a trap and lost %d health!\n", damage);
}

void blessing(Player_t * player)
{
    int seed = time(NULL);
    switch(seed%3)
    {
        case 0:
            player->health += 10;
            printf("\n\nYou found a blessing and gained 10 health!\n");
            break;
        case 1:
            player->attack += 1;
            printf("\n\nYou found a blessing and gained 1 attack!\n");
            break;
        case 2:
            player->defense += 1;
            printf("\n\nYou found a blessing and gained 1 defense!\n");
            break;
        default:
            printf("Something went wrong!\n");
            break;
    }
}

void fight(Player_t * Player, Labyrinth_t * Labyrinth)
{
    Enemy_t enemy;
    if (Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] == 'f')
    {
        enemy.health = 50; enemy.attack = 10;
        printf("\n\nYou encountered an enemy, with %d HP\n", enemy.health);
    }
    else
    {
        enemy.health = time(NULL)%10+1; enemy.attack = time(NULL)%5+1;
        printf("\n\nYou encountered an enemy, with %d HP\n", enemy.health);
    }
    do
    {
        int damage = Player->attack;
        enemy.health -= damage;
        printf("\nYou dealt %d damage to the enemy!\n", damage);
        if (enemy.health <= 0)
        {
            printf("\nYou killed the enemy!\n");
            break;
        }
        damage = enemy.attack - Player->defense;
        Player->health -= damage;
        printf("\nThe enemy dealt %d damage to you!\n", damage);
        if (Player->health <= 0)
        {
            printf("\nYou died!\n");
            break;
        }
    } while (Player->health != 0 || enemy.health != 0);
    
    printf("\nYou have %d health left!\n", Player->health);

}


int isWall(Labyrinth_t * Labyrinth, Player_t * player, int direction)
{
    switch (direction)
    {
        case UP:
            if (Labyrinth->labyrinthlayout[player->position.x - 1][player->position.y] == 'w')
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        case DOWN:
            if (Labyrinth->labyrinthlayout[player->position.x + 1][player->position.y] == 'w')
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        case LEFT:
            if (Labyrinth->labyrinthlayout[player->position.x][player->position.y - 1] == 'w')
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        case RIGHT:
            if (Labyrinth->labyrinthlayout[player->position.x][player->position.y + 1] == 'w')
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        default:
            return -1;
            break;
    }
}

void movePlayer(Labyrinth_t * Labyrinth, Player_t * Player, int direction)
{
    int legal = isWall(Labyrinth, Player, direction);

    if (legal == 1)
    {
        printf("\nYou can't move there!\n");
    }
    else if (legal == 0)
    {
        switch (direction)
        {
            case UP:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'v';
                Player->position.x -= 1;
                checkWhatTile(Labyrinth, Player);
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'c';
                break;
            case DOWN:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'v';
                Player->position.x += 1;
                checkWhatTile(Labyrinth, Player);
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'c';
                break;
            case LEFT:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'v';
                Player->position.y -= 1;
                checkWhatTile(Labyrinth, Player);
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'c';
                break;
            case RIGHT:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'v';
                Player->position.y += 1;
                checkWhatTile(Labyrinth, Player);
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = 'c';
                break;
            default:
                printf("Something went wrong!\n");
                break;
        }
    }
    else
    {
        printf("Something went wrong!\n");
    }
}