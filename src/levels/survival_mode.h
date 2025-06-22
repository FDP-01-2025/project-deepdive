#ifndef SURVIVAL_MODE_H_INCLUDED
#define SURVIVAL_MODE_H_INCLUDED
#include "headers/fish.h"
#include "headers/game_time.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.
#include "headers/timer.h"

static Submarine survivalSubmarine;
static Fish survivalFishes[4];
static int survivalNumFishes;

static void InitGameSurvivalMode()
{
    survivalSubmarine = {5, 15, 3, 3};
    PaintSubmarine(survivalSubmarine);
    PaintHearts(survivalSubmarine);

    survivalFishes[0] = {80, 3};
    survivalFishes[1] = {90, 10};
    survivalFishes[2] = {100, 15};
    survivalFishes[3] = {110, 20};
    survivalNumFishes = 4;
}

static void GameLoopSurvivalMode()
{
    // Tiempo de inicio
    // Se guarda el tiempo actual al comenzar el juego (marca de inicio)
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    // Se guarda el tiempo de la "última actualización de fotograma" (frame)
    // Inicialmente, es el mismo que el de inicio
    std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();

    const int targetFrameTime = 16; // Objetivo: 60 FPS ≈ 16 ms por frame
    do
    {
        // Se toma el tiempo actual (inicio de este nuevo ciclo del bucle)
        std::chrono::high_resolution_clock::time_point currentFrameTime = std::chrono::high_resolution_clock::now();
        // Se calcula cuánto tiempo ha pasado desde el último ciclo (frame)
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - lastFrameTime).count();

        // Se actualiza el tiempo del último ciclo (frame) con el tiempo actual
        // para que en la siguiente vuelta se mida el nuevo deltaTime correctamente
        lastFrameTime = currentFrameTime;

        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentFrameTime - startTime).count();

        // Imprime el contador
        Timer(elapsed);

        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, survivalSubmarine);
        }

        for (int i = 0; i < survivalNumFishes; i++)
        {
            MoveFish(survivalFishes[i]);
            CollisionFish(survivalFishes[i], survivalSubmarine);
        }

        // CONTROL DE FPS:
        auto frameEndTime = std::chrono::high_resolution_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - currentFrameTime).count();

        if (frameDuration < targetFrameTime)
        {
            Sleep(targetFrameTime - frameDuration);
        }

    } while (survivalSubmarine.lifes > 0);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    SaveGameTimeToFile(duration, "database/db_deepdive.txt");
}

#endif