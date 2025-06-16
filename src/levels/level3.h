#ifndef LEVEL3_H
#define LEVEL3_H
#define MAX_MISSILES 100

// Llamada de bibliotecas para acceder a sus funciones.
#include "../headers/position.h"
#include "../headers/hide_cursor.h"
#include "../headers/game_limits.h"
#include "../headers/submarine.h"
#include "../headers/mines.h"
#include "../headers/missiles.h"
#include <conio.h>

// Declaración de variables globales como estaticas, para que no den conflicto en múltiples inclusiones.
static Submarine Level3Submarine;
static Fish Level3Fishes[3];
static int Level3NumFishes;
static Mines Level3Mines1;
static Missiles Level3Missiles[MAX_MISSILES];
static int Level3MissilesCout;

// Funciones estáticas definidas en el .h
static void InitGamelevel3()
{
    Level3Submarine = {5, 15, 1, 3};
    PaintSubmarine(&Level3Submarine);
    PaintHearts(&Level3Submarine);

    Level3Fishes[0] = {90, 3};
    Level3Fishes[1] = {80, 12};
    Level3Fishes[2] = {100, 17};
    
    Level3NumFishes = 3;

    Level3Mines1 = {100, 25};

    Level3MissilesCout = 0;
}

static void GameLooplevel3()
{
    do
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 112 || tecla == 80)
            {
                if (Level3MissilesCout < MAX_MISSILES)
                {
                    Level3Missiles[Level3MissilesCout].x = Level3Submarine.x + 12;
                    Level3Missiles[Level3MissilesCout].y = Level3Submarine.y + 2;
                    Level3MissilesCout++;
                }
            }
            MoveSubmarine(tecla, &Level3Submarine);
        }

        for (int i = 0; i < Level3MissilesCout;)
        {
            MoveMissil(Level3Missiles[i]);
            if (Level3Missiles[i].x >= 115)
            {
                gotoxy(Level3Missiles[i].x, Level3Missiles[i].y);
                cout << ("  ") << endl;

                Level3Missiles[i] = Level3Missiles[Level3MissilesCout - 1];
                Level3MissilesCout--;
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < Level3MissilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < Level3NumFishes; j++)
            {
                if ((Level3Missiles[i].x == Level3Fishes[j].x || Level3Missiles[i].x == Level3Fishes[j].x + 3 || Level3Missiles[i].x == Level3Fishes[j].x + 6) && Level3Missiles[i].y == Level3Fishes[j].y)
                {
                    gotoxy(Level3Missiles[i].x, Level3Missiles[i].y);
                    cout << ("  ") << endl;
                    Level3Missiles[i] = Level3Missiles[Level3MissilesCout - 1];
                    Level3MissilesCout--;
                    erasedMissil = true;

                    gotoxy(Level3Fishes[j].x, Level3Fishes[j].y);
                    cout << ("         ") << endl;
                    Level3Fishes[j].x = 110;
                    Level3Fishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        MoveMines(&Level3Mines1);

        for (int i = 0; i < Level3NumFishes; i++)
        {
            MoveFish(&Level3Fishes[i]);
            CollisionFish(&Level3Fishes[i], &Level3Submarine);
        }

        Sleep(5);
    } while (Level3Submarine.lifes > 0);
}

#endif