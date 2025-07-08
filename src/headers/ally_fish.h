#ifndef ALLY_FISH_H
#define ALLY_FISH_H

#include <string>
typedef struct
{
    int x, y;
} AllyFish;

// Forward declaration of Submarine class
static const std::string framesAllyFish[] = {
    ">{{{°>",
    ">{{{o>",
    ">{{{0>"};

void PaintAllyFish(AllyFish &ally, Submarine &submarine)
{
    static int allyFrame = 0;

    //Avoid painting over the edge
    if (ally.x > 3 && ally.x < 116 && ally.y > 2 && ally.y < 25)
    {
        //Check that it is not on the top or bottom edge row
        gotoxy(ally.x, ally.y);
        std::cout << framesAllyFish[allyFrame];
        allyFrame = (allyFrame + 2) % 3;
    }
}

void DeleteAllyFish(AllyFish &ally)
{
    gotoxy(ally.x, ally.y);
    std::cout << "       "; //7 spaces to erase the fish
}

#endif