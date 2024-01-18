#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum TileType
{
    W = 0, // Wall
    P = 1, // Path
    E = 2, // Enemy
    B = 3, // Blessing
    T = 4, // Trap
    F = 5, // Boss
    V = 6, // Visited
    C = 7, // Characters
};

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
    int defense;
} Enemy_t;

void printLab(Labyrinth_t * Labyrinth);
void checkWhatTile(Labyrinth_t * Labyrinth, Player_t * player);
void trap(Player_t * player);
void blessing(Player_t * player);
int isWall(Labyrinth_t * Labyrinth, Player_t * player, int direction);
void movePlayer(Labyrinth_t * Labyrinth, Player_t * Player, int direction);



void printLab(Labyrinth_t * Labyrinth)
{
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        for (int j = 0; j < 10; j++)
        {
            switch(Labyrinth->labyrinthlayout[i][j]){
                case 0:
                    printf("w ");
                    break;
                case 1:
                    printf(". ");
                    break;
                case 2:
                    printf("e ");
                    break;
                case 3:
                    printf("b ");
                    break;
                case 4:
                    printf("t ");
                    break;
                case 5:
                    printf("f ");
                    break;
                case 6:
                    printf("v ");
                    break;
                case 7:
                    printf("c ");
                    break;
            }
        }
    }
}


void checkWhatTile(Labyrinth_t * Labyrinth, Player_t * player)
{
    switch (Labyrinth->labyrinthlayout[player->position.x][player->position.y])
    {
        case E:
            //return 2;
            break;
        case B:
            blessing(player);
            break;
        case T:
            trap(player);
            break;
        case F:
            //return 5;
            break;
        default:
            //return 1;
            break;
    }
}

void trap(Player_t * player)
{
    int damage = rand() % 10 + 1;
    player->health = player->health - (damage - player->defense);
    printf("You stepped on a trap and lost %d health!\n", damage);
}

void blessing(Player_t * player)
{
    int health = rand() % 10 + 1;
    player->health = player->health + health;
    printf("You found a blessing and gained %d health!\n", health);
}




int isWall(Labyrinth_t * Labyrinth, Player_t * player, int direction)
{
    switch (direction)
    {
        case UP:
            if (Labyrinth->labyrinthlayout[player->position.x - 1][player->position.y] == W)
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        case DOWN:
            if (Labyrinth->labyrinthlayout[player->position.x + 1][player->position.y] == W)
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        case LEFT:
            if (Labyrinth->labyrinthlayout[player->position.x][player->position.y - 1] == W)
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;
        case RIGHT:
            if (Labyrinth->labyrinthlayout[player->position.x][player->position.y + 1] == W)
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
        printf("You can't move there!\n");
    }
    else if (legal == 0)
    {
        switch (direction)
        {
            case UP:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = V;
                Player->position.x -= 1;
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = C;
                break;
            case DOWN:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = V;
                Player->position.x += 1;
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = C;
                break;
            case LEFT:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = V;
                Player->position.y -= 1;
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = C;
                break;
            case RIGHT:
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = V;
                Player->position.y += 1;
                Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] = C;
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