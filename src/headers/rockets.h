#ifndef ROCKETS_
#define ROCKETS_

#include "position.h"
#include "submarine.h"
#include <iostream>

typedef struct
{
    int x, y, frame;
} Rocket;

std::string frames[] =
    {
        "<##E==",
        "<##E~~",
        "<##E<<"
    };
// Pinta la forma del pescado

void Paintrocket(Rocket &rocket)
{
    gotoxy(static_cast<int>(rocket.x), rocket.y);
    std::cout << frames[rocket.frame];
}

// Borra la forma del pescado
void ClearRocket(Rocket &rocket)
{
    gotoxy(static_cast<int>(rocket.x), rocket.y);
    std::cout << ("        ");
}

void MoveRocket(Rocket &rocket)
{
    ClearRocket(rocket);
    /*Se asigna una posición inicial del pescado en x, y se genera una posición aleatoria en y.
    La posición del pescado va decreciendo en x, hasta llegar a la posición 5 en x,
    y luego se vuelve a ejecutar el mismo proceso.*/
    rocket.x -= 0.2f;
    if (rocket.x <= 5.0f)
    {
        rocket.x = 110.0f;
        rocket.y = rand() % 25 + 3;
    }
    rocket.frame = (rocket.frame + 1) % 3;
    Paintrocket(rocket);
}

/*Se declara el espacio que ocupa el submarino en "x" y "y", si la posición de "x" y "y"
coinciden, se detecta un impacto, se reduce la salud del submarino y los obstáculos vuelven a su posición
inicial.*/
void CollisionRocket(Rocket &rocket, Submarine &submarine)
{
    if (rocket.x >= submarine.x && rocket.x <= submarine.x + 11 && rocket.y >= submarine.y && rocket.y <= submarine.y + 3)
    {
        submarine.heart--;
        CollisionSubmarine(submarine);
        DestroySubmarine(submarine);
        ClearRocket(rocket);
        PaintSubmarine(submarine);
        PaintHearts(submarine);
        rocket.x = 110;
        rocket.y = rand() % 20 + 3;
    }
}
#endif