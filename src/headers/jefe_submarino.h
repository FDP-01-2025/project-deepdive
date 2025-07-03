#ifndef JEFE_SUBMARINO_H_INCLUDED
#define JEFE_SUBMARINO_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "position.h"
#include "missiles.h"
#include "submarine.h"

typedef struct {
    int x, y;
    int vida;
    bool estaEnojado;
    int velocidadDisparo;
    int velocidadMovimiento;
    clock_t ultimoDisparo;
} JefeSubmarino;

static Missiles jefeMissiles[10];
static int jefeMissilesCout = 0;

void InicializarJefe(JefeSubmarino &jefe) {
    jefe.x = 100;
    jefe.y = 10;
    jefe.vida = 100;
    jefe.estaEnojado = false;
    jefe.velocidadDisparo = 20;
    jefe.velocidadMovimiento = 2;
    jefe.ultimoDisparo = clock();
}

void DibujarVidaJefe(JefeSubmarino &jefe) {
    gotoxy(50, 1);
    std::cout << "\033[1;31mJEFE: [";

    int vidaRestante = (jefe.vida * 20) / 100;
    for (int i = 0; i < vidaRestante; i++) {
        std::cout << "|";
    }
    for (int i = vidaRestante; i < 20; i++) {
        std::cout << " ";
    }
    std::cout << "] " << jefe.vida << "/100\033[0m";
}

void PintarJefeSubmarino(JefeSubmarino &jefe) {
    gotoxy(jefe.x, jefe.y);
    std::cout << "\033[1;31m    .--.___.--.    \033[0m";
    gotoxy(jefe.x, jefe.y + 1);
    std::cout << "\033[1;31m   /===(====)===\\  \033[0m";
    gotoxy(jefe.x, jefe.y + 2);
    std::cout << "\033[1;31m   \\============/  \033[0m";
    gotoxy(jefe.x, jefe.y + 3);
    std::cout << "\033[1;31m    '--'____'--'   \033[0m";

    DibujarVidaJefe(jefe);
}

void BorrarJefeSubmarino(JefeSubmarino &jefe) {
    for (int i = 0; i < 4; i++) {
        gotoxy(jefe.x, jefe.y + i);
        std::cout << "                     ";
    }
    gotoxy(50, 1);
    std::cout << "                                             ";
}

void MoverJefe(JefeSubmarino &jefe) {
    static int contadorMovimiento = 0;
    contadorMovimiento++;

    if (contadorMovimiento % jefe.velocidadMovimiento == 0) {
        BorrarJefeSubmarino(jefe);

        static bool moviendoseAbajo = true;
        if (moviendoseAbajo) {
            jefe.y += 1;
            if (jefe.y >= 20) moviendoseAbajo = false;
        } else {
            jefe.y -= 1;
            if (jefe.y <= 3) moviendoseAbajo = true;
        }

        PintarJefeSubmarino(jefe);
    }
}

void DispararJefe(JefeSubmarino &jefe) {
    clock_t ahora = clock();
    int tiempoEntreDisparos = jefe.estaEnojado ? 200 : 400;

    if ((ahora - jefe.ultimoDisparo) >= tiempoEntreDisparos && jefeMissilesCout < 10) {
        int cantidadDisparos = jefe.estaEnojado ? (rand() % 2 + 2) : 1;

        for (int i = 0; i < cantidadDisparos && jefeMissilesCout < 10; i++) {
            jefeMissiles[jefeMissilesCout].x = jefe.x - 2;
            jefeMissiles[jefeMissilesCout].y = jefe.y + (rand() % 4);
            jefeMissilesCout++;
        }

        jefe.ultimoDisparo = ahora;
    }
}

void MoverMisilesJefe() {
    for (int i = 0; i < jefeMissilesCout;) {
        gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
        std::cout << "  ";

        jefeMissiles[i].x -= 2;

        if (jefeMissiles[i].x > 2) {
            gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
            std::cout << "\033[1;31m<<\033[0m";
            i++;
        } else {
            for (int j = i; j < jefeMissilesCout - 1; j++) {
                jefeMissiles[j] = jefeMissiles[j + 1];
            }
            jefeMissilesCout--;
        }
    }
}

void LimpiarMisilesJefe() {
    for (int i = 0; i < jefeMissilesCout; i++) {
        gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
        std::cout << "  ";
    }
    jefeMissilesCout = 0;
}

void RecibirDanoJefe(JefeSubmarino &jefe, int dano) {
    jefe.vida -= dano;
    if (jefe.vida < 0) jefe.vida = 0;

    if (jefe.vida < 30 && !jefe.estaEnojado) {
        jefe.estaEnojado = true;
        jefe.velocidadDisparo = 10;
        gotoxy(jefe.x, jefe.y + 4);
        std::cout << "\033[1;91m¡MODO ENOJADO!\033[0m";
    }

    DibujarVidaJefe(jefe);
}

void ExplosionJefe(JefeSubmarino &jefe) {
    for (int frame = 0; frame < 3; frame++) {
        BorrarJefeSubmarino(jefe);

        gotoxy(jefe.x - 2, jefe.y);
        std::cout << "\033[1;33m*** BOOM ***\033[0m";
        gotoxy(jefe.x - 2, jefe.y + 1);
        std::cout << "\033[1;33m  *******  \033[0m";
        Sleep(150);

        gotoxy(jefe.x - 4, jefe.y - 1);
        std::cout << "\033[1;33m**       **\033[0m";
        gotoxy(jefe.x - 2, jefe.y);
        std::cout << "\033[1;33m*  BOOM  *\033[0m";
        gotoxy(jefe.x - 4, jefe.y + 1);
        std::cout << "\033[1;33m**       **\033[0m";
        Sleep(150);

        gotoxy(jefe.x - 6, jefe.y - 2);
        std::cout << "\033[1;33m*           *\033[0m";
        gotoxy(jefe.x - 6, jefe.y - 1);
        std::cout << "\033[1;33m *  BOOOOM  *\033[0m";
        gotoxy(jefe.x - 6, jefe.y);
        std::cout << "\033[1;33m*           *\033[0m";
        Sleep(150);
    }
    BorrarJefeSubmarino(jefe);
    LimpiarMisilesJefe();
}

#endif // JEFE_SUBMARINO_H_INCLUDED
