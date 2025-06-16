#ifndef LEVEL2_H
#define LEVEL2_H
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
static Submarine Level2Submarine;
static Fish Level2Fishes[3];
static int Level2NumFishes;
static Mines Level2Mines1;
static Missiles Level2Missiles[MAX_MISSILES];
static int Level2MissilesCout;

// Funciones estáticas definidas en el .h
static void InitGamelevel2()
{
    Level2Submarine = {5, 15, 1, 3};
    PaintSubmarine(&Level2Submarine);
    PaintHearts(&Level2Submarine);

    Level2Fishes[0] = {90, 3};
    Level2Fishes[1] = {80, 12};
    Level2Fishes[2] = {100, 17};
    
    Level2NumFishes = 3;

    Level2Mines1 = {100, 25};

    Level2MissilesCout = 0;
}

static void GameLooplevel2()
{
    do
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 112 || tecla == 80)
            {
                if (Level2MissilesCout < MAX_MISSILES)
                {
                    Level2Missiles[Level2MissilesCout].x = Level2Submarine.x + 12;
                    Level2Missiles[Level2MissilesCout].y = Level2Submarine.y + 2;
                    Level2MissilesCout++;
                }
            }
            MoveSubmarine(tecla, &Level2Submarine);
        }

        for (int i = 0; i < Level2MissilesCout;)
        {
            MoveMissil(Level2Missiles[i]);
            if (Level2Missiles[i].x >= 115)
            {
                gotoxy(Level2Missiles[i].x, Level2Missiles[i].y);
                cout << ("  ") << endl;

                Level2Missiles[i] = Level2Missiles[Level2MissilesCout - 1];
                Level2MissilesCout--;
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < Level2MissilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < Level2NumFishes; j++)
            {
                if ((Level2Missiles[i].x == Level2Fishes[j].x || Level2Missiles[i].x == Level2Fishes[j].x + 3 || Level2Missiles[i].x == Level2Fishes[j].x + 6) && Level2Missiles[i].y == Level2Fishes[j].y)
                {
                    gotoxy(Level2Missiles[i].x, Level2Missiles[i].y);
                    cout << ("  ") << endl;
                    Level2Missiles[i] = Level2Missiles[Level2MissilesCout - 1];
                    Level2MissilesCout--;
                    erasedMissil = true;

                    gotoxy(Level2Fishes[j].x, Level2Fishes[j].y);
                    cout << ("         ") << endl;
                    Level2Fishes[j].x = 110;
                    Level2Fishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        MoveMines(&Level2Mines1);

        for (int i = 0; i < Level2NumFishes; i++)
        {
            MoveFish(&Level2Fishes[i]);
            CollisionFish(&Level2Fishes[i], &Level2Submarine);
        }

        Sleep(5);
    } while (Level2Submarine.lifes > 0);
}

#endif