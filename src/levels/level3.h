#ifndef LEVEL3_H
#define LEVEL3_H

#include "../headers/fish.h"
#include "../headers/submarine.h"
#include "../headers/game_limits.h"
#include <chrono>

static Submarine level3Submarine;
static Submarine allySubmarine;
static Fish level3Fishes[4];
static int level3NumFishes;
static int allyFrame = 0;
static const std::string framesAllyFish[] = {
    ">{{{°>",
    ">{{{o>",
    ">{{{0>"};

static void InitGameMessagelevel3()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string titulo[7] = {
        "██╗      ███████╗ ██╗   ██╗ ███████╗ ██╗               ██████╗ ",
        "██║      ██╔════╝ ██║   ██║ ██╔════╝ ██║               ╚════██╗",
        "██║      █████╗   ██║   ██║ █████╗   ██║                █████╔╝",
        "██║      ██╔══╝   ╚██╗ ██╔╝ ██╔══╝   ██║                ╚═══██╗",
        "███████╗ ███████╗  ╚████╔╝  ███████╗ ███████╗          ██████╔╝",
        "╚══════╝ ╚══════╝   ╚═══╝   ╚══════╝ ╚══════╝          ╚═════╝ ",
        "                                                                    "};

    for (int i = 0; i < 7; ++i)
    {
        gotoxy(30, 8 + i); // Ajusta según la posición deseada
        std::cout << titulo[i];
    }

    gotoxy(43, 15);
    std::cout << "[ Press ENTER twice to continue ]";

    gotoxy(30, 17);
    std::cout << ">> Principal Objective: Escort and protect the ally fish! <<";

    std::cin.ignore();
    std::cin.get();
    system("cls");
}

static void VictoryLevel3()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string congrats[] = {
    " ██████╗ ██████╗ ███╗   ██╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗██╗      █████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗",
    "██╔════╝██╔═══██╗████╗  ██║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██║     ██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝",
    "██║     ██║   ██║██╔██╗ ██║██║  ███╗██████╔╝███████║   ██║   ██║   ██║██║     ███████║   ██║   ██║██║   ██║██╔██╗ ██║███████╗",
    "██║     ██║   ██║██║╚██╗██║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██║     ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║",
    "╚██████╗╚██████╔╝██║ ╚████║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║███████║",
    " ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝",
    };

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(10, 6 + i);
        std::cout << congrats[i];
    }

    gotoxy(28, 14);
    std::cout << "You successfully protected and escort the ally fish!";

    gotoxy(25, 16);
    std::cout << "[ Press ENTER to return to menu ]";

    std::cin.ignore();
    std::cin.get();
    system("cls");
}

static void GameOverlevel3()
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

    gotoxy(45, 17);
    std::cout << "[Press ENTER twice to continue]" << "\n\n";
}

void PaintAllyFish(Submarine &ally)
{
    gotoxy(ally.x, ally.y);
    std::cout << framesAllyFish[allyFrame];
    allyFrame = (allyFrame + 1) % 3;
}

void DeleteAllyFish(Submarine &ally)
{
    gotoxy(ally.x, ally.y);
    std::cout << "       ";
    gotoxy(ally.x, ally.y + 1); 
    std::cout << "       ";
}

static void InitGamelevel3()
{
    InitGameMessagelevel3();
    system("cls");
    gotoxy(0, 1);
    std::cout << "Principal Objective: Escort the ally fish!";

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

static void GameLooplevel3()
{
    GameLimits();
    using namespace std::chrono;
    auto startTime = steady_clock::now();

    do
    {
        DeleteAllyFish(allySubmarine); // Borrar pez antes de movimiento del Subm
        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, level3Submarine);
        }

        // Mover aliado detrás del jugador
        allySubmarine.x = level3Submarine.x - 8;
        allySubmarine.y = level3Submarine.y;
        //First we paint the Submarine 
        PaintSubmarine(level3Submarine);

        if(allySubmarine.x + 7 < level3Submarine.x){// Validation to avoid conflicts
        //After paint Submarine
        PaintAllyFish(allySubmarine);
        }

        for (int i = 0; i < level3NumFishes; i++)
        {
            MoveFish(level3Fishes[i]);
            CollisionFish(level3Fishes[i], level3Submarine);

            // Si el aliado es tocado, pierde
            if (level3Fishes[i].x == allySubmarine.x &&
                (level3Fishes[i].y == allySubmarine.y || level3Fishes[i].y == allySubmarine.y + 1))
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {40, 15});
                std::cout << "El pez aliado fue devorado!!!";
                Sleep(3000);

                return;
            }
        }

        // Verificar si pasaron 3 minutos
        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime).count();
        if (elapsed >= 180)
        {
            VictoryLevel3();
            return;
        }

        // Mostrar temporizador en la línea 1
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {55, 1});
        int remaining = 180 - static_cast<int>(elapsed);
        int minutes = remaining / 60;
        int seconds = remaining % 60;
        std::cout << "Tiempo restante: " << minutes << "m " << (seconds < 10 ? "0" : "") << seconds << "s     ";

        Sleep(13);

    } while (level3Submarine.lifes > 0);
    GameOverlevel3();
}

#endif
