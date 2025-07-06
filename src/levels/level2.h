#ifndef LEVEL2_H
#define LEVEL2_H
#include "../headers/fish.h"
#include "../headers/pieces.h"
#include "../headers/game_limits.h"
#include <conio.h> //Permite utilizar la función getch(), para detectar las pulsaciones de cada tecla.
/*
OBJETIVO DEL NIVEL 2:
-REUNIR LAS PIEZAS PARA LLENAR LA BARRA DE OXYGENO Y PODER DESBLOQUEAR OTROS NIVELES

*/

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
        "                                                                    "
    };

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(30, 8 + i);  // Ajusta según la posición deseada
        std::cout << titulo[i];
    }

    for (int i = 0; i < 7; ++i)
    {
        gotoxy(30, 8 + i);  // Ajusta según la posición deseada
        std::cout << titulo[i];
    }

    gotoxy(43, 15);
    std::cout << "[ Press ENTER twice to continue ]";

    gotoxy(30, 17);
    std::cout << ">> OBJECTIVE: Collect the pieces to refill the oxygen bar! <<";

    std::cin.ignore();
    std::cin.get();
    system("cls");
}

inline void VictoryLevel2()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string congrats[] = {
    " ██████╗ ██████╗ ██╗   █╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗██╗     █████╗ ████████╗██╗ ██████╗ ██╗   █╗██████╗",
    "██╔════╝██╔═══██╗███╗  █║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██║    ██╔══██╗╚══██╔══╝██║██╔═══██╗███╗  █║██╔═══╝",
    "██║     ██║   ██║█╔██╗ █║██║  ███╗██████╔╝███████║   ██║   ██║   ██║██║    ███████║   ██║   ██║██║   ██║█╔██╗ █║██████╗",
    "██║     ██║   ██║█║╚██╗█║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██║    ██╔══██║   ██║   ██║██║   ██║█║╚██╗█║╚═══██║",
    "╚██████╗╚██████╔╝█║ ╚███║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝██████╗██║  ██║   ██║   ██║╚██████╔╝█║ ╚███║██████║",
    " ╚═════╝ ╚═════╝ ╚╝  ╚══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚╝  ╚══╝ ╚════╝",
    };

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(1, 8 + i);
        std::cout << congrats[i];
    }

    gotoxy(43, 15);
    std::cout << "You successfully filled the oxygen bar!";

    gotoxy(45, 17);
    std::cout << "[ Press ENTER to return to menu ]";

    std::cin.clear();
    std::cin.sync();
    std::cin.get();       // Espera la primera pulsación de ENTER
    std::cin.get();       // Espera la segunda pulsación de ENTER
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
    std::cout << "[Press ENTER to continue]" << "\n\n";
    std::cin.clear();
    std::cin.sync();
    std::cin.get();
    std::cin.get();
}


static Submarine level2Submarine;
static Fish level2Fishes[4];
static int level2Numfishes;
static pieces level2Pieces[1]; // Numero de Piezas
static
int level2NumPieces;
extern int sleepTime; //Tiempo inicial de espera

static void InitGamelevel2()
{   
    InitGameMessagelevel2();
    system("cls");
    setColor(11);
    gotoxy(5,1);
    std::cout << "Principal Objective: Refil the oxygen!";
    level2Submarine = {5, 15, 1, 3};
    PaintSubmarine(level2Submarine);
    PaintHearts(level2Submarine);
    PaintOxygen(level2Submarine);

    level2Fishes[0] = {80, 3};
    level2Fishes[1] = {90, 10};
    level2Fishes[2] = {100, 15};
    level2Fishes[3] = {110, 20};
    level2Numfishes = 4;

    level2Pieces[0] = {85, 5};
    level2NumPieces = 1;
}


static void GameLooplevel2()
{
    GameLimits();
    do
    {
        
        // para que en la siguiente vuelta se mida el nuevo deltaTime correctamente
        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, level2Submarine);
        }

        for (int i = 0; i < level2Numfishes; i++)
        {
            MoveFish(level2Fishes[i]);
            CollisionFish(level2Fishes[i], level2Submarine);
        }
        for (int i = 0; i < level2NumPieces; i++)
        {
            Movepieces(level2Pieces[i]);
            Collisionpieces(level2Pieces[i], level2Submarine);
        }
        Sleep(sleepTime);

    } while (level2Submarine.lifes > 0);
    GameOverlevel2();

}

#endif
