#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Enum for directions
enum direction
{
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
};

// Struct for the Labyrinth, which is a 10x10 array of char
// The char represents the tile type, and is used to determine what happens when the player steps on it
// w = wall, . = path, e = enemy, b = blessing, t = trap, f = final boss, v = visited, c = current
typedef struct Labyrinth
{
    char labyrinthlayout[10][10];
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

// Player
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
int getInput(void);
void action(Labyrinth_t * Labyrinth, Player_t * Player, int input);
int isWall(Labyrinth_t * Labyrinth, Player_t * player, int direction);
void movePlayer(Labyrinth_t * Labyrinth, Player_t * Player, int direction);
void saveGame(Labyrinth_t * Labyrinth, Player_t * Player);
void loadGame(Labyrinth_t * Labyrinth, Player_t * Player);
void menu(Labyrinth_t * Labyrinth, Player_t * Player);


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
            printf("You have already been here, so nothing happened \n");
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
        if (damage < 0)
        {
            damage = 0;
        }
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


int getInput(void)
{
    char input[50];
    scanf("%c", &input);
    if (input[0] >= '1' && input[0] <= '9' && strlen(input) == 1)
    {
        return (int)input[0] - '0';
    }
    else
    {
        printf("Invalid input!\n");
        getInput();
    }
}

void action(Labyrinth_t * Labyrinth, Player_t * player, int input)
{
    if (input >= 1 && input <= 4)
    {
        movePlayer(Labyrinth, player, input);
    }
    else if (input == 5)
    {
        printf("\n\nHealth: %d\nAttack: %d\nDefense: %d\nGold: %d\n", player->health, player->attack, player->defense, player->money);
    }
    else if (input == 9)
    {
        printf("\n\nYou quit the game!\n");
        saveGame(Labyrinth, player);
        exit(0);
    }
    else
    {
        printf("\n\nInvalid input!\n");
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
void movePlayer(Labyrinth_t * Labyrinth, Player_t * Player, int input)
{
    int legal = isWall(Labyrinth, Player, input);

    if (legal == 1)
    {
        printf("\nYou can't move there!\n");
    }
    else if (legal == 0)
    {
        switch (input)
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


//menu
void menu(Labyrinth_t * Labyrinth, Player_t * Player)
{
    printf("Welcome to the Labyrinth!\n");
    printf("What do you want to do?\n");
    printf(" 1 = Start new game\n 2 = Load save\n 3 = Quit\n");
    int input = getInput();
    switch (input)
    {
        case 1:
            break;
        case 2:
            loadGame(Labyrinth, Player);
            break;
        case 3:
            printf("\n\nYou quit the game!\n");
            exit(0);
            break;
        default:
            printf("\n\nInvalid input!\n");
            menu(Labyrinth, Player);
            break;
    }
}

void saveGame(Labyrinth_t * Labyrinth, Player_t * Player)
{
    FILE * file;
    file = fopen("save.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(file, "%c", Labyrinth->labyrinthlayout[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    fprintf(file, "%d %d %d %d %d %d", Player->position.x, Player->position.y, Player->health, Player->attack, Player->defense, Player->money);
}

void loadGame(Labyrinth_t * Labyrinth, Player_t * Player)
{
    FILE * file;
    file = fopen("save.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    char c;
    int i = 0;
    int j = 0;
    while ((c = fgetc(file)) != EOF && i < 10)
    {
        if (c == '\n')
        {
            i++;
            j = 0;
        }
        else
        {   
            Labyrinth->labyrinthlayout[i][j] = c;
            j++;
        }
    }

    fscanf(file, "%d %d %d %d %d %d", &Player->position.x, &Player->position.y, &Player->health, &Player->attack, &Player->defense, &Player->money);
}