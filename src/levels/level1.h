#ifndef LEVEL1_H
#define LEVEL1_H
#include "../headers/fish.h"
#include "../headers/pieces.h"
#include "../headers/game_limits.h"
#include <conio.h> // It allows the use of the getch() function to detect the keystrokes of each key.
/*
OBJECTIVE OF LEVEL 2:
-COLLECT THE PIECES TO FILL THE OXYGEN BAR AND UNLOCK OTHER LEVELS

*/
static Submarine level1Submarine;
static Fish level1Fishes[4];
static int level1Numfishes;
static Pieces level1Pieces[1]; // Number of Pieces
static int chosenSubmarineStylelevel1 = 1;
static int level1NumPieces;
static int sleepTime = 10; // Initial waiting time
// Function to wait for the player to press Enter before starting the game
static void WaitEnterlevel1()
{
    gotoxy(46, 15);
    std::cout << "[Press ENTER to continue]\n\n";  // Display message to wait for Enter key

    while (true)  // Loop until Enter is pressed
    {
        int key = _getch();
        if (key == 13)
            break; // 13 = Enter
        gotoxy(46, 15);
        std::cout << "[Only press ENTER to continue]\n\n";   // Display message if any other key is pressed
    } 
}
static void InitGameMessagelevel1()   // Initialize the game message for level 1
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string title[7] = {
        "██╗      ███████╗ ██╗   ██╗ ███████╗ ██╗                ██╗",
        "██║      ██╔════╝ ██║   ██║ ██╔════╝ ██║               ███║",
        "██║      █████╗   ██║   ██║ █████╗   ██║               ╚██║",
        "██║      ██╔══╝   ╚██╗ ██╔╝ ██╔══╝   ██║                ██║",
        "███████╗ ███████╗  ╚████╔╝  ███████╗ ███████╗           ██║",
        "╚══════╝ ╚══════╝   ╚═══╝   ╚══════╝ ╚══════╝           ╚═╝ ",
        "                                                                    "};

    for (int i = 0; i < 7; ++i)
    {
        gotoxy(30, 8 + i); // Adjust according to the desired position
        std::cout << title[i];
    }

    gotoxy(43, 15);
    std::cout << "[ Press ENTER twice to continue ]";    // Display message to wait for Enter key

    gotoxy(30, 17);
    std::cout << ">> OBJECTIVE: Collect the pieces to refill the oxygen bar❗ <<";   /// Display the objective of the level

    std::cin.ignore();
    std::cin.get();
    system("cls");
}

inline void Victorylevel1()   // Function to display the victory message for level 1
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string congrats[6] = {
        " ██████╗ ██████╗ ██╗   █╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗██╗     █████╗ ████████╗██╗ ██████╗ ██╗   █╗██████╗",
        "██╔════╝██╔═══██╗███╗  █║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██║    ██╔══██╗╚══██╔══╝██║██╔═══██╗███╗  █║██╔═══╝",
        "██║     ██║   ██║█╔██╗ █║██║  ███╗██████╔╝███████║   ██║   ██║   ██║██║    ███████║   ██║   ██║██║   ██║█╔██╗ █║██████╗",
        "██║     ██║   ██║█║╚██╗█║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██║    ██╔══██║   ██║   ██║██║   ██║█║╚██╗█║╚═══██║",
        "╚██████╗╚██████╔╝█║ ╚███║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝██████╗██║  ██║   ██║   ██║╚██████╔╝█║ ╚███║██████║",
        " ╚═════╝ ╚═════╝ ╚╝  ╚══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚╝  ╚══╝ ╚════╝",
    };

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(1, 8 + i);
        std::cout << congrats[i];
    }

    gotoxy(43, 15);
    std::cout << "You successfully filled the oxygen bar!✅";

    gotoxy(45, 17);
    std::cout << "[ Press ENTER to return to menu ]";

    std::cin.ignore();
    std::cin.get();
    system("cls");
}

static void GameOverlevel1()   /// Function to display the game over message for level 1
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string text[6] = {
        " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗",
        "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
        "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
        "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
        "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
        " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"};

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(25, 6 + i);
        std::cout << text[i] << "\n\n";
    }
    system("chcp 437 > nul");
    WaitEnterlevel1();
    system("cls");
}

static void InitGamelevel1()  /// Function to initialize the game for level 1
{
    InitGameMessagelevel1();  // Display the game message for level 1
    WaitEnterlevel1();        // Wait for the player to press Enter
    system("cls");
    setColor(15);
    gotoxy(5, 1);
    std::cout << "Principal Objective: Refil the oxygen❗";   // Display the main objective of the level
    level1Submarine = {5, 15, 1, 3};          // Initialize the submarine with position (5, 15), 1 heart, 3 lives, and oxygen level 0
    PaintSubmarine(level1Submarine, chosenSubmarineStylelevel1);
    PaintHearts(level1Submarine);
    PaintOxygen(level1Submarine);
// Initialize the submarine's oxygen level and hearts
    level1Fishes[0] = {80, 3};
    level1Fishes[1] = {90, 10};
    level1Fishes[2] = {100, 15};
    level1Fishes[3] = {110, 20};
    level1Numfishes = 4;

    level1Pieces[0] = {85, 5};
    level1NumPieces = 1;
}

static void GameLooplevel1()   /// Function to run the game loop for level 1
{
    bool fullOxygen = false, collisionPieces = false, isAlive = true;   // Initialize game state variables
    int countCollision = 0;
    GameLimits();       // Draw the game limits on the screen
    do
    {
        // to ensure that the new deltaTime is measured correctly in the next round
        if (kbhit())
        {
            char key = getch();
            MoveSubmarine(key, level1Submarine);
        }

        for (int i = 0; i < level1Numfishes; i++)   // Move each fish in the level
        {
            MoveFish(level1Fishes[i]);  // Move the fish
            CollisionFish(level1Fishes[i], level1Submarine);   // Check for collision with the submarine
        }
        for (int i = 0; i < level1NumPieces; i++)
        {
            Movepieces(level1Pieces[i]);

            if (Collition(level1Pieces[i], level1Submarine))
            {
                CollisionPieces(level1Pieces[i], level1Submarine); // Impact effect
                collisionPieces = true;
            }
        }
        // Increase oxygen

        if (collisionPieces)    // If a piece is collected
        {
            level1Submarine.oxygen++;   // Increase the oxygen level by 1
            countCollision++;
            PaintOxygen(level1Submarine);  // Update the oxygen bar display
            if (countCollision % 5 == 0 && sleepTime > 1)  // Every 5 pieces collected, decrease the sleep time
                sleepTime--;
        }

        if (level1Submarine.oxygen >= 30)  // Check if the oxygen level is full
        {
            fullOxygen = true;  // Set the flag to indicate full oxygen
        }

        collisionPieces = false;

        if (level1Submarine.lifes <= 0)  // Check if the submarine is out of lives
        {
            isAlive = false;
        }

        Sleep(sleepTime);

    } while (!fullOxygen && isAlive);

    if (fullOxygen)
    {
        Victorylevel1();
    }
    else
    {
        GameOverlevel1();
    }
}

#endif
