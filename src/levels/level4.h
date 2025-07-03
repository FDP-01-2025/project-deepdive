#ifndef LEVEL4_H
#define LEVEL4_H
#define MAX_MISSILES 100

// --- LUEGO LOS INCLUDES ---
#include "../headers/position.h"
#include "../headers/hide_cursor.h"
#include "../headers/submarine.h"
#include "../headers/missiles.h"
#include "../headers/fish.h"
#include "../headers/hud.h"
#include "../headers/power_item.h"
#include "../headers/invulnerability.h"
#include "../headers/jefe_submarino.h"

#include <conio.h>
#include <ctime>
#include <windows.h>

// --- Tus variables y defines ---
static Submarine level4Submarine;
static Fish level4Fishes[3];
static int level4NumFishes;

static Missiles level4Missiles[MAX_MISSILES];
static int level4MissilesCout;

#define playerMissiles level4Missiles
#define playerMissilesCount level4MissilesCout
#define DANO_MISIL_JUGADOR 10

static int score = 0;

// Misiles jugador
static int misilesDisponibles = 10;
static const int maxMisilesPorRecarga = 10;
static bool puedeDisparar = true;
static double tiempoRecarga = 1000;
static clock_t tiempoUltimoDisparo;

// Poder de recarga rápida
static bool poderRecargaActiva = false;
static double duracionPoder = 5000;
static clock_t tiempoInicioPoder;

// Jefe
static JefeSubmarino jefe;
static bool jefeActivo = false;
static bool jefeDerrotado = false;
static clock_t tiempoAparicionJefe;
static const double tiempoParaJefe = 30000; // 30 segundos

// ------------------ FUNCIONES DE PODER -----------------------

static void activarPoderRecarga()
{
    poderRecargaActiva = true;
    tiempoRecarga = 300;
    tiempoInicioPoder = clock();

    misilesDisponibles = maxMisilesPorRecarga;
    puedeDisparar = true;
    mostrarEstado(score, misilesDisponibles, maxMisilesPorRecarga);
}

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

// ------------------ FUNCIONES DEL JEFE -----------------------

// static void dibujarVidaJefe()
// {

//     // Dibuja la barra de vida del jefe en la parte superior central
//     gotoxy(50, 1);
//     std::cout << "\033[1;31mJEFE: [";

//     int vidaRestante = (jefe.vida * 20) / 100; // 20 caracteres de ancho

//     // Parte llena de la barra
//     for (int i = 0; i < vidaRestante; i++)
//     {
//         std::cout << "|";
//     }

//     // Parte vacía de la barra
//     for (int i = vidaRestante; i < 20; i++)
//     {
//         std::cout << " ";
//     }

//     std::cout << "] " << jefe.vida << "/100\033[0m";
// }

static void limpiarDisparosJefe()
{
    for (int i = 0; i < jefeMissilesCout; i++)
    {
        gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
        std::cout << "  ";
    }
    jefeMissilesCout = 0;
}

static void dispararJefe()
{
    if (jefeMissilesCout < 10)
    {
        jefeMissiles[jefeMissilesCout].x = jefe.x - 2;
        jefeMissiles[jefeMissilesCout].y = jefe.y + 2;
        jefeMissilesCout++;
    }
}

static void moverDisparosJefe()
{
    for (int i = 0; i < jefeMissilesCout;)
    {
        gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
        std::cout << "  "; // Limpiar anterior

        jefeMissiles[i].x -= 2; // Mover hacia la izquierda

        // Verificar si el misil sigue en pantalla
        if (jefeMissiles[i].x > 2)
        {
            gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
            std::cout << "\033[1;31m<<\033[0m"; // Dibujar nuevo
            i++;
        }
        else
        {
            // Eliminar misil si sale de pantalla
            for (int j = i; j < jefeMissilesCout - 1; j++)
            {
                jefeMissiles[j] = jefeMissiles[j + 1];
            }
            jefeMissilesCout--;
        }
    }
}

static void inicializarJefe()
{
    jefe.x = 100; // Posición inicial a la derecha
    jefe.y = 10;
    jefe.vida = 100;
    jefe.estaEnojado = false;
    jefe.velocidadDisparo = 50; // Más lento que antes
    jefeActivo = true;
    jefeDerrotado = false;
    PintarJefeSubmarino(jefe);
    DibujarVidaJefe(jefe);
}

// NUEVA FUNCIÓN IMPLEMENTADA AQUÍ
static void DetectarImpactoMisilesJugador(JefeSubmarino &jefe)
{
    const int anchoJefe = 18; // Ancho área del jefe
    const int altoJefe = 4;   // Alto área del jefe

    for (int i = 0; i < level4MissilesCout;)
    {
        bool impacto =
            level4Missiles[i].x >= jefe.x &&
            level4Missiles[i].x <= jefe.x + anchoJefe &&
            level4Missiles[i].y >= jefe.y &&
            level4Missiles[i].y <= jefe.y + altoJefe - 1;

        if (impacto)
        {
            RecibirDanoJefe(jefe, DANO_MISIL_JUGADOR);

            gotoxy(level4Missiles[i].x, level4Missiles[i].y);
            std::cout << "  ";

            level4Missiles[i] = level4Missiles[level4MissilesCout - 1];
            level4MissilesCout--;

            DibujarVidaJefe(jefe);

            if (jefe.vida <= 0)
            {
                jefeDerrotado = true;
                limpiarDisparosJefe();
                ExplosionJefe(jefe);
                score += 100;
                mostrarEstado(score, misilesDisponibles, maxMisilesPorRecarga);
                break;
            }
        }
        else
        {
            i++;
        }
    }
}

