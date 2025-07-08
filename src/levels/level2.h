#ifndef LEVEL2_H
#define LEVEL2_H

#include "../headers/fish.h"
#include "../headers/submarine.h"
#include "../headers/game_limits.h"
#include "../headers/ally_fish.h"
#include <chrono>

static void WaitEnterlevel2()  // Function to wait for the user to press Enter
{
    gotoxy(46, 15);              // Position the cursor at (46, 15)
    std::cout << "[Press ENTER to continue]\n\n";  // Display message to wait for Enter key

    while (true)   // Loop until Enter is pressed
    {
        int key = _getch();  // Get the key pressed by the user
        if (key == 13)
            break; // 13 = Enter
        gotoxy(46, 15);
        std::cout << "[Only press ENTER to continue]\n\n";   // Display message if any other key is pressed
    }
}

static Submarine level2Submarine;  // Submarine object for level 2
static AllyFish allySubmarine;      // Ally fish object for level 2
static Fish level2Fishes[4];    // Array of fish objects for level 2
static int level2NumFishes;   // Number of fish in level 2

static void InitGameMessagelevel2()  // Function to initialize the game message for level 2
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string title[7] = {
        "██╗      ███████╗ ██╗   ██╗ ███████╗ ██╗               ██████╗ ",
        "██║      ██╔════╝ ██║   ██║ ██╔════╝ ██║               ╚════██╗",
        "██║      █████╗   ██║   ██║ █████╗   ██║                █████╔╝",
        "██║      ██╔══╝   ╚██╗ ██╔╝ ██╔══╝   ██║               ██╔═══╝",
        "███████╗ ███████╗  ╚████╔╝  ███████╗ ███████╗          ██████╗",
        "╚══════╝ ╚══════╝   ╚═══╝   ╚══════╝ ╚══════╝          ╚═════╝ ",
        "                                                                    "};

    for (int i = 0; i < 7; ++i)
    {
        gotoxy(30, 8 + i); // Adjust according to the desired position
        std::cout << title[i];
    }

    gotoxy(43, 15);
    std::cout << "[ Press ENTER twice to continue ]";   // Display message to wait for Enter key

    gotoxy(30, 17); 
    std::cout << ">> Principal Objective: Escort and protect the ally fish! <<";   // Display the objective of the level

    std::cin.ignore();  // Clear the input buffer
    std::cin.get();   // Wait for the user to press Enter
    system("cls");  // Clear the console
}

inline void Victorylevel2()   // Function to display the victory message for level 2
{
    system("cls");   // Clear the console
    system("chcp 65001 > nul");  // Set the console code page to UTF-8

    const std::string congrats[6] = {
        " ██████╗ ██████╗ ██╗   █╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗██╗    █████╗ ████████╗██╗ ██████╗ ██╗   █╗███████╗",
        "██╔════╝██╔═══██╗███╗  █║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██║   ██╔══██╗╚══██╔══╝██║██╔═══██╗███╗  █║██╔════╝",
        "██║     ██║   ██║█╔██╗ █║██║  ███╗██████╔╝███████║   ██║   ██║   ██║██║   ███████║   ██║   ██║██║   ██║█╔██╗ █║███████╗",
        "██║     ██║   ██║█║╚██╗█║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██║   ██╔══██║   ██║   ██║██║   ██║█║╚██╗█║╚════██║",
        "╚██████╗╚██████╔╝█║ ╚███║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝█████╗██║  ██║   ██║   ██║╚██████╔╝█║ ╚███║███████║",
        " ╚═════╝ ╚═════╝ ╚╝  ╚══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚╝  ╚══╝╚══════╝",
    };

    for (int i = 0; i < 6; ++i)   // Loop through each line of the victory message
    {
        gotoxy(1, 8 + i);
        std::cout << congrats[i];
    }

    gotoxy(35, 15);   // Position the cursor for the victory message
    std::cout << "You successfully protected and escort the ally fish!✅";   // Display victory message

    gotoxy(45, 17);
    std::cout << "[ Press ENTER to return to menu ]";

    std::cin.clear();
    std::cin.sync();
    std::cin.get();
    system("cls");
}

