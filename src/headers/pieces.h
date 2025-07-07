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

// Pinta la forma de la pieza
void Paintpieces(pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("(@)") << "\n";
}

// Borra la forma de la pieza
void Deletepieces(pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("        ") << "\n";
}

void Movepieces(pieces &pieces)
{
    gotoxy(pieces.x, pieces.y);
    std::cout << ("        ") << "\n";
    /*Se asigna una posición inicial de la pieza en x, y se genera una posición aleatoria en y.
    La posición de la pieza va decreciendo en x, hasta llegar a la posición 5 en x,
    y luego se vuelve a ejecutar el mismo proceso.*/
    pieces.x--;
    if (pieces.x <= 5)
    {
        pieces.x = 110;
        pieces.y = rand() % 10 + 3;
    }
    Paintpieces(pieces);
}

/*Se declara el espacio que ocupa el submarino en "x" y "y", si la posición de "x" y "y"
coinciden, se detecta un impacto, se reduce la salud del submarino y los obstáculos vuelven a su posición
inicial.*/
void Collisionpieces(pieces &pieces, Submarine &submarine)
{
    if (pieces.x >= submarine.x && pieces.x <= submarine.x + 11 &&
        pieces.y >= submarine.y && pieces.y <= submarine.y + 3)
    {
        // Aumento de oxigeno

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
        // Reposicionar la pieza antes del parpadeo
        Deletepieces(pieces);
        pieces.x = 110;
        pieces.y = rand() % 10 + 3;

        // Efecto de parpadeo
        for (int i = 0; i < 3; i++)
        {
            DeleteSubmarine(submarine);
            Sleep(100);
            PaintSubmarine(submarine, 1);
            Sleep(100);
        }

        // Reposicionar la pieza
        Deletepieces(pieces);
        pieces.x = 110;
        pieces.y = rand() % 10 + 3;
    }
}

#endif
