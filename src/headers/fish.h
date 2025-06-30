#ifndef FISH_H
#define FISH_H

#include "position.h"
#include "submarine.h"
#include <iostream>

typedef struct
{
    int x, y, frame;
} Fish;

static const std::string framesFish[] =
    {
        "<0)))><",
        "<°)))><",
        "<o)))><"};
// Pinta la forma del pescado

static void PaintFish(Fish &fish)
{
    gotoxy(static_cast<int>(fish.x), fish.y);
    std::cout << framesFish[fish.frame];
}

// Borra la forma del pescado
static void ClearFish(Fish &fish)
{
    gotoxy(static_cast<int>(fish.x), fish.y);
    std::cout << ("        ");
}

static void MoveFish(Fish &fish)
{
    // Borra la representación actual del pez de la pantalla
    ClearFish(fish);
    fish.x -= 0.2f;
    if (fish.x <= 5.0f)
    {
        // Reinicia la posición X del pez al borde derecho (110.0)
        fish.x = 110.0f;
        // Asigna una nueva posición Y aleatoria
        fish.y = rand() % 25 + 3;
    }
    // Actualiza el frame de animación del pez (cicla entre 0, 1 y 2)
    fish.frame = (fish.frame + 1) % 3;
    // Dibuja el pez en su nueva posición y con el nuevo frame de animación
    PaintFish(fish);
}


static void CollisionFish(Fish &fish, Submarine &submarine)
{
    //Si la posición del pescado es igual a la del submarino, se detecta la colisión
    if (fish.x >= submarine.x && fish.x <= submarine.x + 11 && fish.y >= submarine.y && fish.y <= submarine.y + 3)
    {
        submarine.heart--;
        CollisionSubmarine(submarine);
        DestroySubmarine(submarine);
        ClearFish(fish);
        PaintSubmarine(submarine);
        PaintHearts(submarine);
        fish.x = 110;
        fish.y = rand() % 20 + 3;
    }
}
#endif