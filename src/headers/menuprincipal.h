#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>

using namespace std;

const int TITLE_ROWS = 8;
const string titleLines[TITLE_ROWS] = {
    "██████╗  ███████╗  ███████╗ ██████╗       ██████╗   ██╗ ██╗   ██╗ ███████╗",
    "██╔══██╗ ██╔════╝  ██╔════╝ ██╔══██╗      ██╔══██╗  ██║ ██║   ██║ ██╔════╝",
    "██║  ██║ █████╗    █████╗   ██████╔╝      ██║  ██║  ██║ ██║   ██║ █████╗  ",
    "██║  ██║ ██╔══╝    ██╔══╝   ██╔═══╝       ██║  ██║  ██║ ██║   ██║ ██╔══╝  ",
    "██████╔╝ ███████╗  ███████╗ ██║           ██████╔╝  ██║ ╚██████╔╝ ███████╗",
    "╚═════╝  ╚══════╝  ╚══════╝ ╚═╝           ╚═════╝   ╚═╝  ╚═════╝  ╚══════╝",
    "ESTE MENU AÚN ESTÁ EN DESARROLLO, POR FAVOR SEA PACIENTE, GRACIAS, BESOS",
    "                                                                       "
};

const string menuOptions[] = { "Start Game", "Options", "High Scores", "Exit" };
const int numOptions = 4;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void goTo(int x, int y) {
    COORD pos = { SHORT(x), SHORT(y) };
    SetConsoleCursorPosition(hConsole, pos);
}

void setColor(int fg) {
    SetConsoleTextAttribute(hConsole, fg);
}

// Genera un color aleatorio
int randomColor() {
    return rand() % 15 + 1;
}

// Dibuja el título con color aleatorio
void drawTitle(int color) {
    setColor(color);
    for (int i = 0; i < TITLE_ROWS; ++i) {
        goTo(0, i);
        cout << titleLines[i];
    }
}

// Dibuja una opción del menú
void drawMenuOption(int row, bool selected) {
    int y = TITLE_ROWS + row;
    goTo(0, y);
    setColor(selected ? 14 : 7);
    cout << (selected ? "➤ " : "  ") << menuOptions[row];
    cout << string(50 - menuOptions[row].size(), ' '); // Limpia línea
}

void MenuBorder() {
    int width = 50;
    setColor(7);
    for (int i = 0; i < width; ++i) {
        goTo(i, TITLE_ROWS - 1);
        cout << "-";
        goTo(i, TITLE_ROWS + numOptions);
        cout << "-";
    }
}

// **Función principal del menú**
void runMenu() {
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand((unsigned)time(nullptr));

    system("cls");
    int titleColor = randomColor();
    drawTitle(titleColor);
    for (int i = 0; i < numOptions; ++i)
        drawMenuOption(i, i == 0);

    MenuBorder();

    int selected = 0;

    while (true) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 0 || key == 224) {
                key = _getch();
                int prev = selected;
                if (key == 72)        // Flecha arriba
                    selected = (selected + numOptions - 1) % numOptions;
                else if (key == 80)   // Flecha abajo
                    selected = (selected + 1) % numOptions;
                if (prev != selected) {
                    drawMenuOption(prev, false);
                    drawMenuOption(selected, true);
                }
            }
            else if (key == 13) {    // Enter
                system("cls");
                setColor(7);
                cout << "\n>>> " << menuOptions[selected] << " <<<\n\n";
                switch (selected) {
                    case 0: cout << "Iniciando el juego...\n";   break;
                    case 1: cout << "Abriendo configuración...\n"; break;
                    case 2: cout << "Mostrando puntajes altos...\n"; break;
                    case 3:
                        cout << "Saliendo...\n";
                        Sleep(1000);
                        return;
                }
                system("pause");
                system("cls");
                drawTitle(titleColor);
                for (int i = 0; i < numOptions; ++i)
                    drawMenuOption(i, i == selected);
            }
            else if (key == 27) {    // Escape
                goTo(0, TITLE_ROWS + numOptions + 2);
                setColor(7);
                cout << "Saliendo...\n";
                Sleep(500);
                return;
            }
        }
        Sleep(20);
    }
}

#endif