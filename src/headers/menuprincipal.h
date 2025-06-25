#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Handle de consola
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Ubica el cursor
inline void goTo(int x, int y)
{
    COORD pos = {SHORT(x), SHORT(y)};
    SetConsoleCursorPosition(hConsole, pos);
}

// Cambia color de texto
inline void setColor(int fg)
{
    SetConsoleTextAttribute(hConsole, fg);
}

#include "../levels/level1.h"
#include "../levels/level2.h"
#include "../levels/level3.h"

// --- Arte ASCII del título ---
const int TITLE_ROWS = 9;
const int MENU_WIDTH = 50;
const std::string titleLines[TITLE_ROWS] = {
    "██████╗ ███████╗███████╗██████╗     ██████╗ ██╗██╗   ██╗███████╗",
    "██╔══██╗██╔════╝██╔════╝██╔══██╗    ██╔══██╗██║██║   ██║██╔════╝",
    "██║  ██║█████╗  █████╗  ██████╔╝    ██║  ██║██║██║   ██║█████╗  ",
    "██║  ██║██╔══╝  ██╔══╝  ██╔═══╝     ██║  ██║██║██║   ██║██╔══╝  ",
    "██████╔╝███████╗███████╗██║         ██████╔╝██║╚██████╔╝███████╗",
    "╚═════╝ ╚══════╝╚══════╝╚═╝         ╚═════╝ ╚═╝ ╚═════╝ ╚══════╝",
    "ESTE MENU AÚN ESTÁ EN DESARROLLO, POR FAVOR SEA PACIENTE, GRACIAS, BESOS",
    "                                                                       "};

// Color aleatorio (1..15)
inline int randomColor()
{
    return rand() % 15 + 1;
}

// Dibuja título en su color
inline void drawTitle(int color)
{
    setColor(color);
    for (int i = 0; i < TITLE_ROWS; ++i)
    {
        goTo(0, i);
        std::cout << titleLines[i];
    }
}

// Dibuja una opción
inline void drawMenuOption(int row, bool selected, const std::string &text)
{
    int y = TITLE_ROWS + row;
    goTo(0, y);
    setColor(selected ? 14 : 7);
    std::cout << (selected ? "➤ " : "  ")
              << text
              << std::string(std::max(0, MENU_WIDTH - int(text.size()) - 3), ' ');
}

// Dibuja borde arriba y abajo del bloque de opciones
inline void MenuBorder(int linesHigh)
{
    setColor(7);
    int yTop = TITLE_ROWS - 2;
    int yBottom = TITLE_ROWS + linesHigh;
    for (int x = 0; x < MENU_WIDTH; ++x)
    {
        goTo(x, yTop);
        std::cout << ' ';
        goTo(x, yBottom);
        std::cout << ' ';
    }
}

// Ejecuta menú principal y submenú de niveles
inline void runMenu()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand((unsigned)time(nullptr));

    const std::string mainOpts[] = {"Start Game", "Options", "High Scores", "Exit"};
    const std::string levelOpts[] = {
        "Nivel 1", "Nivel 2", "Nivel 3",
        "Nivel 4", "Nivel 5", "Regresar"};
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
                            goTo(0, TITLE_ROWS + i);
                            std::cout << std::string(MENU_WIDTH, ' ');
                        }
                        // Pinta submenú
                        for (int i = 0; i < N_level; ++i)
                            drawMenuOption(i, i == selected, levelOpts[i]);
                    }
                    else if (selected == 3)
                    {
                        // Salir
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
                            goTo(0, TITLE_ROWS + i);
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
                            case 0:
                                system("cls");
                                InitGamelevel1();
                                GameLooplevel1();
                                break;
                            case 1:
                                system("cls");
                                InitGamelevel2();
                                GameLooplevel2();
                                break;
                            case 2:;
                                break;
                            case 3:;
                                break;
                            case 4:;
                                break;
                            case 5:;
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
                        goTo(0, TITLE_ROWS + i);
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