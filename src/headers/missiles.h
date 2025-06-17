#ifndef MISSILES_H_INCLUDED
#define MISSILES_H_INCLUDED
#include "position.h"
#include <iostream>

typedef struct
{
    int x, y;
} Missiles;

void MoveMissil(Missiles &missiles)
{
    gotoxy(missiles.x, missiles.y);
    std::cout << (" ") << "\n";
    if (missiles.x < 115)
    {
        missiles.x++;
        gotoxy(missiles.x, missiles.y);
        std::cout << ("->") << "\n";
    }
}

#endif