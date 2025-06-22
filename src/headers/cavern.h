#ifndef CAVERN_H
#define CAVERN_H
#include <iostream>
#include <cstdlib>
#include <ctime>

const int width = 40;
const int height = 20;
const int passage = 3;

void desplazarCaverna(char escenario[height][width]) {
    for (int x = 0; x < width - 1; x++) {
        for (int y = 0; y < height; y++) {
            escenario[y][x] = escenario[y][x + 1]; // desplazamiento hacia la izquierda
        }
    }

    // Generar nueva columna aleatoria en el borde derecho
    int alturaArriba = rand() % (height / 3);
    int alturaAbajo = height - passage - (rand() % (height / 3));
    for (int y = 0; y < height; y++) {
        if (y < alturaArriba || y >= alturaAbajo)
            escenario[y][width - 1] = '#';
        else
            escenario[y][width - 1] = ' ';
    }
}

void ShowCavern(char escenery[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            std::cout << (escenery[y][x] ? escenery[y][x] : ' ');
        }
        std::cout << std::endl;
    }
}

#endif