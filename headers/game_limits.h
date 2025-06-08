#ifndef GAME_LIMITS_H_INCLUDED
#define GAME_LIMITS_H_INCLUDED
#include <stdio.h>
#include "../headers/move_cursor.h"

/*Pinta los límites del escenario de juego*/
void GameLimits()
{
    for (int i = 2; i < 120; i++)
    {
        gotoxy(i, 2);
        printf("%c", 205);
        gotoxy(i, 28);
        printf("%c", 205);
    }
    for (int j = 2; j < 28; j++)
    {
        gotoxy(2, j);
        printf("%c", 186);
        gotoxy(119, j);
        printf("%c", 186);
    }

    gotoxy(2, 2);
    printf("%c", 201);
    gotoxy(119, 2);
    printf("%c", 187);
    gotoxy(2, 28);
    printf("%c", 200);
    gotoxy(119, 28);
    printf("%c", 188);
}

#endif