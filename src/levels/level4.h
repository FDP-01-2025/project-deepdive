#ifndef LEVEL4_H
#define LEVEL4_H
#define MAX_MISSILES 100

// --- INCLUDES ---
#include "../headers/position.h"
#include "../headers/hide_cursor.h"
#include "../headers/submarine.h"
#include "../headers/missiles.h"
#include "../headers/fish.h"
#include "../headers/power_item.h"
#include "../headers/invulnerability.h"
#include "../headers/jefe_submarino.h"

#include <conio.h>
#include <ctime>
#include <windows.h>

// ---variables ---
static Submarine level4Submarine;
static Fish level4Fishes[3];
static int level4NumFishes;
static int chosenSubmarineStyleLevel4 = 1; 

static Missiles level4Missiles[MAX_MISSILES];
static int level4MissilesCout;

#define playerMissiles level4Missiles
#define playerMissilesCount level4MissilesCout
#define DANO_MISIL_JUGADOR 10

static int score = 0;

static int misilesDisponibles = 10;
static const int maxMisilesPorRecarga = 10;
static bool puedeDisparar = true;
static double tiempoRecarga = 1000;
static clock_t tiempoUltimoDisparo;

static bool poderRecargaActiva = false;
static double duracionPoder = 5000;
static clock_t tiempoInicioPoder;

static JefeSubmarino jefe;
static bool jefeActivo = false;
static bool jefeDerrotado = false;
static clock_t tiempoAparicionJefe;
static const double tiempoParaJefe = 30000;

// 🟢 NUEVA FUNCIÓN: Mostrar mensaje de inicio del jefe
// 🟢 NUEVA FUNCIÓN: Mostrar mensaje de inicio del jefe
static void mensajeInicioJefeFinal()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string titulo[] = {
        "███████╗██╗███╗   ██╗ █████╗ ██║            ███████╗   ████╗  ██████╗ ██████╗ ",
        "██╔════╝██║████╗  ██║██╔══██╗██║            ██╔═══██╗ ██╔═██╗ ██╔═══╝ ██╔═══╝ ",
        "█████╗  ██║██╔██╗ ██║███████║██║            ███████╔╝ ██║ ██║ ╚█████╗ ╚█████╗ ",
        "██╔══╝  ██║██║╚██╗██║██╔══██║██║            ██╔═══██╗ ██║ ██║ ╚═══██╗ ╚═══██╗ ",
        "██║     ██║██║ ╚████║██║  ██║███████╗       ███████╔╝ ╚████╔╝ █████╔╝ █████╔╝ ",
        "╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝        ╚═════╝   ╚═══╝  ╚════╝  ╚═══╝    ",
    };

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(15, 6 + i);
        std::cout << titulo[i];
    }

    gotoxy(32, 14);
    std::cout << "[ Press ENTER to face the Final Boss ]";

    while (true)
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 13)
                break;
        }
    }

    // 🟡 Mostrar historia con título
    system("cls");

    const std::string tituloHistoria[] = {
        "██╗  ██╗██╗ ███████╗████████╗ ██████╗ ██████╗ ██╗   ██╗",
        "██║  ██║██║ ██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝",
        "███████║██║ ███████╗   ██║   ██║   ██║██████╔╝ ╚████╔╝ ",
        "██╔══██║██║ ╚════██║   ██║   ██║   ██║██╔══██╗  ╚██╔╝  ",
        "██║  ██║██║ ███████║   ██║   ╚██████╔╝██   ██║   ██║   ",
        "╚═╝  ╚═╝╚═╝ ╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   "};

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(20, 3 + i);
        std::cout << tituloHistoria[i];
    }

    // Historia narrativa
    gotoxy(10, 11);
    std::cout << "Después de pasar todos los obstaculos, el submarino se adentra en aguas desconocidas...";

    gotoxy(10, 13);
    std::cout << "El mar se vuelve silencioso. Una sombra inmensa se aproxima.";

    gotoxy(10, 15);
    std::cout << "Los sistemas del submarino detectan una presencia hostil colosal.";

    gotoxy(10, 17);
    std::cout << "Es la Mega Nave alienígena, armada hasta los dientes y con sed de destrucción.";

    gotoxy(10, 19);
    std::cout << "Tú eres la última esperanza para detenerla.";

    gotoxy(25, 22);
    std::cout << "[ Press ENTER to comenzar la batalla final ]";

    while (true)
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 13)
                break;
        }
    }

    system("cls");
}

static void GameOverLevel4()
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string texto[6] = {
        " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗",
        "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
        "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
        "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
        "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
        " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"};

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(25, 6 + i);
        std::cout << texto[i] << "\n\n";
    }
    system("chcp 437 > nul");

    gotoxy(45, 13);
    std::cout << "[Press ENTER twice to continue]" << "\n\n";

    while (true)
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 13)
                break;
        }
    }
}

