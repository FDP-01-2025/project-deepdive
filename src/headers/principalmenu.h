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

// Console handle
const static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Change text color
const static void setColor(int fg)
{
    SetConsoleTextAttribute(hConsole, fg);
}

#include "../levels/level1.h"
#include "../levels/level2.h"
#include "../levels/level3.h"
#include "../levels/survival_mode.h"
#include "../headers/game_data.h"
#include "../headers/hide_cursor.h"

// --- ASCII art of the title ---
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

// Function to show players' scores

// Random color (1..15)
const static int randomColor()
{
    return rand() % 15 + 1;
}

// Draw the title in its color
const static void drawTitle(int color)
{
    setColor(color);
    system("chcp 65001 > nul");

    for (int i = 0; i < TITLE_ROWS; ++i)
    {
        gotoxy(22, i);
        std::cout << titleLines[i];
    }
    system("chcp 437 > nul");
}

// Draw a menu option
const static void drawMenuOption(int row, bool selected, const std::string &text)
{

    int y = TITLE_ROWS + row;
    gotoxy(20, y);
    setColor(selected ? 14 : 7);
    system("chcp 65001 > nul");
    std::cout << (selected ? "➤ " : "  ")
              << text
              << std::string(std::max(0, MENU_WIDTH - int(text.size()) - 3), ' ');
    system("chcp 437 > nul");
}

// Draw border above and below the options block
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

// Executes main menu and submenu of levels
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

    // Initial drawing
    system("cls");
    drawTitle(titleColor);
    MenuBorder(linesHigh);
    for (int i = 0; i < N_main; ++i)
        drawMenuOption(i, i == selected, mainOpts[i]);

    // Main loop
    while (true)
    {
        // 1) Update title color every 1s
        DWORD now = GetTickCount();
        if (now - lastTitle >= 1000)
        {
            titleColor = randomColor();
            drawTitle(titleColor);
            lastTitle = now;
        }

        // 2) Manage user input
        if (_kbhit())
        {
            int key = _getch();

            // Arrows
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

                // Repaint only the two affected options
                if (inLevelMenu) {
                    drawMenuOption(prev, false, levelOpts[prev]);
                    drawMenuOption(selected, true, levelOpts[selected]);
                } else {
                    drawMenuOption(prev, false, mainOpts[prev]);
                    drawMenuOption(selected, true, mainOpts[selected]);
                }
            }
            // Enter
            else if (key == 13)
            {
                if (!inLevelMenu)
                {
                    if (selected == 0)
                    {
                        // Enter levels
                        inLevelMenu = true;
                        selected = 0;
                        // Clear main menu
                        for (int i = 0; i < N_main; ++i)
                        {
                            gotoxy(0, TITLE_ROWS + i);
                            std::cout << std::string(MENU_WIDTH, ' ');
                        }
                        // Paint submenu
                        for (int i = 0; i < N_level; ++i)
                            drawMenuOption(i, i == selected, levelOpts[i]);
                    }
                    else if (selected == 1) // High Scores
                    {
                        readFile("database/db_deepdive.txt");

                        // Redraw the main menu
                        system("cls");
                        drawTitle(titleColor);
                        MenuBorder(linesHigh);
                        for (int i = 0; i < N_main; ++i)
                            drawMenuOption(i, i == selected, mainOpts[i]);
                    }
                    else if (selected == 2)
                    {
                        //Within your 'Exit' option, replace the plain message with this block:

                        // 1) Define the ASCII art for 'EXITING' (6 lines)
                        static const std::string exitArt[6] = {
                            "███████╗██╗   ██╗██╗████████╗██╗███╗   ██╗ ███████╗",
                            "██╔════╝╚██╗ ██╔╝██║╚══██╔══╝██║████╗  ██║██╔═════╝",
                            "█████╗   ╚████╔╝ ██║   ██║   ██║██╔██╗ ██║██║  ███╗",
                            "██╔══╝   ╔████║  ██║   ██║   ██║██║╚██╗██║██║   ██║",
                            "███████╗██╔╝ ╚██╗██║   ██║   ██║██║ ╚████║╚██████╔╝",
                            "╚══════╝╚═╝   ╚═╝╚═╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ "};
                        // 2) Clear the screen and adjust color
                        system("cls");
                        setColor(10); // Bright green

                        // 3) Print the lines where you want (e.g. right below the title)
                        system("chcp 65001 > nul");
                        int y0 = TITLE_ROWS + 2;
                        for (int i = 0; i < 6; ++i)
                        {
                            gotoxy(0, y0 + i);
                            std::cout << exitArt[i];
                        }
                        system("chcp 437 > nul");

                        // Animation of blocks █ as ellipsis
                        // After drawing exitArt and restoring CP437, replace the 4-block animation with a loading bar:

                        // Loading bar parameters
                        int yBar = y0 + 7;     // Row where the bar will go
                        int barWidth = 30;     // Total width of the bar
                        char fill = char(219); // █
                        char empty = ' ';

                        // Draw and update the bar
                        for (int i = 0; i <= barWidth; ++i)
                        {
                            gotoxy(0, yBar);
                            std::cout << "Loading: [";
                            // Filled part
                            for (int j = 0; j < barWidth; ++j)
                                std::cout << (j < i ? fill : empty);
                            std::cout << "] ";
                            // Optional percentage
                            std::cout << std::setw(3) << (i * 100 / barWidth) << "%";

                            Sleep(80);
                        }

                        Sleep(300);
                        return;
                    }
                    // Here: Options(1) and High Scores(2)
                }
                else
                {
                    // Within levels
                    if (selected == N_level - 1)
                    {
                        // Back
                        inLevelMenu = false;
                        selected = 0;
                        // Clear levels
                        for (int i = 0; i < N_level; ++i)
                        {
                            gotoxy(0, TITLE_ROWS + i);
                            std::cout << std::string(MENU_WIDTH, ' ');
                        }
                        // Back to main menu
                        for (int i = 0; i < N_main; ++i)
                            drawMenuOption(i, i == selected, mainOpts[i]);
                    }
                    else
                    {
                        // Choose specific level
                        if (selected >= 0 && selected < N_level - 1)
                        {
                            // Execute the corresponding level
                            switch (selected)
                            {
                            case 0:;
                                system("cls");
                                InitGameSurvivalMode();
                                GameLoopSurvivalMode();
                                break;
                            case 1:
                                system("cls");
                                InitGamelevel1();
                                GameLooplevel1();
                                break;
                            case 2:
                                system("cls");
                                InitGamelevel2();
                                GameLooplevel2();
                                break;
                            case 3:
                                system("cls");
                                InitGamelevel3();
                                GameLooplevel3();
                                break;

                            case 4:;
                                break;
                            }
                            // Once we return from the level, we refresh the main menu:
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
                    // Back to main
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