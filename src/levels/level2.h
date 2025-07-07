#ifndef LEVEL2_H
#define LEVEL2_H

#include "../headers/fish.h"
#include "../headers/submarine.h"
#include "../headers/game_limits.h"
#include <chrono>

static Submarine level2Submarine;
static Submarine allySubmarine;
static Fish level2Fishes[4];
static int level2NumFishes;
static int allyFrame = 0;
static const std::string framesAllyFish[] = {
    ">{{{°>",
    ">{{{o>",
    ">{{{0>"};

static void InitGameMessagelevel2()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string titulo[7] = {
        "██╗      ███████╗ ██╗   ██╗ ███████╗ ██╗               ██████╗ ",
        "██║      ██╔════╝ ██║   ██║ ██╔════╝ ██║               ╚════██╗",
        "██║      █████╗   ██║   ██║ █████╗   ██║                █████╔╝",
        "██║      ██╔══╝   ╚██╗ ██╔╝ ██╔══╝   ██║               ██╔═══╝",
        "███████╗ ███████╗  ╚████╔╝  ███████╗ ███████╗          ██████╗",
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

inline void Victorylevel2()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string congrats[6] = {
        " ██████╗ ██████╗ ██╗   █╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗██╗    █████╗ ████████╗██╗ ██████╗ ██╗   █╗███████╗",
        "██╔════╝██╔═══██╗███╗  █║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██║   ██╔══██╗╚══██╔══╝██║██╔═══██╗███╗  █║██╔════╝",
        "██║     ██║   ██║█╔██╗ █║██║  ███╗██████╔╝███████║   ██║   ██║   ██║██║   ███████║   ██║   ██║██║   ██║█╔██╗ █║███████╗",
        "██║     ██║   ██║█║╚██╗█║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██║   ██╔══██║   ██║   ██║██║   ██║█║╚██╗█║╚════██║",
        "╚██████╗╚██████╔╝█║ ╚███║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝█████╗██║  ██║   ██║   ██║╚██████╔╝█║ ╚███║███████║",
        " ╚═════╝ ╚═════╝ ╚╝  ╚══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚╝  ╚══╝╚══════╝",
    };

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(1, 8 + i);
        std::cout << congrats[i];
    }

    gotoxy(35, 15);
    std::cout << "You successfully protected and escort the ally fish!✅";

    gotoxy(45, 17);
    std::cout << "[ Press ENTER to return to menu ]";

    std::cin.clear();
    std::cin.sync();
    std::cin.get();
    std::cin.get();
    system("cls");
}

static void GameOverlevel2()
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
    std::cin.ignore();
    std::cin.get();
    system("cls");
}
static void GameOverAllyfish()
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
    std::cout << "🐠[The allied fish was deboured]🐠" << "\n\n";
    std::cin.ignore();
    std::cin.get();
    system("cls");
}

void PaintAllyFish(Submarine &ally)
{

    if (ally.x >= 1 && ally.x <= 110 && ally.y >= 2 && ally.y <= 22)
    {
        gotoxy(ally.x, ally.y);
        std::cout << framesAllyFish[allyFrame];
        allyFrame = (allyFrame + 1) % 3;
    }
}

void DeleteAllyFish(Submarine &ally)
{
    if (ally.x > 1 && ally.x < 110 && ally.y >= 2 && ally.y <= 22)
    {
        gotoxy(ally.x, ally.y);
        std::cout << "       ";
    }
}

static void InitGamelevel2()
{
    InitGameMessagelevel2();
    system("cls");
    setColor(11);
    gotoxy(5, 1);
    std::cout << "Principal Objective: Escort the ally fish❗";

    level2Submarine = {5, 15, 3, 3, 10}; // Submarino controlado por usuario
    allySubmarine = {5, 18, 0, 1, 0};    // Aliado a proteger

    PaintSubmarine(level2Submarine,1);
    PaintAllyFish(allySubmarine);
    PaintHearts(level2Submarine);

    level2Fishes[0] = {80, 3};
    level2Fishes[1] = {90, 10};
    level2Fishes[2] = {100, 15};
    level2Fishes[3] = {110, 20};
    level2NumFishes = 4;
}

static void GameLooplevel2()
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
            MoveSubmarine(tecla, level2Submarine);
        }

        // Mover aliado detrás del jugador
        allySubmarine.x = std::max(2, std::min(level2Submarine.x - 8, 103)); // 103 = 110 - 7 (ancho del pez)
        allySubmarine.y = std::min(level2Submarine.y, 22);

        // First we paint the Submarine
        PaintSubmarine(level2Submarine,1);
        PaintAllyFish(allySubmarine);

        for (int i = 0; i < level2NumFishes; i++)
        {
            MoveFish(level2Fishes[i]);
            CollisionFish(level2Fishes[i], level2Submarine);

            // Si el aliado es tocado, pierde
            if (level2Fishes[i].x == allySubmarine.x &&
                (level2Fishes[i].y == allySubmarine.y || level2Fishes[i].y == allySubmarine.y + 1))
            {
                GameOverAllyfish();
                Sleep(3000);

                return;
            }
        }

        // Verificar si pasaron 3 minutos
        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime).count();
        if (elapsed >= 180)
        {
            Victorylevel2();
            return;
        }

        // Mostrar temporizador en la línea 1
        gotoxy(50, 1);
        int remaining = 180 - static_cast<int>(elapsed);
        int minutes = remaining / 60;
        int seconds = remaining % 60;
        std::cout << "Tiempo restante: " << minutes << "m " << (seconds < 10 ? "0" : "") << seconds << "s     ";

        Sleep(13);

    } while (level2Submarine.lifes > 0);
    GameOverlevel2();
}

#endif