static void Victory()
{
    system("chcp 65001 > nul");
    const std::string mensajeVictoria[6] = {

        "██╗   ██╗██╗ ██████╗ ████████╗ ██████╗ ██████╗ ██╗   ██╗",
        "██║   ██║██║██╔═══██╗╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝",
        "██║   ██║██║██║   ██║   ██║   ██║   ██║██████╔╝ ╚████╔╝ ",
        "╚██╗ ██╔╝██║██║   ██║   ██║   ██║   ██║██╔══██╗  ╚██╔╝  ",
        " ╚████╔╝ ██║╚██████╔╝   ██║   ╚██████╔╝██║  ██║   ██║   ",
        "  ╚═══╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ",
    };
    system("cls");
    for (int i = 0; i < 6; ++i)
    {
        gotoxy(20, 6 + i);
        std::cout << "\033[1;32m" << mensajeVictoria[i] << "\033[0m";
    }
    system("chcp 437 > nul");

    gotoxy(32, 14);
    std::cout << "\033[1;32m[ Press ENTER to continue ]\033[0m";

    while (true)
    {
        if (kbhit() && getch() == 13)
            break;
    }
}

  static void mostrarEstado(int score, int misilesDisponibles, int maxMisiles)
{
    gotoxy(2, 0);
    std::cout << "PUNTAJE: " << score << "        ";

    gotoxy(2, 1);
    std::cout << "MISILES: " << misilesDisponibles << "/" << maxMisiles << "       ";
}

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
        std::cout << "  ";
        jefeMissiles[i].x -= 2;
        if (jefeMissiles[i].x > 2)
        {
            gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
            std::cout << "\033[1;31m<<\033[0m";
            i++;
        }
        else
        {
            for (int j = i; j < jefeMissilesCout - 1; j++)
            {
                jefeMissiles[j] = jefeMissiles[j + 1];
            }
            jefeMissilesCout--;
        }
    }
}
static void DetectarColisionSubmarinoConJefe(Submarine &sub, JefeSubmarino &jefe) {
    // Verificamos si el área del submarino y el jefe se solapan
    if ((sub.x + 12 >= jefe.x && sub.x <= jefe.x + 18) && // ancho
        (sub.y + 2 >= jefe.y && sub.y <= jefe.y + 3))     // alto
    {
        // Si chocan, submarino muere de una
        sub.heart = 0;
        sub.lifes = 0;
    }
}


static void inicializarJefe()
{
    jefe.x = 100;
    jefe.y = 10;
    jefe.vida = 100;
    jefe.estaEnojado = false;
    jefe.velocidadDisparo = 50;
    jefeActivo = true;
    jefeDerrotado = false;
    PintarJefeSubmarino(jefe);
    DibujarVidaJefe(jefe);
}

static void DetectarImpactoMisilesJugador(JefeSubmarino &jefe)
{
    const int anchoJefe = 18;
    const int altoJefe = 4;
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
            i++;
    }
}

static void actualizarJefe()
{
    if (!jefeActivo || jefeDerrotado)
        return;
    static int contadorMovimiento = 0;
    contadorMovimiento++;
    if (contadorMovimiento % 2 == 0)
    {
        BorrarJefeSubmarino(jefe);
        static bool moviendoseAbajo = true;
        if (moviendoseAbajo)
        {
            jefe.y += (rand() % 2);
            if (jefe.y >= 20)
                moviendoseAbajo = false;
        }
        else
        {
            jefe.y -= (rand() % 2);
            if (jefe.y <= 3)
                moviendoseAbajo = true;
        }
        PintarJefeSubmarino(jefe);
    }
    if (rand() % jefe.velocidadDisparo == 0)
    {
        dispararJefe();
    }
    moverDisparosJefe();
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
                PaintSubmarine(level4Submarine, chosenSubmarineStyleLevel4);
                PaintHearts(level4Submarine);
            }
            gotoxy(jefeMissiles[i].x, jefeMissiles[i].y);
            std::cout << "  ";
            for (int j = i; j < jefeMissilesCout - 1; j++)
                jefeMissiles[j] = jefeMissiles[j + 1];
            jefeMissilesCout--;
        }
        else
            i++;
    }
    // Verificar colisión entre el submarino y el jefe
    DetectarColisionSubmarinoConJefe(level4Submarine, jefe);
    if (!invulnerableActiva &&
        ((level4Submarine.x + 12 >= jefe.x && level4Submarine.x <= jefe.x + 18) &&
         (level4Submarine.y + 2 >= jefe.y && level4Submarine.y <= jefe.y + 3)))
    {
        CollisionSubmarine(level4Submarine);
        PaintHearts(level4Submarine);
    }
}

static void actualizarRecarga(char tecla)
{
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
}

void InitGamelevel4()
{
    mensajeInicioJefeFinal(); // 🟢 NUEVA FUNCIÓN: Mostrar mensaje de inicio del jefe
    level4Submarine = {5, 15, 3, 3};
    PaintSubmarine(level4Submarine, chosenSubmarineStyleLevel4);
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

        if (!jefeActivo && !jefeDerrotado && (clock() - tiempoAparicionJefe) >= tiempoParaJefe)
        {
            inicializarJefe();
        }

        mostrarItem();
        verificarReaparicionItem();
        if (detectarColisionItem(level4Submarine))
        {
            ocultarItem();
            activarPoderRecarga();
        }

        mostrarItemInvulnerable();
        verificarReaparicionItemInvulnerable();
        if (detectarColisionItemInvulnerable(level4Submarine))
        {
            ocultarItemInvulnerable();
            activarInvulnerabilidad();
        }
        actualizarInvulnerabilidad();

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
                i++;
        }

        if (jefeActivo && !jefeDerrotado)
        {
            DetectarImpactoMisilesJugador(jefe);
            actualizarJefe();
        }

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
                CollisionFish(level4Fishes[i], level4Submarine);
            else if (CollisionWithInvulnerability(level4Fishes[i], level4Submarine))
                paint = true;
        }
        if (paint)
            PaintSubmarine(level4Submarine, chosenSubmarineStyleLevel4);

        actualizarPoder();
        actualizarInvulnerabilidad();

        Sleep(10);

    } while (level4Submarine.lifes > 0 && !jefeDerrotado);

    system("cls");
    gotoxy(45, 12);
    system("cls");
    gotoxy(45, 12);

    if (jefeDerrotado)
    {
        Victory();
    }
    else
    {
        gotoxy(45, 12);
        GameOverLevel4();
        Sleep(3000);
    }
}

#endif