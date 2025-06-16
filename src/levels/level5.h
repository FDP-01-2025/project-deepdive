#ifndef LEVEL5_H
#define LEVEL5_H
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
static Submarine Level5Submarine;
static Fish Level5Fishes[3];
static int Level5NumFishes;
static Mines Level5Mines1;
static Missiles Level5Missiles[MAX_MISSILES];
static int Level5MissilesCout;

// Funciones estáticas definidas en el .h
static void InitGamelevel5()
{
    Level5Submarine = {5, 15, 1, 3};
    PaintSubmarine(&Level5Submarine);
    PaintHearts(&Level5Submarine);

    Level5Fishes[0] = {90, 3};
    Level5Fishes[1] = {80, 12};
    Level5Fishes[2] = {100, 17};
    
    Level5NumFishes = 3;

    Level5Mines1 = {100, 25};

    Level5MissilesCout = 0;
}

static void GameLooplevel5()
{
    do
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 112 || tecla == 80)
            {
                if (Level5MissilesCout < MAX_MISSILES)
                {
                    Level5Missiles[Level5MissilesCout].x = Level5Submarine.x + 12;
                    Level5Missiles[Level5MissilesCout].y = Level5Submarine.y + 2;
                    Level5MissilesCout++;
                }
            }
            MoveSubmarine(tecla, &Level5Submarine);
        }

        for (int i = 0; i < Level5MissilesCout;)
        {
            MoveMissil(Level5Missiles[i]);
            if (Level5Missiles[i].x >= 115)
            {
                gotoxy(Level5Missiles[i].x, Level5Missiles[i].y);
                cout << ("  ") << endl;

                Level5Missiles[i] = Level5Missiles[Level5MissilesCout - 1];
                Level5MissilesCout--;
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < Level5MissilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < Level5NumFishes; j++)
            {
                if ((Level5Missiles[i].x == Level5Fishes[j].x || Level5Missiles[i].x == Level5Fishes[j].x + 3 || Level5Missiles[i].x == Level5Fishes[j].x + 6) && Level5Missiles[i].y == Level5Fishes[j].y)
                {
                    gotoxy(Level5Missiles[i].x, Level5Missiles[i].y);
                    cout << ("  ") << endl;
                    Level5Missiles[i] = Level5Missiles[Level5MissilesCout - 1];
                    Level5MissilesCout--;
                    erasedMissil = true;

                    gotoxy(Level5Fishes[j].x, Level5Fishes[j].y);
                    cout << ("         ") << endl;
                    Level5Fishes[j].x = 110;
                    Level5Fishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        MoveMines(&Level5Mines1);

        for (int i = 0; i < Level5NumFishes; i++)
        {
            MoveFish(&Level5Fishes[i]);
            CollisionFish(&Level5Fishes[i], &Level5Submarine);
        }

        Sleep(5);
    } while (Level5Submarine.lifes > 0);
}

#endif