#ifndef SURVIVAL_MODE_H_INCLUDED
#define SURVIVAL_MODE_H_INCLUDED
#include "headers/rockets.h"
#include "headers/game_time.h"
#include "headers/timer.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.

static Submarine survivalSubmarine;
static Rocket survivalRockets[4];
static int survivalNumrocketes;

static void InitGameSurvivalMode()
{
    survivalSubmarine = {5, 15, 3, 3};
    PaintSubmarine(survivalSubmarine);
    PaintHearts(survivalSubmarine);

    survivalRockets[0] = {80, 3};
    survivalRockets[1] = {90, 10};
    survivalRockets[2] = {100, 15};
    survivalRockets[3] = {110, 20};
    survivalNumrocketes = 4;
}

static void GameLoopSurvivalMode()
{
    int targetFrameTime = 16; // Inicializa en 60 FPS ≈ 16 ms por frame
    int speed = 0;
    // Tiempo de inicio
    // Se guarda el tiempo actual al comenzar el juego (marca de inicio)
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    // Se guarda el tiempo de la "última actualización de fotograma" (frame)
    // Inicialmente, es el mismo que el de inicio
    std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now();

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

        speed = elapsed / 10;

        switch (speed)
        {
        case 1:
            targetFrameTime = 11;
            break;
        case 2:
            targetFrameTime = 9;
            break;
        case 3:
            targetFrameTime = 6;
            break;
        case 4:
            targetFrameTime = 4;
            break;
        case 5:
            targetFrameTime = 2;
            break;
        default:
            break;
        }

        // Imprime el contador
        Timer(elapsed);

        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, survivalSubmarine);
        }

        for (int i = 0; i < survivalNumrocketes; i++)
        {
            MoveRocket(survivalRockets[i]);
            CollisionRocket(survivalRockets[i], survivalSubmarine);
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