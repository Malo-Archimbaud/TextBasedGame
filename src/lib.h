#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum TileType
{
    W, // Wall
    P, // Path
    E, // Enemy
    B, // Blessing
    T, // Trap
    F, // Boss
    C, // Characters
};

int Labyrinth[10][10] = 
{   W, W, W, W, W, W, P, W, W, W,
    W, B, E, P, W, W, F, P, B, W,
    W, W, W, P, T, W, W, W, B, W,
    W, B, P, E, W, W, W, W, P, W,
    W, T, W, P, E, B, P, W, P, W,
    W, B, W, W, P, W, B, P, E, W,
    W, E, P, W, P, W, T, W, P, W,
    W, W, E, P, E, P, E, W, P, W,
    W, C, B, W, W, W, P, T, B, W,
    W, W, W, W, W, W, W, W, W, W };

/*
w, w, w, w, w, w, w, ., w, w,
w, ., ., ., w, ., ., ., ., w,
w, w, w, ., ., w, ., w, ., w,
w, ., ., ., w, w, w, w, ., w,
w, ., w, ., ., ., w, w, ., w,
w, ., w, w, ., w, ., ., ., w,
w, ., ., w, ., w, ., w, ., w,
w, w, ., ., ., ., ., w, ., w,
w, ., ., w, w, w, ., ., ., w,
w, w, w, w, w, w, w, w, w, w
*/

void printLab(int lab[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
        for (int j = 0; j < 10; j++)
        {
            switch(lab[i][j]){
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
                    printf("c ");
                    break;
            }
        }
    }
}