#ifndef FISH_H
#define FISH_H

#include "position.h"
#include "submarine.h"

typedef struct
{
    int x, y;
} Fish;

// Pinta la forma del pescado
void PaintFish(Fish &fish)
{
    gotoxy(fish.x, fish.y);
    cout << ("<0)))><") << endl;
}

// Borra la forma del pescado
void DeleteFish(Fish &fish)
{
    gotoxy(fish.x, fish.y);
    cout << ("        ") << endl;
}

void MoveFish(Fish &fish)
{
    gotoxy(fish.x, fish.y);
    cout << ("        ") << endl;
    /*Se asigna una posición inicial del pescado en x, y se genera una posición aleatoria en y.
    La posición del pescado va decreciendo en x, hasta llegar a la posición 5 en x,
    y luego se vuelve a ejecutar el mismo proceso.*/
    fish.x--;
    if (fish.x <= 5)
    {
        fish.x = 110;
        fish.y = rand() % 25 + 3;
    }
    PaintFish(fish);
}

/*Se declara el espacio que ocupa el submarino en "x" y "y", si la posición de "x" y "y"
coinciden, se detecta un impacto, se reduce la salud del submarino y los obstáculos vuelven a su posición
inicial.*/
void CollisionFish(Fish &fish, Submarine &submarine)
{
    if (fish.x >= submarine.x && fish.x <= submarine.x + 11 && fish.y >= submarine.y && fish.y <= submarine.y + 3)
    {
        submarine.heart--;
        DestroySubmarine(submarine);
        DeleteFish(fish);
        PaintSubmarine(submarine);
        PaintHearts(submarine);
        fish.x = 110;
        fish.y = rand() % 20 + 3;
    }
}
#endif