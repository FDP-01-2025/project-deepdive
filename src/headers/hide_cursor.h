#ifndef HIDE_CURSOR_H_INCLUDED
#define HIDE_CURSOR_H_INCLUDED
#include <windows.h>
void HideCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    //Tamaño del cursor.
    cci.dwSize = 2; 
    //Se asigna false, para definir que el cursor no esté visible.
    cci.bVisible = FALSE;
    //Aplica la configuración para ocultar el cursor.
    SetConsoleCursorInfo(hCon, &cci);
}

#endif