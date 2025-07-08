#ifndef PIECES_H
#define PIECES_H
#include "position.h"
#include "submarine.h"
#include <iostream>

typedef struct
{
    int x, y;
} Pieces;

void Victorylevel2();

// Paint the shape of the piece
void Paintpieces(Pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("(@)") << "\n";
}

// Delete the shape of the piece
void Deletepieces(Pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("        ") << "\n";
}

void Movepieces(Pieces &pieces)
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

bool Collition(Pieces &pieces, Submarine &submarine)
{

    return (pieces.x >= submarine.x && pieces.x <= submarine.x + 11 &&
            pieces.y >= submarine.y && pieces.y <= submarine.y + 3);
}
/*The space occupied by the submarine is declared in 'x' and 'y', if the position of 'x' and 'y'
coincide, an impact is detected, the health of the submarine is reduced, and the obstacles return to their initial position.*/
void CollisionPieces(Pieces &pieces, Submarine &submarine)
{
    if (pieces.x >= submarine.x && pieces.x <= submarine.x + 11 &&
        pieces.y >= submarine.y && pieces.y <= submarine.y + 3)
    {
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
