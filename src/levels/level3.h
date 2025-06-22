#ifndef LEVEL3_H
#define LEVEL3_H

#include "../headers/fish.h"
#include "../headers/messages.h"
#include "../headers/submarine.h"
#include <chrono>

static Submarine level3Submarine;
static Submarine allySubmarine;
static Fish level3Fishes[4];
static int level3NumFishes;

void PaintAllyFish(Submarine &ally)
{
    gotoxy(ally.x, ally.y);
    std::cout << "><(((°>";
}

void DeleteAllyFish(Submarine &ally)
{
    gotoxy(ally.x, ally.y);
    std::cout << "       ";
}


static void InitGameLevel3()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    PrincipalObjectiveLevel3();

    SetConsoleCursorPosition(hConsole, {0, 1});
    std::cout << "Principal Objective: Escort the ally submarine for 3 minutes!";

    level3Submarine = {5, 15, 3, 3, 10}; // Submarino controlado por usuario
    allySubmarine = {5, 18, 0, 1, 0};    // Aliado a proteger

    PaintSubmarine(level3Submarine);
    PaintAllyFish(allySubmarine);
    PaintHearts(level3Submarine);

    level3Fishes[0] = {80, 3};
    level3Fishes[1] = {90, 10};
    level3Fishes[2] = {100, 15};
    level3Fishes[3] = {110, 20};
    level3NumFishes = 4;
}

static void GameLoopLevel3()
{
    using namespace std::chrono;
    auto startTime = steady_clock::now();

    do
    {
        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, level3Submarine);
        }

        // Mover aliado detrás del jugador
        DeleteAllyFish(allySubmarine);
        allySubmarine.x = level3Submarine.x;
        allySubmarine.y = level3Submarine.y + 3;
        PaintAllyFish(allySubmarine);

        for (int i = 0; i < level3NumFishes; i++)
        {
            MoveFish(level3Fishes[i]);
            CollisionFish(level3Fishes[i], level3Submarine);

            // Si el aliado es tocado, pierde
            if (level3Fishes[i].x == allySubmarine.x &&
                (level3Fishes[i].y == allySubmarine.y || level3Fishes[i].y == allySubmarine.y + 1))
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {40, 15});
                std::cout << "¡El submarino aliado fue destruido!";
                Sleep(3000);
                return;
            }
        }

        // Verificar si pasaron 3 minutos
        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime).count();
        if (elapsed >= 180)
        {
            CongratsLevel3();
            return;
        }

        Sleep(13);

    } while (level3Submarine.lifes > 0);
}

#endif
