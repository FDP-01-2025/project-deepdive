#ifndef GAME_LIMITS_H_INCLUDED
#define GAME_LIMITS_H_INCLUDED
#include "position.h"
#include <iostream>

/* Pinta los límites del escenario de juego */

void GameLimits()
{
    // Parte horizontal
    for (int i = 2; i < 120; i++)
    {
        gotoxy(i, 2);
        std::cout << (char)205;
        gotoxy(i, 28);
        std::cout << (char)205;
    }

    // Parte vertical
    for (int j = 2; j < 28; j++)
    {
        gotoxy(2, j);
        std::cout << (char)186;
        gotoxy(119, j);
        std::cout << (char)186;
    }

    // Esquinas
    gotoxy(2, 2);
    std::cout << (char)201;
    gotoxy(119, 2);
    std::cout << (char)187;
    gotoxy(2, 28);
    std::cout << (char)200;
    gotoxy(119, 28);
    std::cout << (char)188;
}

#endif
