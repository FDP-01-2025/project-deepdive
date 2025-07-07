#ifndef LEVEL1_H
#define LEVEL1_H
#include "../headers/fish.h"
#include "../headers/pieces.h"
#include "../headers/game_limits.h"
#include <conio.h> // It allows the use of the getch() function to detect the keystrokes of each key.
/*
OBJECTIVE OF LEVEL 2:
-COLLECT THE PIECES TO FILL THE OXYGEN BAR AND UNLOCK OTHER LEVELS

*/
static Submarine level1Submarine;
static Fish level1Fishes[4];
static int level1Numfishes;
static pieces level1Pieces[1]; // Numero de Piezas
static int chosenSubmarineStylelevel1=1;
static int level1NumPieces;
extern int sleepTime; //Tiempo inicial de espera

static void WaitEnterlevel1()
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
static void InitGameMessagelevel1()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string title[7] = {
        "██╗      ███████╗ ██╗   ██╗ ███████╗ ██╗                ██╗",
        "██║      ██╔════╝ ██║   ██║ ██╔════╝ ██║               ███║",
        "██║      █████╗   ██║   ██║ █████╗   ██║               ╚██║",
        "██║      ██╔══╝   ╚██╗ ██╔╝ ██╔══╝   ██║                ██║",
        "███████╗ ███████╗  ╚████╔╝  ███████╗ ███████╗           ██║",
        "╚══════╝ ╚══════╝   ╚═══╝   ╚══════╝ ╚══════╝           ╚═╝ ",
        "                                                                    "
    };

    for (int i = 0; i < 7; ++i)
    {
        gotoxy(30, 8 + i);  // Adjust according to the desired position
        std::cout << title[i];
    }

    gotoxy(43, 15);
    std::cout << "[ Press ENTER twice to continue ]";

    gotoxy(30, 17);
    std::cout << ">> OBJECTIVE: Collect the pieces to refill the oxygen bar❗ <<";

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
    std::cout << "You successfully filled the oxygen bar!✅";

    gotoxy(45, 17);
    std::cout << "[ Press ENTER to return to menu ]";

    std::cin.ignore();
    std::cin.get();
    system("cls");
}

static void GameOverlevel1()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string text[6] = {
        " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗",
        "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
        "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
        "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
        "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
        " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"};

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(25, 6 + i);
        std::cout << text[i] << "\n\n";
    }
    system("chcp 437 > nul");
    WaitEnterlevel1();
    system("cls");
}

static void InitGamelevel1()
{   
    InitGameMessagelevel1();
    system("cls");
    setColor(15);
    gotoxy(5,1);
    std::cout << "Principal Objective: Refil the oxygen❗";
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

        // to ensure that the new deltaTime is measured correctly in the next round
        if (kbhit())
        {
            char key = getch();
            MoveSubmarine(key, level1Submarine);
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
