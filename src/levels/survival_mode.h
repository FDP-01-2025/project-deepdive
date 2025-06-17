#ifndef SURVIVAL_MODE_H_INCLUDED
#define SURVIVAL_MODE_H_INCLUDED
#include "headers/fish.h"
#include "headers/game_time.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.

using namespace std::chrono;
static Submarine survivalSubmarine;
static Fish survivalFishes[4];
static int survival_num_fishes;

static void InitGameSurvivalMode()
{
    survivalSubmarine = {5, 15, 1, 3};
    PaintSubmarine(survivalSubmarine);
    PaintHearts(survivalSubmarine);

    survivalFishes[0] = {80, 3};
    survivalFishes[1] = {90, 10};
    survivalFishes[2] = {100, 15};
    survivalFishes[3] = {110, 20};
    survival_num_fishes = 4;
}

static void GameLoopSurvivalMode()
{
    // Tiempo de inicio
    // Se guarda el tiempo actual al comenzar el juego (marca de inicio)
    high_resolution_clock::time_point startTime = high_resolution_clock::now();

    // Se guarda el tiempo de la "última actualización de fotograma" (frame)
    // Inicialmente, es el mismo que el de inicio
    high_resolution_clock::time_point lastFrameTime = high_resolution_clock::now();
    do
    {
        // Se toma el tiempo actual (inicio de este nuevo ciclo del bucle)
        high_resolution_clock::time_point currentFrameTime = high_resolution_clock::now();
        // Se calcula cuánto tiempo ha pasado desde el último ciclo (frame)
        auto deltaTime = duration_cast<milliseconds>(currentFrameTime - lastFrameTime).count();

        // Se actualiza el tiempo del último ciclo (frame) con el tiempo actual
        // para que en la siguiente vuelta se mida el nuevo deltaTime correctamente
        lastFrameTime = currentFrameTime;

        auto elapsed = duration_cast<seconds>(currentFrameTime - startTime).count();

        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, survivalSubmarine);
        }

        for (int i = 0; i < survival_num_fishes; i++)
        {
            MoveFish(survivalFishes[i]);
            CollisionFish(survivalFishes[i], survivalSubmarine);
        }
        Sleep(5);

    } while (survivalSubmarine.lifes > 0);
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(endTime - startTime).count();
    SaveGameTimeToFile(duration, "database/db_deepdive.txt");
}

#endif