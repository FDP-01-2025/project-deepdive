#ifndef MINES_H_INCLUDED
#define MINES_H_INCLUDED
#include "../headers/position.h"
typedef struct
{
    int x, y;
} Mines;


void PaintMines(Mines *mines)
{
    gotoxy(mines->x, mines->y);
    printf(" %c%c%c%c ", 46, 45, 45, 46);
    gotoxy(mines->x, mines->y + 1);
    printf("%c %c%c %c", 47, 88, 88, 92);
    gotoxy(mines->x, mines->y + 2);
    printf("%c%c%c%c%c%c", 96, 45, 45, 45, 45, 39);
}

void MoveMines(Mines *mines)
{
    gotoxy(mines->x, mines->y);
    printf("      ");
    gotoxy(mines->x, mines->y + 1);
    printf("      ");
    gotoxy(mines->x, mines->y + 2);
    printf("      ");
    mines->x--;
    if (mines->x <= 5)
    {
        mines->x = 110;
        mines->y;
    }
    PaintMines(mines);
}

#endif