static void actualizarJefe()
{
    if (!jefeActivo || jefeDerrotado)
        return;

    // Mover jefe más lentamente (cada 2 iteraciones)
    static int contadorMovimiento = 0;
    contadorMovimiento++;
    if (contadorMovimiento % 2 == 0)
    {
        BorrarJefeSubmarino(jefe);

        // Movimiento vertical más lento y suave
        static bool moviendoseAbajo = true;
        if (moviendoseAbajo)
        {
            jefe.y += (rand() % 2); // 0 o 1
            if (jefe.y >= 20)
                moviendoseAbajo = false;
        }
        else
        {
            jefe.y -= (rand() % 2); // 0 o 1
            if (jefe.y <= 3)
                moviendoseAbajo = true;
        }

        PintarJefeSubmarino(jefe);
    }

    // Disparar aleatoriamente
    if (rand() % jefe.velocidadDisparo == 0)
    {
        dispararJefe();
    }

    moverDisparosJefe();

    // Verificar colisión de misiles del jefe con el submarino
    for (int i = 0; i < jefeMissilesCout;)
    {
        if ((jefeMissiles[i].x >= level4Submarine.x && jefeMissiles[i].x <= level4Submarine.x + 12) &&
            (jefeMissiles[i].y >= level4Submarine.y && jefeMissiles[i].y <= level4Submarine.y + 3))
        {
            if (!invulnerableActiva)
            {

                level4Submarine.heart--;
                if (level4Submarine.heart > 0)
                {
                    CollisionSubmarine(level4Submarine);
                }
                DestroySubmarine(level4Submarine);
                PaintSubmarine(level4Submarine);
                PaintHearts(level4Submarine);

                PaintHearts(level4Submarine);
            }
            gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
            std::cout << "  ";
            for (int j = i; j < jefeMissilesCout - 1; j++)
            {
                jefeMissiles[j] = jefeMissiles[j + 1];
            }
            jefeMissilesCout--;
        }
        else
        {
            i++;
        }
    }

    // Verificar colisión directa del submarino con el jefe
    if (!invulnerableActiva &&
        ((level4Submarine.x + 12 >= jefe.x && level4Submarine.x <= jefe.x + 18) &&
         (level4Submarine.y + 2 >= jefe.y && level4Submarine.y <= jefe.y + 3)))
    {
        CollisionSubmarine(level4Submarine);
        PaintHearts(level4Submarine);
    }
}

// ------------------ JUEGO -----------------------

static void actualizarRecarga(char tecla)
{
    if (tecla == 32 && puedeDisparar && misilesDisponibles > 0 && level4MissilesCout < MAX_MISSILES)
    {
        if (misilesDisponibles > 0)
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
    }
}

void InitGamelevel4()
{
    level4Submarine = {5, 15, 3, 3};
    PaintSubmarine(level4Submarine);
    PaintHearts(level4Submarine);

    level4Fishes[0] = {90, 3};
    level4Fishes[1] = {80, 12};
    level4Fishes[2] = {100, 17};

    level4NumFishes = 3;
    level4MissilesCout = 0;
    jefeMissilesCout = 0;

    score = 0;
    misilesDisponibles = maxMisilesPorRecarga;
    puedeDisparar = true;

    jefeActivo = false;
    jefeDerrotado = false;
    tiempoAparicionJefe = clock();

    reiniciarItem();
    mostrarEstado(score, misilesDisponibles, maxMisilesPorRecarga);
}

void GameLooplevel4()
{
    char tecla = 0;
    bool paint = false;

    do
    {
        HideCursor();

        if (kbhit())
        {
            tecla = getch();

            actualizarRecarga(tecla);
            MoveSubmarine(tecla, level4Submarine);
        }

        // Activar jefe después de 30 segundos si no está activo
        if (!jefeActivo && !jefeDerrotado &&
            (clock() - tiempoAparicionJefe) >= tiempoParaJefe)
        {
            inicializarJefe();
        }

        // --- RECARGA ---
        mostrarItem();
        verificarReaparicionItem();
        if (detectarColisionItem(level4Submarine))
        {
            ocultarItem();
            activarPoderRecarga();
        }

        // --- INVULNERABILIDAD ---
        mostrarItemInvulnerable();
        verificarReaparicionItemInvulnerable();
        if (detectarColisionItemInvulnerable(level4Submarine))
        {
            ocultarItemInvulnerable();
            activarInvulnerabilidad();
        }
        actualizarInvulnerabilidad();

        // Mover misiles del jugador
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

        // Actualizar jefe si está activo
        if (jefeActivo && !jefeDerrotado)
        {
            DetectarImpactoMisilesJugador(jefe);
            actualizarJefe();
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
            if (!erasedMissil)
                i++;
        }

        for (int i = 0; i < level4NumFishes; i++)
        {
            MoveFish(level4Fishes[i]);
            if (!invulnerableActiva)
            {
                CollisionFish(level4Fishes[i], level4Submarine);
            }
            else if (CollisionWithInvulnerability(level4Fishes[i], level4Submarine))
            {
                paint = true;
            }
        }
        if (paint)
        {
            PaintSubmarine(level4Submarine);
        }
        actualizarPoder();
        actualizarInvulnerabilidad();

        Sleep(10);
    } while (level4Submarine.lifes > 0);
}

#endif
