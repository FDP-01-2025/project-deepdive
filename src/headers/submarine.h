#ifndef SUBMARINE_H_INCLUDED
#define SUBMARINE_H_INCLUDED

#include <iostream>
#include <windows.h>
#include "position.h"
// Se definen las teclas A, W, S, D en mayúsculas y minúsculas
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

/* Pinta al submarino con caracteres del código ASCII */

inline void PaintSubmarine(Submarine &submarine, int option)
{

    optionSubmarine = option;
    switch (optionSubmarine)
    {
    case 1:
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;34m       " << (char)95 << (char)218 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;34m " << (char)126 << (char)42 << (char)95 << (char)95 << (char)95 << (char)47 << (char)111 << (char)111 << (char)92 << (char)95 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;34m  " << (char)40 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)41 << "\033[0m";
        break;
    case 2:
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;36m       " << (char)95 << (char)201 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;36m " << (char)177 << (char)62 << (char)95 << (char)95 << (char)219 << (char)47 << (char)240 << (char)240 << (char)92 << (char)92 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;36m  " << (char)40 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)41 << "\033[0m";

        break;
    case 3:
        gotoxy(submarine.x, submarine.y);
        std::cout << "\033[1;35m       " << (char)95 << (char)254 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 1);
        std::cout << "\033[1;35m " << (char)178 << (char)35 << (char)95 << (char)95 << (char)95 << (char)47 << (char)216 << (char)216 << (char)92 << (char)45 << "\033[0m";

        gotoxy(submarine.x, submarine.y + 2);
        std::cout << "\033[1;35m  " << (char)40 << (char)61 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)61 << (char)41 << "\033[0m";

        break;
    case 4:
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

/* Borra al submarino en cada desplazamiento */
void DeleteSubmarine(Submarine &submarine)
{
    gotoxy(submarine.x, submarine.y);
    std::cout << "         ";
    gotoxy(submarine.x, submarine.y + 1);
    std::cout << "           ";
    gotoxy(submarine.x, submarine.y + 2);
    std::cout << "            ";
}

/* Pinta la vida y los corazones del submarino */
void PaintHearts(Submarine &submarine)
{

    gotoxy(96, 1);
    std::cout << "Lifes: " << submarine.lifes;
    gotoxy(107, 1);
    std::cout << "Hearts: ";
    gotoxy(115, 1);
    std::cout << "   ";
    // Activa el UTF-8
    system("chcp 65001 > nul");
    for (int i = 0; i < submarine.heart; i++)
    {
        // Se usa ANSI para pintar de otro color los corazones
        gotoxy(115 + i, 1);
        std::cout << "\033[1;31m♥\033[0m";
    }
    // Restaura la codificación
    system("chcp 437 > nul");
}

void PaintOxygen(Submarine &submarine)
{
    // Barra de Oxigeno
    gotoxy(50, 1);
    std::cout << "Oxygen:";

    for (int i = 0; i < submarine.oxygen; i++)
    {   
        setColor(9);
        std::cout << (char)178;
    }
}

/* Si los corazones del submarino llegan a 0, se pinta una explosión animada */
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

/* Movimiento del submarino en base a las teclas presionadas */
void MoveSubmarine(char tecla, Submarine &submarine)
{
    DeleteSubmarine(submarine);

    if ((tecla == LEFT || tecla == LEFTlc) && submarine.x > 3)
        submarine.x--;
    if ((tecla == RIGHT || tecla == RIGHTlc) && submarine.x < 106)
        submarine.x++;
    if ((tecla == UP || tecla == UPlc) && submarine.y > 3)
        submarine.y--;
    if ((tecla == DOWN || tecla == DOWNlc) && submarine.y < 25)
        submarine.y++;

    PaintSubmarine(submarine, optionSubmarine);
}

void MoveWithAlly(char tecla, Submarine &submarine)
{
    DeleteSubmarine(submarine);

    if ((tecla == LEFT || tecla == LEFTlc) && submarine.x > 7)
        submarine.x--;
    if ((tecla == RIGHT || tecla == RIGHTlc) && submarine.x < 104)
        submarine.x++;
    if ((tecla == UP || tecla == UPlc) && submarine.y > 5)
        submarine.y--;
    if ((tecla == DOWN || tecla == DOWNlc) && submarine.y < 25)
        submarine.y++;

    PaintSubmarine(submarine, optionSubmarine);
}

#endif
