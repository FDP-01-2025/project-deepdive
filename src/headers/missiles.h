#ifndef MISSILES_H_INCLUDED
#define MISSILES_H_INCLUDED
#include "position.h"
#include <iostream>

// Structure representing a missile's position
typedef struct
{
    int x, y;
} Missiles;
// Function to move the missile forward (to the right)
void MoveMissil(Missiles &missiles)
{
    gotoxy(missiles.x, missiles.y);
    std::cout << (" ") << "\n";
    if (missiles.x < 115)
    {
        // Draw the missile at the new position
        missiles.x++;
        gotoxy(missiles.x, missiles.y);
        std::cout << ("=>") << "\n";
    }
}

#endif