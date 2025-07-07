#ifndef SURVIVAL_MODE_H_INCLUDED
#define SURVIVAL_MODE_H_INCLUDED

#include "../headers/rockets.h"
#include "../headers/game_data.h"
#include "../headers/game_limits.h"
#include "../headers/game_data.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.
#include <limits>
#include <string>

static Submarine survivalSubmarine;
static Rocket survivalRockets[5];
static int survivalNumrocketes;
static int chosenSubmarineStyle = 1;
static std::string captain;

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
    gotoxy(46, 15);
    std::cout << "[Press ENTER to continue]\n\n";

    while (true)
    {
        int key = _getch();
        if (key == 13)
            break; // 13 = Enter
        gotoxy(46, 15);
        std::cout << "[Only press ENTER to continue]\n\n";
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
        gotoxy(10, 6 + i);
        std::cout << texto[i] << "\n\n";
    }
    gotoxy(35, 17);
    std::cout << ">>Dodge obstacles and survive as long as possible<<\n";

    WaitEnter();
    system("chcp 437 > nul");
}

static void GameOverSurvivalMode(int duration)
{
    while (_kbhit())
        _getch();

    system("cls");
    int minutes = duration / 60;
    int seconds = duration % 60;
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
    gotoxy(45, 17);
    std::cout << ">>Survived time: " << minutes << " min" << " " << seconds << " sec<<" << "\n";

    WaitEnter();
}

void Timer(int time)
{
    gotoxy(5, 1);
    std::cout << "Time: " << time << " sec.";
}

static void SubmarineType(int style)
{
    system("chcp 437 > nul");

    switch (style)
    {
    case 1:
        std::cout << "\033[1;34m       " << (char)95 << (char)218 << "\033[0m" << "\n";

        std::cout << "\033[1;34m " << (char)126 << (char)42 << (char)95 << (char)95 << (char)95 << (char)47 << (char)111 << (char)111 << (char)92 << (char)95 << "\033[0m" << "\n";

        std::cout << "\033[1;34m  " << (char)40 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)41 << "\033[0m" << "\n";
        break;
    case 2:
        std::cout << "\033[1;36m       " << (char)95 << (char)201 << "\033[0m" << "\n";

        std::cout << "\033[1;36m " << (char)177 << (char)62 << (char)95 << (char)95 << (char)219 << (char)47 << (char)240 << (char)240 << (char)92 << (char)92 << "\033[0m" << "\n";

        std::cout << "\033[1;36m  " << (char)40 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)41 << "\033[0m" << "\n";

        break;
    case 3:
        std::cout << "\033[1;35m       " << (char)95 << (char)254 << "\033[0m" << "\n";

        std::cout << "\033[1;35m " << (char)178 << (char)35 << (char)95 << (char)95 << (char)95 << (char)47 << (char)216 << (char)216 << (char)92 << (char)45 << "\033[0m" << "\n";

        std::cout << "\033[1;35m  " << (char)40 << (char)61 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)61 << (char)41 << "\033[0m" << "\n";
        break;
    case 4:
        std::cout << "\033[1;34m       " << (char)95 << (char)209 << "\033[0m" << "\n";

        std::cout << "\033[1;34m " << (char)177 << (char)62 << (char)95 << (char)95 << (char)45 << (char)47 << (char)248 << (char)248 << (char)92 << (char)45 << "\033[0m" << "\n";

        std::cout << "\033[1;34m  " << (char)40 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)41 << "\033[0m" << "\n";
        break;
    default:
        std::cout << "Error, invalid option\n";
        break;
    }
    system("chcp 65001 > nul");
}

static void Player()
{
    int count = 1, option;
    std::string line, selectedCaptain;

    system("cls");
    system("chcp 65001 > nul");

    std::ifstream file("database/characters.txt");
    if (!file.is_open())
    {
        std::cout << "⚠️ Error: No se pudo abrir el archivo de personajes.\n";
        WaitEnter();
        return;
    }

    // Mostrar personajes
    while (getline(file, line))
    {
        int style = ((count - 1) % 6) + 1;

        std::cout << "\033[1;37m[🔔] Canal táctico -- ID " << count << "\033[0m\n";
        std::cout << "\033[1;37m--------------------------------------------\033[0m\n";
        std::cout << "\033[1;37m👤 Registro de Capitán: " << line << "\033[0m\n";
        std::cout << "\033[1;37m🛠️ Submarino tipo-" << style << " asignado:\033[0m\n";

        SubmarineType(style);

        std::cout << "\033[1;37m--------------------------------------------\033[0m\n\n";
        count++;
    }
    file.close();

    // Pedir opción
    do
    {
        std::cout << "🔱 Elige tu personaje (1 a " << count - 1 << "): ";
        std::cin >> option;

        if (std::cin.fail() || option < 1 || option >= count)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "❌ Selección inválida. Intenta nuevamente.\n";
        }
        else
        {
            break;
        }
    } while (true);

    // Volver a leer el archivo para obtener el capitán seleccionado
    file.open("database/characters.txt");
    if (!file.is_open())
    {
        std::cout << "⚠️ Error: No se pudo volver a abrir el archivo.\n";
        WaitEnter();
        return;
    }

    count = 1;
    while (getline(file, line))
    {
        if (count == option)
        {
            selectedCaptain = line;
            break;
        }
        count++;
    }
    file.close();

    // Confirmar selección
    if (selectedCaptain.empty())
    {
        std::cout << "❌ No se encontró el capitán seleccionado.\n";
    }
    else
    {
        std::cout << "✅ Capitán asignado: " << selectedCaptain << "\n";
        captain = selectedCaptain;
        chosenSubmarineStyle = ((option - 1) % 4) + 1;
    }

    system("pause");
    system("chcp 437 > nul");
    system("cls");
}

static void InitGameSurvivalMode()
{
    InitGameMessage();
    Player();
    survivalSubmarine = {5, 15, 3, 1};
    PaintSubmarine(survivalSubmarine, chosenSubmarineStyle);
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

    SaveGameTimeToFile(duration, captain);

    GameOverSurvivalMode(duration);
}

#endif