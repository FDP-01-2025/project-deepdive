#ifndef SUBMARINE_H_INCLUDED
#define SUBMARINE_H_INCLUDED
#include <stdio.h>
#include <conio.h>

#include "../headers/move_cursor.h"

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
    int x, y, heart, lifes;
} Submarine;

/*Pinta al submarino con caracteres del código ASCII*/
void PaintSubmarine(Submarine *submarine)
{
    gotoxy(submarine->x, submarine->y);
    printf("       %c%c", 95, 218);
    gotoxy(submarine->x, submarine->y + 1);
    printf(" %c%c%c%c%c%c%c%c%c%c", 126, 42, 95, 95, 95, 47, 111, 111, 92, 95);
    gotoxy(submarine->x, submarine->y + 2);
    printf("  %c%c%c%c%c%c%c%c%c%c", 40, 95, 95, 95, 95, 95, 95, 95, 95, 41);
}

/*Borra al submarino en cada desplazamiento*/
void DeleteSubmarine(Submarine *submarine)
{
    gotoxy(submarine->x, submarine->y);
    printf("         ");
    gotoxy(submarine->x, submarine->y + 1);
    printf("           ");
    gotoxy(submarine->x, submarine->y + 2);
    printf("            ");
}

/*Pinta la vida y los corazones del submarino*/
void PaintHearts(Submarine *submarine)
{
    gotoxy(80, 1);
    printf("Vidas %d", submarine->lifes);
    gotoxy(100, 1);
    printf("Salud");
    gotoxy(110, 1);
    printf("     ");

    for (int i = 0; i < submarine->heart; i++)
    {
        gotoxy(110 + i, 1);
        printf("%c", 223);
    }
}

/*Se valida si los corazones del submarino son igual a 0,
en caso que sí, se pinta la exploción del submarino.
Para dar el efecto de movimiento, se realizan distintas animaciones con un intervalo de tiempo
para cada una.*/
void DestroySubmarine(Submarine *submarine)
{
    if (submarine->heart == 0)
    {
        DeleteSubmarine(submarine);
        gotoxy(submarine->x, submarine->y);
        printf(" * * * * ");
        gotoxy(submarine->x, submarine->y + 1);
        printf("********");
        gotoxy(submarine->x, submarine->y + 2);
        printf(" * * * * ");
        Sleep(350);
        DeleteSubmarine(submarine);
        gotoxy(submarine->x, submarine->y);
        printf("*    *");
        gotoxy(submarine->x, submarine->y + 1);
        printf(" * * * * ");
        gotoxy(submarine->x, submarine->y + 2);
        printf("*    *");
        Sleep(350);
        DeleteSubmarine(submarine);
        submarine->lifes--;
        PaintHearts(submarine);
        submarine->heart = 1;
        PaintSubmarine(submarine);
    }
}

void MoveSubmarine(Submarine *submarine)
{
    if (kbhit())
    {
        /*Captura los parámetros ingresados por teclado y los guarda en la variable "tecla"*/
        char tecla = getch();
        gotoxy(submarine->x, submarine->y);
        DeleteSubmarine(submarine);

        /*Valida cada tecla presionada, para desplazar al submarino
        en los ejes "x" y "y", y se añade un límite para no salirse del escenario*/

        if (tecla == LEFT || tecla == LEFTlc && submarine->x > 3)
            submarine->x--;
        if (tecla == RIGHT || tecla == RIGHTlc && submarine->x < 106)
            submarine->x++;
        if (tecla == UP || tecla == UPlc && submarine->y > 3)
            submarine->y--;
        if (tecla == DOWN || tecla == DOWNlc && submarine->y < 25)
            submarine->y++;
        gotoxy(submarine->x, submarine->y);
        PaintSubmarine(submarine);
    }
}
#endif