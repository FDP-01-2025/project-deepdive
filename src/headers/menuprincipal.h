#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <iomanip>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Handle de consola
const static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Cambia color de texto
const static void setColor(int fg)
{
    SetConsoleTextAttribute(hConsole, fg);
}

#include "../levels/level2.h"
#include "../levels/level3.h"
#include "../levels/level4.h"
#include "../levels/survival_mode.h"
#include "../headers/game_data.h"
#include "../headers/hide_cursor.h"

// --- Arte ASCII del título ---
const int TITLE_ROWS = 9;
const int MENU_WIDTH = 50;
const std::string titleLines[TITLE_ROWS] = {
    "██████╗ ███████╗███████╗██████╗     ██████╗ ██╗██╗   ██╗███████╗",
    "██╔══██╗██╔════╝██╔════╝██╔══██╗    ██╔══██╗██║██║   ██║██╔════╝",
    "██║  ██║█████╗  █████╗  ██████╔╝    ██║  ██║██║██║   ██║█████╗  ",
    "██║  ██║██╔══╝  ██╔══╝  ██╔═══╝     ██║  ██║██║╚██╗ ██╔╝██╔══╝  ",
    "██████╔╝███████╗███████╗██║         ██████╔╝██║ ╚████╔╝ ███████╗",
    "╚═════╝ ╚══════╝╚══════╝╚═╝         ╚═════╝ ╚═╝  ╚═══╝  ╚══════╝",
    "ESTE MENU AÚN ESTÁ EN DESARROLLO, POR FAVOR SEA PACIENTE, GRACIAS, BESOS",
    "                                                                       "};

// Función para mostrar scores de los jugadores

// Color aleatorio (1..15)
const static int randomColor()
{
    return rand() % 15 + 1;
}

// Dibuja título en su color
const static void drawTitle(int color)
{
    setColor(color);
    system("chcp 65001 > nul");

    for (int i = 0; i < TITLE_ROWS; ++i)
    {
        gotoxy(0, i);
        std::cout << titleLines[i];
    }
    system("chcp 437 > nul");
}

// Dibuja una opción
const static void drawMenuOption(int row, bool selected, const std::string &text)
{

    int y = TITLE_ROWS + row;
    gotoxy(0, y);
    setColor(selected ? 14 : 7);
    system("chcp 65001 > nul");
    std::cout << (selected ? "➤ " : "  ")
              << text
              << std::string(std::max(0, MENU_WIDTH - int(text.size()) - 3), ' ');
    system("chcp 437 > nul");
}

// Dibuja borde arriba y abajo del bloque de opciones
const static void MenuBorder(int linesHigh)
{
    setColor(7);
    int yTop = TITLE_ROWS - 2;
    int yBottom = TITLE_ROWS + linesHigh;
    for (int x = 0; x < MENU_WIDTH; ++x)
    {
        gotoxy(x, yTop);
        std::cout << ' ';
        gotoxy(x, yBottom);
        std::cout << ' ';
    }
}

