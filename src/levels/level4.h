#ifndef LEVEL4_H
#define LEVEL4_H
#define MAX_MISSILES 100

#include "../headers/position.h"
#include "../headers/hide_cursor.h"

#include "../headers/submarine.h"
#include "../headers/missiles.h"
#include "../headers/fish.h"
#include "../headers/hud.h"
#include "../headers/power_item.h"

#include <conio.h>
#include <ctime>
#include <windows.h>

static Submarine level4Submarine;
static Fish level4Fishes[3];
static int level4NumFishes;

static Missiles level4Missiles[MAX_MISSILES];
static int level4MissilesCout;

static int score = 0;

// Para limitar misiles
static int misilesDisponibles = 10;
static const int maxMisilesPorRecarga = 10;
static bool puedeDisparar = true;
static double tiempoRecarga = 1000;
static clock_t tiempoUltimoDisparo;

// Poder de recarga rápida
static bool poderRecargaActiva = false;
static double duracionPoder = 5000;
static clock_t tiempoInicioPoder;

static void activarPoderRecarga()
{
    poderRecargaActiva = true;
    tiempoRecarga = 300;
    tiempoInicioPoder = clock();

    //Recarga inmediata de misiles
    misilesDisponibles = maxMisilesPorRecarga;
    puedeDisparar = true;
    mostrarEstado(score, misilesDisponibles, maxMisilesPorRecarga);
    
}
 //Holaaaaa
static void actualizarPoder()
{
    if (poderRecargaActiva)
    {
        clock_t ahora = clock();
        if (ahora - tiempoInicioPoder >= duracionPoder)
        {
            poderRecargaActiva = false;
            tiempoRecarga = 1000;
        }
    }
}

static void actualizarRecarga()
{
    if (!puedeDisparar)
    {
        clock_t ahora = clock();
        if (ahora - tiempoUltimoDisparo >= tiempoRecarga)
        {
            puedeDisparar = true;
            misilesDisponibles = maxMisilesPorRecarga;
        }
    }
}

static void InitGameLevel4()
{
    level4Submarine = {5, 15, 1, 3};
    PaintSubmarine(level4Submarine);
    PaintHearts(level4Submarine);

    level4Fishes[0] = {90, 3};
    level4Fishes[1] = {80, 12};
    level4Fishes[2] = {100, 17};

    level4NumFishes = 3;
    level4MissilesCout = 0;

    score = 0;
    misilesDisponibles = maxMisilesPorRecarga;
    puedeDisparar = true;

    reiniciarItem(); // inicia el temporizador del ítem
    mostrarEstado(score, misilesDisponibles, maxMisilesPorRecarga);
}

static void GameLoopLevel4()
{
    do
    {
        HideCursor();
      

        if (kbhit())
        {
            char tecla = getch();

            if (tecla == 32 && puedeDisparar && misilesDisponibles > 0 && level4MissilesCout < MAX_MISSILES)
            {
                level4Missiles[level4MissilesCout].x = level4Submarine.x + 12;
                level4Missiles[level4MissilesCout].y = level4Submarine.y + 2;
                level4MissilesCout++;
                misilesDisponibles--;

                if (misilesDisponibles == 0)
                {
                    puedeDisparar = false;
                    tiempoUltimoDisparo = clock();
                }

                mostrarEstado(score, misilesDisponibles, maxMisilesPorRecarga);
            }

            MoveSubmarine(tecla, level4Submarine);
        }

        // Colisión con ítem *
        if (detectarColisionItem(level4Submarine))
        {
            ocultarItem();
            activarPoderRecarga();
        }

        // Mover misiles
        for (int i = 0; i < level4MissilesCout;)
        {
            MoveMissil(level4Missiles[i]);
            if (level4Missiles[i].x >= 115)
            {
                gotoxy(level4Missiles[i].x, level4Missiles[i].y);
                std::cout << "  ";
                level4Missiles[i] = level4Missiles[level4MissilesCout - 1];
                level4MissilesCout--;
            }
            else
            {
                i++;
            }
        }

        // Colisión misil vs pez
        for (int i = 0; i < level4MissilesCout;)
        {
            bool erasedMissil = false;

            for (int j = 0; j < level4NumFishes; j++)
            {
                if ((level4Missiles[i].x == level4Fishes[j].x || level4Missiles[i].x == level4Fishes[j].x + 3 || level4Missiles[i].x == level4Fishes[j].x + 6) &&
                    level4Missiles[i].y == level4Fishes[j].y)
                {
                    gotoxy(level4Missiles[i].x, level4Missiles[i].y);
                    std::cout << "  ";
                    level4Missiles[i] = level4Missiles[level4MissilesCout - 1];
                    level4MissilesCout--;
                    erasedMissil = true;

                    gotoxy(level4Fishes[j].x, level4Fishes[j].y);
                    std::cout << "         ";
                    level4Fishes[j].x = 110;
                    level4Fishes[j].y = rand() % 20 + 3;

                    score += 10;
                    mostrarEstado(score, misilesDisponibles, maxMisilesPorRecarga);
                    break;
                }
            }
            if (!erasedMissil) i++;
        }

        for (int i = 0; i < level4NumFishes; i++)
        {
            MoveFish(level4Fishes[i]);
            CollisionFish(level4Fishes[i], level4Submarine);
        }

        verificarReaparicionItem(); // aparece cada 20s si no está
        mostrarItem();              // muestra el ítem si está visible

        actualizarRecarga();
        actualizarPoder();

        Sleep(5);
    } while (level4Submarine.lifes > 0);
}

#endif
