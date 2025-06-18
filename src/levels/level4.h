#ifndef LEVEL4_H
#define LEVEL4_H
#define MAX_MISSILES 100

// Llamada de bibliotecas para acceder a sus funciones.
#include "headers/position.h"
#include "headers/hide_cursor.h"
#include "headers/game_limits.h"
#include "headers/submarine.h"

#include "headers/missiles.h"
#include "headers/fish.h"
#include <conio.h>

// Declaración de variables globales como estaticas, para que no den conflicto en múltiples inclusiones.
static Submarine level4Submarine;
static Fish level4Fishes[3];
static int level4NumFishes;

static Missiles level4Missiles[MAX_MISSILES];
static int level4MissilesCout;

// Funciones estáticas definidas en el .h
static void InitGameLevel4()
{
    level4Submarine = {5, 15, 1, 3};
    PaintSubmarine(level4Submarine);
    PaintHearts(level4Submarine);

    level4Fishes[0] = {90, 3};
    level4Fishes[1] = {80, 12};
    level4Fishes[2] = {100, 17};

    level4NumFishes = 3;

    level4MissilesCout = 0;
}

static void GameLoopLevel4()
{
    do
    {
        HideCursor();
        GameLimits();
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 32)
            {
                if (level4MissilesCout < MAX_MISSILES)
                {
                    level4Missiles[level4MissilesCout].x = level4Submarine.x + 12;
                    level4Missiles[level4MissilesCout].y = level4Submarine.y + 2;
                    level4MissilesCout++;
                }
            }
            MoveSubmarine(tecla, level4Submarine);
        }

        for (int i = 0; i < level4MissilesCout;)
        {
            MoveMissil(level4Missiles[i]);
            if (level4Missiles[i].x >= 115)
            {
                gotoxy(level4Missiles[i].x, level4Missiles[i].y);
                std::cout << ("  ") << std::endl;

                level4Missiles[i] = level4Missiles[level4MissilesCout - 1];
                level4MissilesCout--;
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < level4MissilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < level4NumFishes; j++)
            {
                if ((level4Missiles[i].x == level4Fishes[j].x || level4Missiles[i].x == level4Fishes[j].x + 3 || level4Missiles[i].x == level4Fishes[j].x + 6) && level4Missiles[i].y == level4Fishes[j].y)
                {
                    gotoxy(level4Missiles[i].x, level4Missiles[i].y);
                    std::cout << ("  ") << std::endl;
                    level4Missiles[i] = level4Missiles[level4MissilesCout - 1];
                    level4MissilesCout--;
                    erasedMissil = true;

                    gotoxy(level4Fishes[j].x, level4Fishes[j].y);
                    std::cout << ("         ") << std::endl;
                    level4Fishes[j].x = 110;
                    level4Fishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        

        for (int i = 0; i < level4NumFishes; i++)
        {
            MoveFish(level4Fishes[i]);
            CollisionFish(level4Fishes[i], level4Submarine);
        }

        Sleep(5);
    } while (level4Submarine.lifes > 0);
}

#endif
