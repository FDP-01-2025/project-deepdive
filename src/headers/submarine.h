#ifndef SUBMARINE_H_INCLUDED
#define SUBMARINE_H_INCLUDED

#include <iostream>
#include <windows.h>
#include "position.h"
using namespace std;

// Se definen las teclas A, W, S, D en mayúsculas y minúsculas
#define UP 87
#define DOWN 83
#define LEFT 65
#define RIGHT 68

#define UPlc 119
#define DOWNlc 115
#define LEFTlc 97
#define RIGHTlc 100

typedef struct
{
    int x, y, heart, lifes;
} Submarine;

/* Pinta al submarino con caracteres del código ASCII */
void PaintSubmarine(Submarine &submarine)
{
    gotoxy(submarine.x, submarine.y);
    cout << "       " << (char)95 << (char)218;
    gotoxy(submarine.x, submarine.y + 1);
    cout << ' ' << (char)126 << (char)42 << (char)95 << (char)95 << (char)95
         << (char)47 << (char)111 << (char)111 << (char)92 << (char)95;
    gotoxy(submarine.x, submarine.y + 2);
    cout << "  " << (char)40 << (char)95 << (char)95 << (char)95 << (char)95
         << (char)95 << (char)95 << (char)95 << (char)95 << (char)41;
}

/* Borra al submarino en cada desplazamiento */
void DeleteSubmarine(Submarine &submarine)
{
    gotoxy(submarine.x, submarine.y);
    cout << "         ";
    gotoxy(submarine.x, submarine.y + 1);
    cout << "           ";
    gotoxy(submarine.x, submarine.y + 2);
    cout << "            ";
}

/* Pinta la vida y los corazones del submarino */
void PaintHearts(Submarine &submarine)
{
    gotoxy(80, 1);
    cout << "Vidas " << submarine.lifes;
    gotoxy(100, 1);
    cout << "Salud";
    gotoxy(110, 1);
    cout << "     ";

    for (int i = 0; i < submarine.heart; i++)
    {
        gotoxy(110 + i, 1);
        cout << (char)223;
    }
}

/* Si los corazones del submarino llegan a 0, se pinta una explosión animada */
void DestroySubmarine(Submarine &submarine)
{
    if (submarine.heart == 0)
    {
        DeleteSubmarine(submarine);
        gotoxy(submarine.x, submarine.y);
        cout << " * * * * ";
        gotoxy(submarine.x, submarine.y + 1);
        cout << "********";
        gotoxy(submarine.x, submarine.y + 2);
        cout << " * * * * ";
        Sleep(350);
        DeleteSubmarine(submarine);
        gotoxy(submarine.x, submarine.y);
        cout << "*    *";
        gotoxy(submarine.x, submarine.y + 1);
        cout << " * * * * ";
        gotoxy(submarine.x, submarine.y + 2);
        cout << "*    *";
        Sleep(350);
        DeleteSubmarine(submarine);
        submarine.lifes--;
        PaintHearts(submarine);
        submarine.heart = 1;
        PaintSubmarine(submarine);
    }
}

/* Movimiento del submarino en base a las teclas presionadas */
void MoveSubmarine(char tecla, Submarine &submarine)
{
    DeleteSubmarine(submarine);

    if ((tecla == LEFT || tecla == LEFTlc) && submarine.x > 3)
        submarine.x--;
    if ((tecla == RIGHT || tecla == RIGHTlc) && submarine.x < 106)
        submarine.x++;
    if ((tecla == UP || tecla == UPlc) && submarine.y > 3)
        submarine.y--;
    if ((tecla == DOWN || tecla == DOWNlc) && submarine.y < 25)
        submarine.y++;

    PaintSubmarine(submarine);
}

#endif
