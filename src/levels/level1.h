#ifndef LEVEL1_H
#define LEVEL1_H
#include "../headers/fish.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.

static Submarine level1Submarine;
static Fish level1Fishes[4];
static int level1_num_fishes;

static void InitGamelevel1()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 7);       // Color blanco predeterminado
    SetConsoleCursorPosition(hConsole, {0, 0}); // Cursor en la esquina superior izquierda

    level1Submarine = {5, 15, 1, 3};
    PaintSubmarine(level1Submarine);
    PaintHearts(level1Submarine);

    level1Fishes[0] = {80, 3};
    level1Fishes[1] = {90, 10};
    level1Fishes[2] = {100, 15};
    level1Fishes[3] = {110, 20};
    level1_num_fishes = 4;
}

static void GameLooplevel1()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 7);       // Color blanco predeterminado
    SetConsoleCursorPosition(hConsole, {0, 0}); // Cursor en la esquina superior izquierda

    do
    {
        // para que en la siguiente vuelta se mida el nuevo deltaTime correctamente
        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, level1Submarine);
        }

        for (int i = 0; i < level1_num_fishes; i++)
        {
            MoveFish(level1Fishes[i]);
            CollisionFish(level1Fishes[i], level1Submarine);
        }
        Sleep(5);

    } while (level1Submarine.lifes > 0);
}

#endif
