#ifndef SURVIVAL_MODE_H_INCLUDED
#define SURVIVAL_MODE_H_INCLUDED

#include "../headers/rockets.h"
#include "../headers/game_data.h"
#include "../headers/game_limits.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.

static Submarine survivalSubmarine;
static Rocket survivalRockets[5];
static int survivalNumrocketes;

const int BASE_FPS = 60;
const int BASE_FRAME_TIME_MS = 1000 / BASE_FPS;

struct DifficultySettings
{
    int targetFrameTime;
    float rocketSpeed;
    int activeRockets;
};

// Calcula la dificultad en base al tiempo
DifficultySettings UpdateDifficulty(int elapsedSeconds, int totalRockets)
{
    int speed = std::min(elapsedSeconds / 10, 20); // Sube la dificultad cada 10 segundos. Tope de velocidad 20;

    int targetFrameTime = BASE_FRAME_TIME_MS - std::min(speed, 8); // FPS máximo ajustable
    float rocketSpeed = 0.4f + speed * 0.05f;                      // Aumenta velocidad de los cohetes con el tiempo (0.4f -> velocidad inicial, 0.5f aumento de velocidad por nivel)
    int activeRockets = std::min(3 + speed, totalRockets);         // Activa más cohetes progresivamente

    return {targetFrameTime, rocketSpeed, activeRockets};
}

static void WaitEnter()
{
    std::string entry;
    gotoxy(46, 15);
    std::cout << "[Press ENTER to continue]" << "\n\n";
    std::getline(std::cin, entry);

    while (!entry.empty())
    {
        gotoxy(46, 15);
        std::cout << "                         " << "\n";
        gotoxy(46, 15);
        std::cout << "[Only press ENTER to continue]" << "\n\n";
        std::getline(std::cin, entry);
    }
}

static void InitGameMessage()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string texto[6] = {
        "███████╗██╗   ██╗██████╗ ██╗   ██╗██╗██╗   ██╗ █████╗ ██╗         ███╗   ███╗ ██████╗ ██████╗ ███████╗",
        "██╔════╝██║   ██║██╔══██╗██║   ██║██║██║   ██║██╔══██╗██║         ████╗ ████║██╔═══██╗██╔══██╗██╔════╝",
        "███████╗██║   ██║██████╔╝██║   ██║██║██║   ██║███████║██║         ██╔████╔██║██║   ██║██║  ██║█████╗  ",
        "╚════██║██║   ██║██╔══██╗╚██╗ ██╔╝██║╚██╗ ██╔╝██╔══██║██║         ██║╚██╔╝██║██║   ██║██║  ██║██╔══╝  ",
        "███████║╚██████╔╝██║  ██║ ╚████╔╝ ██║ ╚████╔╝ ██║  ██║███████╗    ██║ ╚═╝ ██║╚██████╔╝██████╔╝███████╗",
        "╚══════╝ ╚═════╝ ╚═╝  ╚═╝  ╚═══╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝    ╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝"};

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(10, 8 + i);
        std::cout << texto[i] << "\n\n";
    }
    system("chcp 437 > nul");

    gotoxy(35, 17);
    std::cout << ">>Dodge obstacles and survive ad long as possible<<" << "\n";

    WaitEnter();
    system("cls");
}

static void GameOverSurvivalMode()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string texto[6] = {
        " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗",
        "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
        "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
        "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
        "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
        " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"};

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(25, 6 + i);
        std::cout << texto[i] << "\n\n";
    }
    system("chcp 437 > nul");
}


void Timer(int time)
{
    gotoxy(5, 1);
    std::cout << "Time: " << time <<" sec.";
}

static void GameTime(int duration)
{
    int minutes = duration / 60;
    int seconds = duration % 60;
    gotoxy(45, 17);
    std::cout << ">>Survived time: " << minutes << " min" << " " << seconds << " sec<<" << "\n";
    WaitEnter();
}

static void InitGameSurvivalMode()
{
    InitGameMessage();
    survivalSubmarine = {5, 15, 3, 1};
    PaintSubmarine(survivalSubmarine);
    PaintHearts(survivalSubmarine);

    survivalRockets[0] = {102, 3};
    survivalRockets[1] = {104, 20};
    survivalRockets[2] = {106, 15};
    survivalRockets[3] = {108, 9};
    survivalRockets[4] = {110, 6};
    survivalNumrocketes = 5;
}

static void GameLoopSurvivalMode()
{
    GameLimits();

    // Se guarda el tiempo actual al comenzar el juego (marca de inicio)
    auto startTime = std::chrono::high_resolution_clock::now();
    // Se guarda el tiempo de la "última actualización de fotograma" (frame). Inicialmente, es el mismo que el de inicio
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    auto now = startTime;
    while (survivalSubmarine.lifes > 0)
    {
        // Se obtiene el tiempo actual en este instante del bucle
        now = std::chrono::high_resolution_clock::now();

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

        if (survivalSubmarine.lifes < 0)
        {
            auto now = std::chrono::high_resolution_clock::now();
        }
    }

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

    SaveGameTimeToFile(duration);

    GameOverSurvivalMode();
    GameTime(duration);
}

#endif