#ifndef POWER_ITEM_H
#define POWER_ITEM_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "position.h"
#include "submarine.h"

static int itemX = 0;
static int itemY = 0;
static bool itemVisible = false;

static const int intervaloReaparicion = 20000;
static clock_t tiempoUltimaReaparicion;

static void generarPosicionAleatoria()
{
    itemX = rand() % 60 + 40;
    itemY = rand() % 18 + 3;
}

static void mostrarItem()
{
    if (itemVisible)
    {
        gotoxy(itemX, itemY);
        std::cout << "{#}";
    }
}

static void ocultarItem()
{
    gotoxy(itemX, itemY);
    std::cout << " ";
    itemVisible = false;
}

static bool detectarColisionItem(const Submarine& sub)
{
    return itemVisible &&
           sub.x + 6 >= itemX &&
           sub.x <= itemX + 1 &&
           sub.y + 2 == itemY;
}

static void verificarReaparicionItem()
{
    clock_t ahora = clock();
    if (!itemVisible && ahora - tiempoUltimaReaparicion >= intervaloReaparicion)
    {
        generarPosicionAleatoria();
        itemVisible = true;
        tiempoUltimaReaparicion = ahora;
    }
}

static void reiniciarItem()
{
    tiempoUltimaReaparicion = clock();
    itemVisible = false;
}

#endif