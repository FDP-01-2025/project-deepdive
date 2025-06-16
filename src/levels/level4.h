#ifndef LEVEL4_H
#define LEVEL4_H
#define MAX_MISSILES 100

// Llamada de bibliotecas para acceder a sus funciones.
#include "../headers/position.h"
#include "../headers/hide_cursor.h"
#include "../headers/game_limits.h"
#include "../headers/submarine.h"
#include "../headers/mines.h"
#include "../headers/missiles.h"
#include "../headers/fish.h"
#include <conio.h>

// Declaración de variables globales como estaticas, para que no den conflicto en múltiples inclusiones.
static Submarine Level4Submarine;
static Fish Level4Fishes[3];
static int Level4NumFishes;
static Mines Level4Mines1;
static Missiles Level4Missiles[MAX_MISSILES];
static int Level4MissilesCout;

// Funciones estáticas definidas en el .h
static void InitGamelevel4()
{
    Level4Submarine = {5, 15, 1, 3};
    PaintSubmarine(&Level4Submarine);
    PaintHearts(&Level4Submarine);

    Level4Fishes[0] = {90, 3};
    Level4Fishes[1] = {80, 12};
    Level4Fishes[2] = {100, 17};
    
    Level4NumFishes = 3;

    Level4Mines1 = {100, 25};

    Level4MissilesCout = 0;
}

static void GameLooplevel4()
{
    do
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 112 || tecla == 80)
            {
                if (Level4MissilesCout < MAX_MISSILES)
                {
                    Level4Missiles[Level4MissilesCout].x = Level4Submarine.x + 12;
                    Level4Missiles[Level4MissilesCout].y = Level4Submarine.y + 2;
                    Level4MissilesCout++;
                }
            }
            MoveSubmarine(tecla, &Level4Submarine);
        }

        for (int i = 0; i < Level4MissilesCout;)
        {
            MoveMissil(Level4Missiles[i]);
            if (Level4Missiles[i].x >= 115)
            {
                gotoxy(Level4Missiles[i].x, Level4Missiles[i].y);
                cout << ("  ") << endl;

                Level4Missiles[i] = Level4Missiles[Level4MissilesCout - 1];
                Level4MissilesCout--;
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < Level4MissilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < Level4NumFishes; j++)
            {
                if ((Level4Missiles[i].x == Level4Fishes[j].x || Level4Missiles[i].x == Level4Fishes[j].x + 3 || Level4Missiles[i].x == Level4Fishes[j].x + 6) && Level4Missiles[i].y == Level4Fishes[j].y)
                {
                    gotoxy(Level4Missiles[i].x, Level4Missiles[i].y);
                    cout << ("  ") << endl;
                    Level4Missiles[i] = Level4Missiles[Level4MissilesCout - 1];
                    Level4MissilesCout--;
                    erasedMissil = true;

                    gotoxy(Level4Fishes[j].x, Level4Fishes[j].y);
                    cout << ("         ") << endl;
                    Level4Fishes[j].x = 110;
                    Level4Fishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        MoveMines(&Level4Mines1);

        for (int i = 0; i < Level4NumFishes; i++)
        {
            MoveFish(&Level4Fishes[i]);
            CollisionFish(&Level4Fishes[i], &Level4Submarine);
        }

        Sleep(5);
    } while (Level4Submarine.lifes > 0);
}

#endif