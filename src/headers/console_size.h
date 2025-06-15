#ifndef CONSOLE_SIZE_H
#define CONSOLE_SIZE_H
#include "../libraries/libraries.h"

void SetConsoleSize(int width, int height)
{
    // Obtener el handle de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Establecer el tamaño del búfer
    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Establecer el tamaño de la ventana
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height - 1;
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

#endif