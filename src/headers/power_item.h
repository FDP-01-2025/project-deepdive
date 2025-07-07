#ifndef POWER_ITEM_H
#define POWER_ITEM_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "position.h"
#include "submarine.h"

static int itemX = 0;
static int itemY = 0;
static bool itemVisible = false;

static const int respawnInterval = 20000;
static clock_t lastRespawnTime;

// Generates a new random position for the item
static void generateRandomPosition()
{
    itemX = rand() % 60 + 40;
    itemY = rand() % 18 + 3;
}

// Shows the item on screen
static void showItem()
{
    if (itemVisible)
    {
        gotoxy(itemX, itemY);
        std::cout << "{#}";
    }
}

// Hides the item
static void hideItem()
{
    gotoxy(itemX, itemY);
    std::cout << "   ";
    itemVisible = false;
}

// Detects collision between submarine and item
static bool detectItemCollision(const Submarine& sub)
{
    if (!itemVisible)
        return false;

    int subX = sub.x;
    int subY = sub.y;
    const int subW = 12;
    const int subH = 3;  

    int itemPosX = itemX;
    int itemPosY = itemY;

    if (subX <= itemPosX && itemPosX < subX + subW &&  subY <= itemPosY && itemPosY < subY + subH)
    {
        return true;
    }

    return false;
}

// Checks if the item should respawn
static void checkItemRespawn()
{
    clock_t now = clock();
    if (!itemVisible && now - lastRespawnTime >= respawnInterval)
    {
        generateRandomPosition();
        itemVisible = true;
        lastRespawnTime = now;
    }
}

// Resets the item at level start
static void resetItem()
{
    lastRespawnTime = clock();
    itemVisible = false;
}

#endif // POWER_ITEM_H