static void GameOverlevel2(std::string messegeDevouredFish)   // Function to display the game over message for level 2
{
    while (_kbhit())  // Clear the input buffer
        _getch();        // Read and discard any characters in the input buffer
    system("cls");
    system("chcp 65001 > nul");  // Set the console code page to UTF-8

    const std::string text[6] = {
        " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗",
        "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
        "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
        "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
        "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
        " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"};

    for (int i = 0; i < 6; ++i)   // Loop through each line of the game over message
    {
        gotoxy(25, 6 + i);
        std::cout << text[i] << "\n\n"; // Display the game over message
    }
    gotoxy(42, 17);
    std::cout << messegeDevouredFish;

    system("chcp 437 > nul");
    WaitEnterlevel2();
    system("cls");
}

static void InitGamelevel2()  // Function to initialize the game for level 2
{
    InitGameMessagelevel2();  // Display the game message for level 2
    system("cls");
    setColor(15);
    gotoxy(5, 1);
    std::cout << "Principal Objective: Escort the ally fish🐠";   

    level2Submarine = {15, 15, 3, 3}; // Submarine controlled by user

    PaintSubmarine(level2Submarine, 1);  // Paint the submarine in blue
    PaintAllyFish(allySubmarine, level2Submarine);  // Paint the ally fish
    PaintHearts(level2Submarine);  // Paint the hearts representing lives
    // Initialize the submarine's oxygen level and hearts
    level2Fishes[0] = {80, 3};
    level2Fishes[1] = {90, 10};
    level2Fishes[2] = {100, 15};
    level2Fishes[3] = {110, 20};
    level2NumFishes = 4;
}

static void GameLooplevel2()  // Function to run the game loop for level 2
{
    GameLimits();
    bool devouredAlly = false, completedTime = false, stillAlive = true;   // Initialize game state variables
    std::string messageDevouredFish;  // Message to display when the ally fish is devoured or player runs out of lives
    using namespace std::chrono;
    auto startTime = steady_clock::now();

    do
    {
        DeleteAllyFish(allySubmarine); // Delete ally fish before submarine movement
        if (kbhit())
        {
            char key = getch();
            MoveWithAlly(key, level2Submarine);  // Move the submarine based on user input
        }

        // Move ally behind the player
        allySubmarine.x = level2Submarine.x - 3;
        allySubmarine.y = level2Submarine.y - 2;

        // First we paint the Submarine
        PaintSubmarine(level2Submarine, 1);
        PaintAllyFish(allySubmarine, level2Submarine);  // Paint the ally fish behind the submarine

        for (int i = 0; i < level2NumFishes; i++)   // Move each fish in the level
        {
            MoveFish(level2Fishes[i]);
            CollisionFish(level2Fishes[i], level2Submarine);  // Check for collision with the submarine

            // If the ally is touched, it loses
            if ((level2Fishes[i].x >= allySubmarine.x &&
                 level2Fishes[i].x <= allySubmarine.x + 6) &&
                (level2Fishes[i].y == allySubmarine.y))
            {
                devouredAlly = true;
            }
        }

        // Check if 3 minutes have passed
        auto currentTime = steady_clock::now();
        auto elapsed = duration_cast<seconds>(currentTime - startTime).count();  // Calculate elapsed time in seconds
        if (elapsed >= 180)  // 3 minutes
        {
            completedTime = true;
        }

        // Show timer on line 1
        gotoxy(50, 1);
        int remaining = 180 - static_cast<int>(elapsed);    // Calculate remaining time in seconds
        int minutes = remaining / 60;
        int seconds = remaining % 60;
        std::cout << "Time remaining: " << minutes << "min " << (seconds < 10 ? "0" : "") << seconds << "sec     ";  // Display remaining time

        if (level2Submarine.lifes <= 0)   // Check if the submarine is out of lives
        {
            stillAlive = false;
        }

        Sleep(13);

    } while (!devouredAlly && !completedTime && stillAlive);  // Continue the game loop until ally is devoured, time is completed, or player runs out of lives

    if (devouredAlly || !stillAlive)   // If the ally fish is devoured or player runs out of lives
    {
        if (devouredAlly)
            messageDevouredFish = "🐠 [The allied fish was devoured] 🐠";  
        else if (!stillAlive)
            messageDevouredFish = "💀 [You ran out of lives] 💀";

        GameOverlevel2(messageDevouredFish); // Display the game over message
    }
    else if (completedTime)  // If the time is completed
    {
        Victorylevel2();
    }
}

#endif
