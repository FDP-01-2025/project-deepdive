#ifndef LEVEL1_H
#define LEVEL1_H
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
        "██╗      ███████╗ ██╗   ██╗ ███████╗ ██╗                ██╗",
        "██║      ██╔════╝ ██║   ██║ ██╔════╝ ██║               ███║",
        "██║      █████╗   ██║   ██║ █████╗   ██║               ╚██║",
        "██║      ██╔══╝   ╚██╗ ██╔╝ ██╔══╝   ██║                ██║",
        "███████╗ ███████╗  ╚████╔╝  ███████╗ ███████╗           ██║",
        "╚══════╝ ╚══════╝   ╚═══╝   ╚══════╝ ╚══════╝           ╚═╝ ",
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

inline void Victorylevel1()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string congrats[6] = {
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

static void GameOverlevel1()
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


static Submarine level1Submarine;
static Fish level1Fishes[4];
static int level1Numfishes;
static pieces level1Pieces[1]; // Numero de Piezas
static
int level1NumPieces;
extern int sleepTime; //Tiempo inicial de espera

static void InitGamelevel1()
{   
    InitGameMessagelevel1();
    system("cls");
    setColor(11);
    gotoxy(5,1);
    std::cout << "Principal Objective: Refil the oxygen!";
    level1Submarine = {5, 15, 1, 3};
    PaintSubmarine(level1Submarine, chosenSubmarineStylelevel1);
    PaintHearts(level1Submarine);
    PaintOxygen(level1Submarine);

    level1Fishes[0] = {80, 3};
    level1Fishes[1] = {90, 10};
    level1Fishes[2] = {100, 15};
    level1Fishes[3] = {110, 20};
    level1Numfishes = 4;

    level1Pieces[0] = {85, 5};
    level1NumPieces = 1;
}


static void GameLooplevel1()
{
    GameLimits();
    do
    {
        
        // para que en la siguiente vuelta se mida el nuevo deltaTime correctamente
        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, level1Submarine);
        }

        for (int i = 0; i < level1Numfishes; i++)
        {
            MoveFish(level1Fishes[i]);
            CollisionFish(level1Fishes[i], level1Submarine);
        }
        for (int i = 0; i < level1NumPieces; i++)
        {
            Movepieces(level1Pieces[i]);
            Collisionpieces(level1Pieces[i], level1Submarine);
        }
        Sleep(sleepTime);

    } while (level1Submarine.lifes > 0);
    GameOverlevel1();

}

#endif
