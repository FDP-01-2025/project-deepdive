#ifndef level3_H
#define level3_H
#include "../headers/fish.h"
#include "../headers/pieces.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.

static Submarine level3Submarine;
static Fish level3Fishes[4];
static int level3_num_fishes;

static void InitGamelevel3Mode()
{
    level3Submarine = {5, 15, 1, 3};
    PaintSubmarine(level3Submarine);
    PaintHearts(level3Submarine);

    level3Fishes[0] = {80, 3};
    level3Fishes[1] = {90, 10};
    level3Fishes[2] = {100, 15};
    level3Fishes[3] = {110, 20};
    level3_num_fishes = 4;
}

static void GameLooplevel3Mode()
{
    do
    {
        // para que en la siguiente vuelta se mida el nuevo deltaTime correctamente
        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, level3Submarine);
        }

        for (int i = 0; i < level3_num_fishes; i++)
        {
            MoveFish(level3Fishes[i]);
            CollisionFish(level3Fishes[i], level3Submarine);
        }
        Sleep(5);

    } while (level3Submarine.lifes > 0);
}

#endif
