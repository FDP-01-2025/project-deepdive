#ifndef ALLY_FISH_H
#define ALLY_FISH_H

#include <string>
typedef struct
{
    int x, y;
} AllyFish;

static const std::string framesAllyFish[] = {
    ">{{{°>",
    ">{{{o>",
    ">{{{0>"};

void PaintAllyFish(AllyFish &ally, Submarine &submarine)
{
    static int allyFrame = 0;

    // Evitar pintar sobre el borde
    if (ally.x > 3 && ally.x < 116 && ally.y > 2 && ally.y < 25)
    {
        // Verifica que no esté en la fila del borde superior o inferior
        gotoxy(ally.x, ally.y);
        std::cout << framesAllyFish[allyFrame];
        allyFrame = (allyFrame + 2) % 3;
    }
}

void DeleteAllyFish(AllyFish &ally)
{
    gotoxy(ally.x, ally.y);
    std::cout << "       "; // 7 espacios para borrar el pez
}

#endif