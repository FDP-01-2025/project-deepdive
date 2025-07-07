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
//Paint the shape of the fish

static void PaintFish(Fish &fish)
{
    gotoxy(static_cast<int>(fish.x), fish.y);
    std::cout << framesFish[fish.frame];
}

// Clear the shape of the fish
static void ClearFish(Fish &fish)
{
    gotoxy(static_cast<int>(fish.x), fish.y);
    std::cout << ("        ");
}

static void MoveFish(Fish &fish)
{
    // Clear the current representation of the fish from the screen
    ClearFish(fish);
    fish.x -= 0.2f;
    if (fish.x <= 5.0f)
    {
        // Reset the X position of the fish to the right edge (110.0)
        fish.x = 110.0f;
        // Assign a new random Y position
        fish.y = rand() % 25 + 3;
    }
    // Update the animation frame of the fish (cycling between 0, 1, and 2)
    fish.frame = (fish.frame + 1) % 3;
    // Draw the fish in its new position and with the new animation frame
    PaintFish(fish);
}

static void CollisionFish(Fish &fish, Submarine &submarine)
{
    // If the position of the fish is equal to that of the submarine, a collision is detected
    if (fish.x >= submarine.x && fish.x <= submarine.x + 11 && fish.y >= submarine.y && fish.y <= submarine.y + 3)
    {
        submarine.heart--;
        CollisionSubmarine(submarine);
        DestroySubmarine(submarine);
        ClearFish(fish);
        PaintHearts(submarine);
        fish.x = 110;
        fish.y = rand() % 20 + 3;
    }
}

static bool CollisionWithInvulnerability(Fish &fish, Submarine &submarine)
{
    fish.x >= submarine.x &&fish.x <= submarine.x + 11 && fish.y >= submarine.y &&fish.y <= submarine.y + 3;

}
#endif