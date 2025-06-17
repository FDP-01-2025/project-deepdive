#ifndef LEVEL2_H
#define LEVEL2_H
#include "../headers/fish.h"
#include "../headers/pieces.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.

static Submarine level2Submarine;
static Fish level2Fishes[4];
static int level2Numfishes;
static pieces level2Pieces[1];
static int level2NumPieces;
//Numero de Piezas


static void InitGamelevel2Mode()
{
    level2Submarine = {5, 15, 1, 3};
    PaintSubmarine(level2Submarine);
    PaintHearts(level2Submarine);

    level2Fishes[0] = {80, 3};
    level2Fishes[1] = {90, 10};
    level2Fishes[2] = {100, 15};
    level2Fishes[3] = {110, 20};
    level2Numfishes = 4;

    level2Pieces[0] = {80, 3};
    level2NumPieces = 1;
    
}

static void GameLooplevel2Mode()
{
    do
    {
        // para que en la siguiente vuelta se mida el nuevo deltaTime correctamente
        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, level2Submarine);
        }

        for (int i = 0; i < level2Numfishes; i++)
        {
            MoveFish(level2Fishes[i]);
            CollisionFish(level2Fishes[i], level2Submarine);
        }
        for (int i = 0; i < level2NumPieces; i++)
        {
            Movepieces(level2Pieces[i]);
            Collisionpieces(level2Pieces[i], level2Submarine);
        }
        Sleep(5);

    } while (level2Submarine.lifes > 0);
}

#endif
