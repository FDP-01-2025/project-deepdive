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
 // Paint the shape of the fish

static void PaintRocket(Rocket &rocket)
{
    gotoxy(static_cast<int>(rocket.x), rocket.y);
    std::cout << framesRokets[rocket.frame];
}

//Remove the shape of the fish
static void ClearRocket(Rocket &rocket)
{
    gotoxy(static_cast<int>(rocket.x), rocket.y);
    std::cout << ("        ");
}

static void MoveRocket(Rocket &rocket, float speed)
{
    ClearRocket(rocket);
    //The amount of motion depends on the 'speed' parameter.
    rocket.x -= speed;

    if (rocket.x <= 5.0f)
    {
        // Reset the rocket's X position to the right edge (110.0)
        rocket.x = 110.0f;

        // Assign a new position
        rocket.y = rand() % 25 + 3;
    }
    // Update the rocket's animation frame (cycles between 0, 1, and 2)
    rocket.frame = (rocket.frame + 1) % 3;
    // Draw the rocket in its new position and with the new animation frame
    PaintRocket(rocket);
}

static void CollisionRocket(Rocket &rocket, Submarine &submarine)
{
    // Detect if the rocket's position is equal to the submarine's
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