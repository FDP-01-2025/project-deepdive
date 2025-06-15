#ifndef GAME_PROCESSES_H
#define GAME_PROCESSES_H
#define MAX_MISSILES 100

// Llamada de bibliotecas para acceder a sus funciones.
#include "headers/position.h"
#include "headers/hide_cursor.h"
#include "headers/game_limits.h"
#include "headers/submarine.h"
#include "headers/fish.h"
#include "headers/mines.h"
#include "headers/missiles.h"

using namespace std;

// Declaración de variables globales como estaticas, para que no den conflicto en múltiples inclusiones.
static Submarine submarine;
static Fish fishes[3];
static int num_fishes;
static Mines mines1;
static Missiles missiles[MAX_MISSILES];
static int missilesCout;

// Funciones estáticas definidas en el .h
static void InitGame()
{
    submarine = {5, 15, 1, 3};
    PaintSubmarine(&submarine);
    PaintHearts(&submarine);

    fishes[0] = {90, 3};
    fishes[1] = {80, 12};
    fishes[2] = {100, 17};
    
    num_fishes = 3;

    mines1 = {100, 25};

    missilesCout = 0;
}

static void GameLoop()
{
    do
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 112 || tecla == 80)
            {
                if (missilesCout < MAX_MISSILES)
                {
                    missiles[missilesCout].x = submarine.x + 12;
                    missiles[missilesCout].y = submarine.y + 2;
                    missilesCout++;
                }
            }
            MoveSubmarine(tecla, &submarine);
        }

        for (int i = 0; i < missilesCout;)
        {
            MoveMissil(missiles[i]);
            if (missiles[i].x >= 115)
            {
                gotoxy(missiles[i].x, missiles[i].y);
                cout << ("  ") << endl;

                missiles[i] = missiles[missilesCout - 1];
                missilesCout--;
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < missilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < num_fishes; j++)
            {
                if ((missiles[i].x == fishes[j].x || missiles[i].x == fishes[j].x + 3 || missiles[i].x == fishes[j].x + 6) && missiles[i].y == fishes[j].y)
                {
                    gotoxy(missiles[i].x, missiles[i].y);
                    cout << ("  ") << endl;
                    missiles[i] = missiles[missilesCout - 1];
                    missilesCout--;
                    erasedMissil = true;

                    gotoxy(fishes[j].x, fishes[j].y);
                    cout << ("         ") << endl;
                    fishes[j].x = 110;
                    fishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        MoveMines(&mines1);

        for (int i = 0; i < num_fishes; i++)
        {
            MoveFish(&fishes[i]);
            CollisionFish(&fishes[i], &submarine);
        }

        Sleep(15);
    } while (submarine.lifes > 0);
}
#endif