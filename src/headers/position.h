#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED
#include <windows.h> //Permite darle una posición al cursor.

/*Función para mover el cursor de la consola, en "x" y "y".*/
void gotoxy(int x, int y)
{
    HANDLE hCon;
    //Obtiene el manejador handle de la consola.
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    //Mueve el cursor en la posición "x" y "y".
    SetConsoleCursorPosition(hCon, dwPos);
}

#endif