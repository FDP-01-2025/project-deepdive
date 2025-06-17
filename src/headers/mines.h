#ifndef MINES_H_INCLUDED
#define MINES_H_INCLUDED

#include <iostream> // Asegúrate de que esté incluido si no lo está en position.h
#include "position.h"

typedef struct
{
    int x, y;
} Mines;

void PaintMines(Mines &mines)
{
    gotoxy(mines.x, mines.y);
    std::cout << ' ' << (char)46 << (char)45 << (char)45 << (char)46 << ' ';
    gotoxy(mines.x, mines.y + 1);
    std::cout << (char)47 << ' ' << (char)88 << (char)88 << ' ' << (char)92;
    gotoxy(mines.x, mines.y + 2);
    std::cout << (char)96 << (char)45 << (char)45 << (char)45 << (char)45 << (char)39;
}

void MoveMines(Mines &mines)
{
    gotoxy(mines.x, mines.y);
    std::cout << "      ";
    gotoxy(mines.x, mines.y + 1);
    std::cout << "      ";
    gotoxy(mines.x, mines.y + 2);
    std::cout << "      ";

    mines.x--;
    if (mines.x <= 5)
    {
        mines.x = 110;
    }

    PaintMines(mines);
}

#endif
