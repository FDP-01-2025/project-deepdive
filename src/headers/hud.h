#ifndef HUD_H
#define HUD_H

#include <iostream>
#include "position.h"

static void mostrarEstado(int score, int misilesDisponibles, int maxMisiles)
{
    gotoxy(2, 0);
    std::cout << "PUNTAJE: " << score << "        ";  // Espacios extra por si el valor anterior era mayor

    gotoxy(2, 1);
    std::cout << "MISILES: " << misilesDisponibles << "/" << maxMisiles << "       ";
}

#endif


