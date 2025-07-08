#ifndef GAME_LIMITS_H_INCLUDED
#define GAME_LIMITS_H_INCLUDED
#include "position.h"
#include <iostream>

/* Paint the boundaries of the playing field. */

void GameLimits()
{
    // Horizontal part
    for (int i = 2; i < 120; i++)
    {
        gotoxy(i, 2);
        std::cout << (char)205; // Top border
        gotoxy(i, 28);
        std::cout << (char)205; // Bottom border
    }

    // Vertical part 
    for (int j = 2; j < 28; j++)  
    {
        gotoxy(2, j);
        std::cout << (char)186;  // Left border
        gotoxy(119, j);
        std::cout << (char)186;  // Right border
    }

    // Corners
    gotoxy(2, 2);
    std::cout << (char)201;  // Top left corner
    gotoxy(119, 2); 
    std::cout << (char)187;  // Top right corner
    gotoxy(2, 28); 
    std::cout << (char)200;  // Bottom left corner
    gotoxy(119, 28);
    std::cout << (char)188;  // Bottom right corner
} 

#endif
