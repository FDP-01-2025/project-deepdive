#ifndef MISSILES_H_INCLUDED
#define MISSILES_H_INCLUDED
#include "../headers/position.h"

typedef struct
{
    int x, y;
} Missiles;

void MoveMissil(Missiles &missiles)
{
    gotoxy(missiles.x, missiles.y);
    printf(" ");
    if (missiles.x < 115)
    {
        missiles.x++;
        gotoxy(missiles.x, missiles.y);
        printf("->");
    }
}

#endif