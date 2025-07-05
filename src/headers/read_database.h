#ifndef READ_DATABASE
#define READ_DATABASE
#include <iostream>
#include <fstream>
#include <string>
#include "../headers/hide_cursor.h"

void readFile(const std::string &db_deepdive)
{ 
    system("cls");
    setColor(11);
    gotoxy(0, 0);

    std::ifstream file(db_deepdive);
    if (!file.is_open())
    {
        std::cout << "[DBG] No pude abrir: " << db_deepdive << "\n";
        std::cout << "Pulsa tecla...";
        int c = _getch();
        return;

    }
    std::string line;

    std::cout << "Mejores puntajes:\n\n";
    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }
    std::cout << "\nPresione cualquier tecla para continuar...";
    _getch(); // pausa simple
    file.close();
}

#endif