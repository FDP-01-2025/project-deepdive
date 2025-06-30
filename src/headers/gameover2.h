#ifndef GAMEOVER2_H
#define GAMEOVER2_H

#include <iostream>
#include <limits>
#include <windows.h>
#include <conio.h>

// Función inline para evitar redefiniciones múltiples
inline void GameOver2() {
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

    // Vuelve a código de página por defecto
    system("chcp 437 > nul");

    // Espera ENTER sin atrapar otros caracteres
    std::cout << "\tPresiona ENTER dos veces para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

#endif
