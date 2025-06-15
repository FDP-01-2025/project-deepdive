#ifndef SURVIVAL_MODE_H
#define SURVIVAL_MODE_H
#include "../headers/game_limits.h"
#include "../headers/hide_cursor.h"
#include "../headers/fish.h"
#include "../headers/game_time.h"

using namespace std::chrono;
static Submarine submarine;
static Fish fishes[5];
static int num_fishes;

static void InitGame()
{
    submarine = {5, 15, 1, 3};
    PaintSubmarine(&submarine);
    PaintHearts(&submarine);

    fishes[0] = {80, 3};
    fishes[1] = {90, 10};
    fishes[2] = {100, 15};
    fishes[3] = {110, 20};
    fishes[5] = {115, 30};
    num_fishes = 5;
}

static void GameLoop()
{
    // Tiempo de inicio
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    high_resolution_clock::time_point lastFrameTime = high_resolution_clock::now();
    do
    {
        high_resolution_clock::time_point currentFrameTime = high_resolution_clock::now();
        auto deltaTime = duration_cast<milliseconds>(currentFrameTime - lastFrameTime).count();
        lastFrameTime = currentFrameTime;

        auto elapsed = duration_cast<seconds>(currentFrameTime - startTime).count();

        if (kbhit())
        {
            char tecla = getch();
            MoveSubmarine(tecla, &submarine);
        }

        for (int i = 0; i < num_fishes; i++)
        {
            MoveFish(&fishes[i]);
            CollisionFish(&fishes[i], &submarine);
        }
        Sleep(10);

    } while (submarine.lifes > 0);
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(endTime - startTime).count();
    SaveGameTimeToFile(duration, "../database/db_deepdive.txt");
}

#endif