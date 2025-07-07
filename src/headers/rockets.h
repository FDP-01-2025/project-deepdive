#ifndef ROCKETS_
#define ROCKETS_

#include "position.h"
#include "submarine.h"
#include <iostream>

typedef struct
{
    int x, y, frame;
} Rocket;

static const std::string framesRokets[] =
    {
        "<##E==",
        "<##E~~",
        "<##E<<"};
// Pinta la forma del pescado

static void Paintrocket(Rocket &rocket)
{
    gotoxy(static_cast<int>(rocket.x), rocket.y);
    std::cout << framesRokets[rocket.frame];
}

// Borra la forma del pescado
static void ClearRocket(Rocket &rocket)
{
    gotoxy(static_cast<int>(rocket.x), rocket.y);
    std::cout << ("        ");
}

static void MoveRocket(Rocket &rocket, float speed)
{
    ClearRocket(rocket);
    // La cantidad de movimiento depende del parámetro 'speed'
    rocket.x -= speed;

    if (rocket.x <= 5.0f)
    {
        // Reinicia la posición X del cohete al borde derecho (110.0)
        rocket.x = 110.0f;

        // Asigna una nueva posición
        rocket.y = rand() % 25 + 3;
    }
    // Actualiza el frame de animación del cohete (cicla entre 0, 1 y 2)
    rocket.frame = (rocket.frame + 1) % 3;
    // Dibuja el cohete en su nueva posición y con el nuevo frame de animación
    Paintrocket(rocket);
}

static void CollisionRocket(Rocket &rocket, Submarine &submarine)
{
    // Detecta si la posición del cohete es igual a la del submarino
    if (rocket.x >= submarine.x && rocket.x <= submarine.x + 12 && rocket.y >= submarine.y && rocket.y <= submarine.y + 2)
    {
        submarine.heart--;
        if (submarine.heart > 0)
        {
            CollisionSubmarine(submarine);
        }
        DestroySubmarine(submarine);
        ClearRocket(rocket);
        PaintHearts(submarine);
        rocket.x = 110;
        rocket.y = rand() % 20 + 3;
    }
}
#endif