// Ejecuta menú principal y submenú de niveles
const static void runMenu()
{
    // setlocale(LC_ALL, "es_ES.UTF-8");
    srand((unsigned)time(nullptr));

    const std::string mainOpts[] = {"Start Levels", "High Scores", "Exit"};
    const std::string levelOpts[] = {
        "SurvivalMode", "Level 1", "Level 2",
        "Final Boss", "Regresar"};
    const int N_main = sizeof(mainOpts) / sizeof(mainOpts[0]);
    const int N_level = sizeof(levelOpts) / sizeof(levelOpts[0]);
    const int linesHigh = std::max(N_main, N_level);

    bool inLevelMenu = false;
    int selected = 0;
    int titleColor = randomColor();
    DWORD lastTitle = GetTickCount();

    // Dibujo inicial
    system("cls");
    drawTitle(titleColor);
    MenuBorder(linesHigh);
    for (int i = 0; i < N_main; ++i)
        drawMenuOption(i, i == selected, mainOpts[i]);

    // Bucle principal
    while (true)
    {
        // 1) Actualizar color del título cada 1s
        DWORD now = GetTickCount();
        if (now - lastTitle >= 1000)
        {
            titleColor = randomColor();
            drawTitle(titleColor);
            lastTitle = now;
        }

        // 2) Gestionar entrada de usuario
        if (_kbhit())
        {
            int key = _getch();

            // Flechas
            if (key == 0 || key == 224)
            {
                key = _getch();
                int prev = selected;
                int N = inLevelMenu ? N_level : N_main;

                if (key == 72) // ↑
                    selected = (selected + N - 1) % N;
                else if (key == 80) // ↓
                    selected = (selected + 1) % N;
                else
                    continue;

                // Repinta únicamente las dos opciones afectadas
                const std::string *opts = inLevelMenu ? levelOpts : mainOpts;
                drawMenuOption(prev, false, opts[prev]);
                drawMenuOption(selected, true, opts[selected]);
            }
            // Enter
            else if (key == 13)
            {
                if (!inLevelMenu)
                {
                    if (selected == 0)
                    {
                        // Entrar a niveles
                        inLevelMenu = true;
                        selected = 0;
                        // Borra menú principal
                        for (int i = 0; i < N_main; ++i)
                        {
                            gotoxy(0, TITLE_ROWS + i);
                            std::cout << std::string(MENU_WIDTH, ' ');
                        }
                        // Pinta submenú
                        for (int i = 0; i < N_level; ++i)
                            drawMenuOption(i, i == selected, levelOpts[i]);
                    }
                    else if (selected == 1) // High Scores
                    {
                        readFile("database/db_deepdive.txt");

                        // Redibuja el menú principal
                        system("cls");
                        drawTitle(titleColor);
                        MenuBorder(linesHigh);
                        for (int i = 0; i < N_main; ++i)
                            drawMenuOption(i, i == selected, mainOpts[i]);
                    }
                    else if (selected == 2)
                    {
                                                // Dentro de tu opción “Salir”, sustituye el mensaje plano por este bloque:

                        // 1) Define el ASCII art para “EXITING” (6 líneas)
                        static const std::string exitArt[6] = {
                            "███████╗██╗   ██╗██╗████████╗██╗███╗   ██╗ ███████╗",
                            "██╔════╝╚██╗ ██╔╝██║╚══██╔══╝██║████╗  ██║██╔═════╝",
                            "█████╗   ╚████╔╝ ██║   ██║   ██║██╔██╗ ██║██║  ███╗",
                            "██╔══╝   ╔████║  ██║   ██║   ██║██║╚██╗██║██║   ██║",
                            "███████╗██╔╝ ╚██╗██║   ██║   ██║██║ ╚████║╚██████╔╝",
                            "╚══════╝╚═╝   ╚═╝╚═╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ "};
                        // 2) Limpia la panta a y ajusta color
                        system("cls");
                        setColor(10); // Verde brillante

                        // 3) Imprime las líneas donde quieras (ejemplo justo debajo del título)
                        system("chcp 65001 > nul");
                        int y0 = TITLE_ROWS + 2;
                        for (int i = 0; i < 6; ++i)
                        {
                            gotoxy(0, y0 + i);
                            std::cout << exitArt[i];
                        }
                        system("chcp 437 > nul");

                        // Animación de bloques █ como puntos suspensivos
                        // Tras dibujar exitArt y restaurar CP437, reemplaza la animación de 4 bloques por una barra de carga:

                        // Parámetros de la barra
                        int yBar = y0 + 7;     // fila donde la barras irá
                        int barWidth = 30;     // ancho total de la barra
                        char fill = char(219); // █
                        char empty = ' ';

                        // Dibuja y actualiza la barra
                        for (int i = 0; i <= barWidth; ++i)
                        {
                            gotoxy(0, yBar);
                            std::cout << "Cargando: [";
                            // Parte llena
                            for (int j = 0; j < barWidth; ++j)
                                std::cout << (j < i ? fill : empty);
                            std::cout << "] ";
                            // Porcentaje opcional
                            std::cout << std::setw(3) << (i * 100 / barWidth) << "%";

                            Sleep(80);
                        }

                        Sleep(300);
                        return;
                    }
                    // Aquí: Options(1) y High Scores(2)
                }
                else
                {
                    // Dentro de niveles
                    if (selected == N_level - 1)
                    {
                        // Regresar
                        inLevelMenu = false;
                        selected = 0;
                        // Borra niveles
                        for (int i = 0; i < N_level; ++i)
                        {
                            gotoxy(0, TITLE_ROWS + i);
                            std::cout << std::string(MENU_WIDTH, ' ');
                        }
                        // Vuelve a menú principal
                        for (int i = 0; i < N_main; ++i)
                            drawMenuOption(i, i == selected, mainOpts[i]);
                    }
                    else
                    {
                        // Elegir nivel concreto
                        if (selected >= 0 && selected < N_level - 1)
                        {
                            // Ejecutar el nivel correspondiente
                            switch (selected)
                            {
                            case 0:;
                                system("cls");
                                InitGameSurvivalMode();
                                GameLoopSurvivalMode();
                                break;
                            case 1:
                                system("cls");
                                InitGamelevel2();
                                GameLooplevel2();
                                break;
                            case 2:
                                system("cls");
                                InitGamelevel3();
                                GameLooplevel3();
                                break;
                            case 3:
                                system("cls");
                                InitGamelevel4();
                                GameLooplevel4();
                                break;

                            case 4:;
                                break;
                            }
                            // Una vez que regrese del nivel, refrescamos el menú principal:
                            system("cls");
                            drawTitle(titleColor);
                            MenuBorder(linesHigh);
                            inLevelMenu = false;
                            selected = 0;
                            for (int i = 0; i < N_main; ++i)
                                drawMenuOption(i, i == selected, mainOpts[i]);
                        }
                    }
                }
            }
            // Escape
            else if (key == 27)
            {
                if (inLevelMenu)
                {
                    // Regresar a principal
                    inLevelMenu = false;
                    selected = 0;
                    for (int i = 0; i < N_level; ++i)
                    {
                        gotoxy(0, TITLE_ROWS + i);
                        std::cout << std::string(MENU_WIDTH, ' ');
                    }
                    for (int i = 0; i < N_main; ++i)
                        drawMenuOption(i, i == selected, mainOpts[i]);
                }
                else
                {
                    return;
                }
            }
        }

        Sleep(20);
    }
}

#endif // MENUPRINCIPAL_H