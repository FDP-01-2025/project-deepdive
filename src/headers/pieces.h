#ifndef PIECES_H
#define PIECES_H
#include "position.h"
#include "submarine.h"
#include <iostream>
static int sleepTime=13;

typedef struct
{
    int x, y;
} pieces;

 void Victorylevel2(); 

// Paint the shape of the piece
void Paintpieces(pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("(@)") << "\n";
}

// Delete the shape of the piece
void Deletepieces(pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("        ") << "\n";
}

void Movepieces(pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("        ") << "\n";
    /*.*/
    pieces.x--;
    if (pieces.x <= 5)
    {
        pieces.x = 110;
        pieces.y = rand() % 10 + 3;
    }
    Paintpieces(pieces);
}

/*The space occupied by the submarine is declared in 'x' and 'y', if the position of 'x' and 'y'
coincide, an impact is detected, the health of the submarine is reduced, and the obstacles return to their initial position.*/
void Collisionpieces(pieces &pieces, Submarine &submarine)
{
    if (pieces.x >= submarine.x && pieces.x <= submarine.x + 11 &&
        pieces.y >= submarine.y && pieces.y <= submarine.y + 3)
    {
        // Increase oxygen

        if (submarine.oxygen < 30)
        {
            submarine.oxygen++;
            PaintOxygen(submarine);

            if (sleepTime > 1)
                sleepTime--;

            if (submarine.oxygen >= 30)
            {
                Victorylevel2();
            }
        }
        // Reposition the piece before blinking
        Deletepieces(pieces);
        pieces.x = 110;
        pieces.y = rand() % 10 + 3;

        // Blinking effect
        for (int i = 0; i < 3; i++)
        {
            DeleteSubmarine(submarine);
            Sleep(100);
            PaintSubmarine(submarine, 1);
            Sleep(100);
        }

        // Reposition the piece
        Deletepieces(pieces);
        pieces.x = 110;
        pieces.y = rand() % 10 + 3;
    }
}

#endif
