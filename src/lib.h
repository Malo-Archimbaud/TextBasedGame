#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Enum for directions
enum direction
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
};

// Struct for the Labyrinth, which is a 10x10 array of char
// The char represents the tile type, and is used to determine what happens when the player steps on it
// w = wall, . = path, e = enemy, b = blessing, t = trap, f = final boss, v = visited, c = current
typedef struct Labyrinth
{
    int labyrinthlayout[10][10];
} Labyrinth_t;

/* Simplfied layout of the maps, with just walls and paths.

w, w, w, w, w, w, ., W, w, w,
w, ., ., ., w, W, ., ., ., w,
w, w, w, ., ., ., ., w, ., w,
w, ., ., ., w, w, w, w, ., w,
w, ., w, ., ., ., ., w, ., w,
w, ., w, w, ., w, ., ., ., w,
w, ., ., w, ., w, ., w, ., w,
w, w, ., ., ., ., ., w, ., w,
w, ., ., w, w, w, ., ., ., w,
w, w, w, w, w, w, w, w, w, w
*/

// Coordinates for the player
typedef struct Position
{
    int x;
    int y;
} Position_t;

// Player, you can initialize how you want in the main.c
typedef	struct Player
{
    Position_t position;
    int health;
    int attack;
    int defense;
    int money;  // represents the score
} Player_t;

// Enemy, stats are randomized each time a new enemy is encountered
typedef struct Enemy
{
    int health;
    int attack;
    int money;
} Enemy_t;

void printLab(Labyrinth_t * Labyrinth);
void checkWhatTile(Labyrinth_t * Labyrinth, Player_t * player);
void trap(Player_t * player);
void blessing(Player_t * player);
void fight(Player_t * player, Labyrinth_t * Labyrinth);
void randomEvent(Labyrinth_t * Labyrinth, Player_t * Player);
int isWall(Labyrinth_t * Labyrinth, Player_t * player, int direction);
void movePlayer(Labyrinth_t * Labyrinth, Player_t * Player, int direction);


// Prints the labyrinth, with the player represented by 'c', tile already visited by 'v', walls by 'w', and the rest by '.'
void printLab(Labyrinth_t * Labyrinth)
{
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        for (int j = 0; j < 10; j++)
        {
            if (Labyrinth->labyrinthlayout[i][j] == 'w' || Labyrinth->labyrinthlayout[i][j] == 'v' || Labyrinth->labyrinthlayout[i][j] == 'c')
            {
                printf("%c ", Labyrinth->labyrinthlayout[i][j]);
            }
            else
            {
                printf(". ");
            }
        }
    }
    printf("\n");
}


// Checks what tile the player is on, and calls the appropriate function
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
            fight(player, Labyrinth);
            break;
        case 'v':
            printf("You have already been here!\n");
            break;
        case 'p':
            randomEvent(Labyrinth, player);
            break;
        default:
            //printf("Something went wrong!\n");
            break;
    }
}

// Randomly damages the player
void trap(Player_t * player)
{
    int damage = time(NULL) % 5 + 1;
    player->health = player->health - (damage - player->defense);
    printf("\n\nYou stepped on a trap and lost %d health!\n", damage);
}

// Randomly gives the player a blessing between health, attack, and defense
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
            break;
    }
}

// Handle enemy generation and fight
void fight(Player_t * Player, Labyrinth_t * Labyrinth)
{
    Enemy_t enemy;
    if (Labyrinth->labyrinthlayout[Player->position.x][Player->position.y] == 'f') // final boss, fixed stats
    {
        enemy.health = 50; enemy.attack = 10; enemy.money = 100;
        printf("\n\nYou encountered a more powerful foe, with %d HP\n", enemy.health);
    }
    else // normal enemy, randomized stats
    {
        enemy.health = time(NULL)%10+1; enemy.attack = time(NULL)%5+1; enemy.money = time(NULL)%11+10;
        printf("\n\nYou encountered an enemy, with %d HP\n", enemy.health);
    }
    do // simple turn by turn fight
    {
        int damage = Player->attack;
        enemy.health -= damage;
        printf("\nYou dealt %d damage to the enemy!\n", damage);
        if (enemy.health <= 0)
        {
            printf("\nYou killed the enemy, and earn %d gold\n", enemy.money);
            Player->money += enemy.money;
            break;
        }
        damage = enemy.attack - Player->defense;
        Player->health -= damage;
        printf("\nThe enemy dealt %d damage to you!\n", damage);
        if (Player->health <= 0)
        {
            printf("\nYou died!\n");
            return;
        }
    } while (Player->health != 0 || enemy.health != 0);
    
    printf("\nYou have %d health left!\n", Player->health);
}

// Trigger a random event on empty tiles , 60% chance of nothing happening, 20% chance of fight, 10% chance of blessing, 10% chance of trap
void randomEvent(Labyrinth_t * Labyrinth, Player_t * Player)
{
    int seed = time(NULL)%10;

    if (seed >=6 && seed <= 7)
    {
        fight(Player, Labyrinth);
    }
    else if (seed == 8)
    {
        blessing(Player);
    }
    else if (seed == 9)
    {
        trap(Player);
    }
    else
    {
        printf("\n\nNothing happened!\n");
    }
}


// Checks if the player is trying to move into a wall
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

// Moves the player in the direction specified, if possible
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