#ifndef TEST_LEVEL_H_INCLUDED
#define TEST_LEVEL_H_INCLUDED
#define MAX_MISSILES 100

// Llamada de bibliotecas para acceder a sus funciones.
#include "headers/position.h"
#include "headers/hide_cursor.h"
#include "headers/game_limits.h"
#include "headers/submarine.h"
#include "headers/mines.h"
#include "headers/missiles.h"
#include "headers/fish.h"
#include <conio.h>

// Declaración de variables globales como estaticas, para que no den conflicto en múltiples inclusiones.
static Submarine testLevelSubmarine;
static Fish testLevelFishes[3];
static int testLevelNumFishes;
static Mines testLevelMines1;
static Missiles testLevelMissiles[MAX_MISSILES];
static int testLevelMissilesCout;

// Funciones estáticas definidas en el .h
static void InitGameTL()
{
    testLevelSubmarine = {5, 15, 1, 3};
    PaintSubmarine(testLevelSubmarine);
    PaintHearts(testLevelSubmarine);

    testLevelFishes[0] = {90, 3};
    testLevelFishes[1] = {80, 12};
    testLevelFishes[2] = {100, 17};
    
    testLevelNumFishes = 3;

    testLevelMines1 = {100, 25};

    testLevelMissilesCout = 0;
}

static void GameLoopTL()
{
    do
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 112 || tecla == 80)
            {
                if (testLevelMissilesCout < MAX_MISSILES)
                {
                    testLevelMissiles[testLevelMissilesCout].x = testLevelSubmarine.x + 12;
                    testLevelMissiles[testLevelMissilesCout].y = testLevelSubmarine.y + 2;
                    testLevelMissilesCout++;
                }
            }
            MoveSubmarine(tecla, testLevelSubmarine);
        }

        for (int i = 0; i < testLevelMissilesCout;)
        {
            MoveMissil(testLevelMissiles[i]);
            if (testLevelMissiles[i].x >= 115)
            {
                gotoxy(testLevelMissiles[i].x, testLevelMissiles[i].y);
                std::cout << ("  ") << std::endl;

                testLevelMissiles[i] = testLevelMissiles[testLevelMissilesCout - 1];
                testLevelMissilesCout--;
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < testLevelMissilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < testLevelNumFishes; j++)
            {
                if ((testLevelMissiles[i].x == testLevelFishes[j].x || testLevelMissiles[i].x == testLevelFishes[j].x + 3 || testLevelMissiles[i].x == testLevelFishes[j].x + 6) && testLevelMissiles[i].y == testLevelFishes[j].y)
                {
                    gotoxy(testLevelMissiles[i].x, testLevelMissiles[i].y);
                    std::cout << ("  ") << std::endl;
                    testLevelMissiles[i] = testLevelMissiles[testLevelMissilesCout - 1];
                    testLevelMissilesCout--;
                    erasedMissil = true;

                    gotoxy(testLevelFishes[j].x, testLevelFishes[j].y);
                    std::cout << ("         ") << std::endl;
                    testLevelFishes[j].x = 110;
                    testLevelFishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        MoveMines(testLevelMines1);

        for (int i = 0; i < testLevelNumFishes; i++)
        {
            MoveFish(testLevelFishes[i]);
            CollisionFish(testLevelFishes[i], testLevelSubmarine);
        }

        Sleep(5);
    } while (testLevelSubmarine.lifes > 0);
}

#endif