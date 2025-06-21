#ifndef MESSAGES_H
#define MESSAGES_H
#include <iostream>
#include <windows.h>

void PrincipalObjectiveLevel2()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Posicionar mensaje en la parte superior central
    COORD mensajePos = {30, 1};
    SetConsoleCursorPosition(hConsole, mensajePos);

    // Cambiar color del texto (amarillo brillante)
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    SetConsoleCursorPosition(hConsole, {40, 7});
    std::cout << "===============================\n";
    SetConsoleCursorPosition(hConsole, {40, 8});
    std::cout << "   OBJETIVO PRINCIPAL:\n";
    SetConsoleCursorPosition(hConsole, {40, 9});
    std::cout << "   RELLENAR LA BARRA DE OXÍGENO\n";
    SetConsoleCursorPosition(hConsole, {40, 10});
    std::cout << "===============================\n";

    Sleep(4000); // Esperar 4 segundos

    // Borrar mensaje sobrescribiendo con espacios
    for (int i = 7; i <= 10; i++)
    {
        SetConsoleCursorPosition(hConsole, {40, (SHORT)i});
        std::cout << "                                   ";
    }

    // Restaurar color por defecto (gris claro)
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void CongratsLevel2()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD mensajePos = {30, 1};
    SetConsoleCursorPosition(hConsole, mensajePos);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    SetConsoleCursorPosition(hConsole, {40, 7});
    std::cout << "***********************************\n";
    SetConsoleCursorPosition(hConsole, {40, 8});
    std::cout << " ¡FELICIDADES! Has completado el nivel\n";
    SetConsoleCursorPosition(hConsole, {40, 9});
    std::cout << "   Has rellenado la barra de oxígeno 30 veces\n";
    SetConsoleCursorPosition(hConsole, {40, 10});
    std::cout << "***********************************\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Sleep(4000);
}

#endif