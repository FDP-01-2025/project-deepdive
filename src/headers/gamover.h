#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <iostream>
#include <limits>
#include <windows.h>  // Sleep, SetConsoleTextAttribute, etc.
#include <conio.h>    // getch()

// Función inline para que puedas incluirla en tantos headers como quieras
inline void GameOver(int duration) {
    int minutes = duration / 60;
    int seconds = duration % 60;

    // Limpia pantalla y activa UTF-8
    system("cls");
    system("chcp 65001 > nul");

    // ASCII art
    std::cout << R"(
      ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗
     ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
     ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝
     ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║██║   ██║██╔══╝  ██╔══██╗
     ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝╚██████╔╝███████╗██║  ██║
      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝

           ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
           ░░       EL JUEGO HA TERMINADO       ░░
           ░░   [Presiona Enter para continuar] ░░
           ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
    )" << "\n\n";

    std::cout << "\tSurvived time: "
              << minutes << " min " << seconds << " sec\n\n";

    // Vuelve a código de página por defecto
    system("chcp 437 > nul");

    // Espera ENTER sin atrapar otros caracteres
    std::cout << "\tPresiona ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

#endif