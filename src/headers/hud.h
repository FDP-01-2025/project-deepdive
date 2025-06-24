#ifndef HUD_H
#define HUD_H

#include <iostream>
#include "position.h"

static void mostrarEstado(int score, int misilesDisponibles, int maxMisiles)
{
    gotoxy(2, 1);
    std::cout << "Puntaje: " << score << "   ";

    gotoxy(2, 2);
    std::cout << "Misiles: " << misilesDisponibles << "/" << maxMisiles << "   ";
}

#endif
