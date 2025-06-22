#ifndef SURVIVAL_MODE_H_INCLUDED
#define SURVIVAL_MODE_H_INCLUDED
#include "headers/rockets.h"
#include "headers/game_time.h"
#include "headers/timer.h"
#include "headers/game_limits.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.

static Submarine survivalSubmarine;
static Rocket survivalRockets[6];
static int survivalNumrocketes;

const int BASE_FPS = 60;
const int BASE_FRAME_TIME_MS = 1000 / BASE_FPS;

struct DifficultySettings
{
    int targetFrameTime;
    float rocketSpeed;
    int activeRockets;
};

static void InitGameSurvivalMode()
{
    survivalSubmarine = {5, 15, 3, 3};
    PaintSubmarine(survivalSubmarine);
    PaintHearts(survivalSubmarine);

    survivalRockets[0] = {80, 3};
    survivalRockets[1] = {90, 6};
    survivalRockets[2] = {100, 9};
    survivalRockets[3] = {110, 12};
    survivalRockets[4] = {115, 15};
    survivalRockets[5] = {120, 18};
    survivalNumrocketes = 6;
}

// Calcula la dificultad en base al tiempo
DifficultySettings UpdateDifficulty(int elapsedSeconds, int totalRockets)
{
    int speed = std::min(elapsedSeconds / 10, 20); // Sube la dificultad cada 10 segundos. Tope de velocidad 20;

    int targetFrameTime = BASE_FRAME_TIME_MS - std::min(speed, 8); // FPS máximo ajustable
    float rocketSpeed = 0.4f + speed * 0.05f;                      // Aumenta velocidad de los cohetes con el tiempo (0.4f -> velocidad inicial, 0.5f aumento de velocidad por nivel)
    int activeRockets = std::min(3 + speed, totalRockets);         // Activa más cohetes progresivamente

    return {targetFrameTime, rocketSpeed, activeRockets};
}

static void GameLoopSurvivalMode()
{
    GameLimits();

    // Se guarda el tiempo actual al comenzar el juego (marca de inicio)
    auto startTime = std::chrono::high_resolution_clock::now();

    // Se guarda el tiempo de la "última actualización de fotograma" (frame)
    // Inicialmente, es el mismo que el de inicio
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (survivalSubmarine.lifes > 0)
    {
        // Se obtiene el tiempo actual en este instante del bucle
        auto now = std::chrono::high_resolution_clock::now();

        // Se calcula el tiempo transcurrido desde el último frame, en milisegundos
        // Esto permite ajustar los movimientos y animaciones según el tiempo real entre frames
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();

        // Se actualiza lastFrameTime para la próxima iteración del bucle
        lastFrameTime = now;

        // Se calcula el tiempo total transcurrido desde que inició el juego (en segundos)
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

        // Se actualizan los parámetros de dificultad en función del tiempo transcurrido y la cantidad de cohetes activos
        auto settings = UpdateDifficulty(elapsed, survivalNumrocketes);
        
        // Imprime el contador
        Timer(elapsed);

        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, survivalSubmarine);
        }

        for (int i = 0; i < settings.activeRockets; i++)
        {
            MoveRocket(survivalRockets[i], settings.rocketSpeed);
            CollisionRocket(survivalRockets[i], survivalSubmarine);
        }

        // CONTROL DE FPS:
        auto frameEndTime = std::chrono::high_resolution_clock::now();
        auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - now).count();

        if (frameDuration < settings.targetFrameTime)
        {
            Sleep(settings.targetFrameTime - frameDuration);
        }
    }

    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    SaveGameTimeToFile(duration, "database/db_deepdive.txt");
}

#endif