#ifndef SUBMARINE_H_INCLUDED
#define SUBMARINE_H_INCLUDED

#include <iostream>
#include <windows.h>
#include "position.h"
// The keys A, W, S, D are defined in uppercase and lowercase.
#define UP 87
#define DOWN 83
#define LEFT 65
#define RIGHT 68

#define UPlc 119
#define DOWNlc 115
#define LEFTlc 97
#define RIGHTlc 100

typedef struct
{
    int x, y, heart, lifes, oxygen, Time;
} Submarine;

static int optionSubmarine = 1;

/* Paint the submarine with ASCII code characters */
// This function paints the submarine based on the selected option.
// The submarine is painted in different colors and styles depending on the option chosen.
inline void PaintSubmarine(Submarine &submarine, int option)
{
    // Clear the previous submarine
    optionSubmarine = option;
    switch (optionSubmarine)
    {   
    case 1:   // Paint the submarine in blue
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;34m       " << (char)95 << (char)218 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;34m " << (char)126 << (char)42 << (char)95 << (char)95 << (char)95 << (char)47 << (char)111 << (char)111 << (char)92 << (char)95 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;34m  " << (char)40 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)41 << "\033[0m";
        break;
    case 2:  // Paint the submarine in cyan
        // The submarine is painted in cyan color using ANSI escape codes.
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;36m       " << (char)95 << (char)201 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;36m " << (char)177 << (char)62 << (char)95 << (char)95 << (char)219 << (char)47 << (char)240 << (char)240 << (char)92 << (char)92 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;36m  " << (char)40 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)41 << "\033[0m";

        break;
    case 3:  // Paint the submarine in magenta
        // The submarine is painted in magenta color using ANSI escape codes.
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;35m       " << (char)95 << (char)254 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;35m " << (char)178 << (char)35 << (char)95 << (char)95 << (char)95 << (char)47 << (char)216 << (char)216 << (char)92 << (char)45 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;35m  " << (char)40 << (char)61 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)61 << (char)41 << "\033[0m";

        break;
    case 4:  // Paint the submarine in red
        // The submarine is painted in red color using ANSI escape codes.
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;34m       " << (char)95 << (char)209 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;34m " << (char)177 << (char)62 << (char)95 << (char)95 << (char)45 << (char)47 << (char)248 << (char)248 << (char)92 << (char)45 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;34m  " << (char)40 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)41 << "\033[0m";
        break;
    default:
        std::cout << "Error, invalid option\n";
        break;
    }
}

/* Delete the submarine in each movement*/
void DeleteSubmarine(Submarine &submarine)
{
    gotoxy(submarine.x, submarine.y);
    std::cout << "         ";
    gotoxy(submarine.x, submarine.y + 1);
    std::cout << "           ";
    gotoxy(submarine.x, submarine.y + 2);
    std::cout << "            ";
}

/* Paint the life and hearts of the submarine */
void PaintHearts(Submarine &submarine)
{

    gotoxy(96, 1);
    std::cout << "Lifes: " << submarine.lifes;
    gotoxy(107, 1);
    std::cout << "Hearts: ";
    gotoxy(115, 1);
    std::cout << "   ";
    // Activate UTF-8
    system("chcp 65001 > nul");
    for (int i = 0; i < submarine.heart; i++)
    {
        // ANSI is used to paint the hearts in another color
        gotoxy(115 + i, 1);
        std::cout << "\033[1;31m♥\033[0m";
    }
    // Restore the encoding
    system("chcp 437 > nul");
}

void PaintOxygen(Submarine &submarine)
{
    // Oxygen bar
    gotoxy(50, 1);
    std::cout << "Oxygen:";

    for (int i = 0; i < submarine.oxygen; i++)
    {   
        setColor(9);
        std::cout << (char)178;
    }
}

/* If the submarine's hearts reach 0, an animated explosion is drawn. */
void DestroySubmarine(Submarine &submarine)
{
    if (submarine.heart == 0)
    {
        DeleteSubmarine(submarine);
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;33m * * * * \033[0m";
        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;33m********\033[0m";
        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;33m * * * * \033[0m";
        Sleep(180);
        DeleteSubmarine(submarine);
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;33m*    *\033[0m";
        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;33m * * * * \033[0m";
        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;33m*    *\033[0m";
        Sleep(180);
        DeleteSubmarine(submarine);
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;33m * * * * \033[0m";
        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;33m********\033[0m";
        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;33m * * * * \033[0m";
        Sleep(180);
        DeleteSubmarine(submarine);
        submarine.lifes--;
        PaintHearts(submarine);
        submarine.heart = 3;
        PaintSubmarine(submarine, optionSubmarine);
    }
}
//Displays a blinking animation when the submarine gets hit (but is not destroyed)
void CollisionSubmarine(Submarine &submarine)
{
    for (int i = 0; i < 3; i++)
    {
        Sleep(80);
        DeleteSubmarine(submarine);
        gotoxy(submarine.x, submarine.y);
        std::cout << "        ";
        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "      ";
        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "      ";
        Sleep(80);
        PaintSubmarine(submarine, optionSubmarine);
    }
}

/* Submarine movement based on the keys pressed */
void MoveSubmarine(char key, Submarine &submarine)
{
    DeleteSubmarine(submarine);

    if ((key == LEFT || key == LEFTlc) && submarine.x > 3)
        submarine.x--;
    if ((key == RIGHT || key == RIGHTlc) && submarine.x < 106)
        submarine.x++;
    if ((key == UP || key == UPlc) && submarine.y > 3)
        submarine.y--;
    if ((key == DOWN || key == DOWNlc) && submarine.y < 25)
        submarine.y++;

    PaintSubmarine(submarine, optionSubmarine);
}


  // Submarine movement with ally fish
 // The ally fish follows the submarine's position, moving behind it.
void MoveWithAlly(char key, Submarine &submarine)
{
    // Delete the ally fish before moving the submarine
    // DeleteAllyFish(allySubmarine);
    DeleteSubmarine(submarine);

    if ((key == LEFT || key == LEFTlc) && submarine.x > 7)
        submarine.x--;
    if ((key == RIGHT || key == RIGHTlc) && submarine.x < 104)
        submarine.x++;
    if ((key == UP || key == UPlc) && submarine.y > 5)
        submarine.y--;
    if ((key == DOWN || key == DOWNlc) && submarine.y < 25)
        submarine.y++;

    PaintSubmarine(submarine, optionSubmarine);
}

#endif
