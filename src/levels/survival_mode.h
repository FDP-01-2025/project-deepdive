#ifndef SURVIVAL_MODE_H_INCLUDED
#define SURVIVAL_MODE_H_INCLUDED

#include "../headers/rockets.h"
#include "../headers/game_data.h"
#include "../headers/game_limits.h"
#include "../headers/game_data.h"
#include <conio.h> // It allows the use of the getch() function to detect the keystrokes of each key.
#include <limits>
#include <string>

// --- VARIABLES ---
static const int MAX_ROCKETS = 5; // Maximum number of rockets in survival mode
static Submarine survivalSubmarine;
static Rocket survivalRockets[5];
static int survivalNumRockets;
static int chosenSubmarineStyle = 1;
static std::string captain;

const int BASE_FPS = 60;
const int BASE_FRAME_TIME_MS = 1000 / BASE_FPS; // Base frame time in milliseconds for 60 FPS

struct DifficultySettings  // Structure to hold difficulty settings
{
    int targetFrameTime;  // Target frame time in milliseconds
    float rocketSpeed;  // Speed of the rockets
    int activeRockets;
};

// Calculates difficulty based on time
DifficultySettings UpdateDifficulty(int elapsedSeconds, int totalRockets)
{
    int speed = std::min(elapsedSeconds / 10, 20); // Increases difficulty every 10 seconds. Speed cap at 20.

    int targetFrameTime = BASE_FRAME_TIME_MS - std::min(speed, 8); // Max adjustable FPS
    float rocketSpeed = 0.4f + speed * 0.05f;                      // Increases rocket speed over time (0.4f -> initial speed, 0.5f increase per level)
    int activeRockets = std::min(3 + speed, totalRockets);         // Activates more rockets progressively

    return {targetFrameTime, rocketSpeed, activeRockets};
}
static void WaitEnter()
{
    gotoxy(46, 15);
    std::cout << "[Press ENTER to continue]\n\n";

    while (true)
    {
        int key = _getch();  // Waits for a key press without showing it
        if (key == 13)
            break; // 13 = Enter
        gotoxy(46, 15);   // If a different key was pressed, repeat the message
        std::cout << "[Only press ENTER to continue]\n\n";
    }
}
// Displays the game title and an initial instruction before starting
static void InitGameMessage()
{

    system("cls");// Clear the console screen
    system("chcp 65001 > nul");

    const std::string text[6] = {
        "███████╗██╗   ██╗██████╗ ██╗   ██╗██╗██╗   ██╗ █████╗ ██╗         ███╗   ███╗ ██████╗ ██████╗ ███████╗",
        "██╔════╝██║   ██║██╔══██╗██║   ██║██║██║   ██║██╔══██╗██║         ████╗ ████║██╔═══██╗██╔══██╗██╔════╝",
        "███████╗██║   ██║██████╔╝██║   ██║██║██║   ██║███████║██║         ██╔████╔██║██║   ██║██║  ██║█████╗  ",
        "╚════██║██║   ██║██╔══██╗╚██╗ ██╔╝██║╚██╗ ██╔╝██╔══██║██║         ██║╚██╔╝██║██║   ██║██║  ██║██╔══╝  ",
        "███████║╚██████╔╝██║  ██║ ╚████╔╝ ██║ ╚████╔╝ ██║  ██║███████╗    ██║ ╚═╝ ██║╚██████╔╝██████╔╝███████╗",
        "╚══════╝ ╚═════╝ ╚═╝  ╚═╝  ╚═══╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝    ╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝"};
     // Print each line of the title starting at position (10,6)
    for (int i = 0; i < 6; ++i)
    {
        gotoxy(10, 6 + i);
        std::cout << text[i] << "\n\n";
    }    // Show an instruction line below the title
    gotoxy(35, 17);
    std::cout << ">>Dodge obstacles and survive as long as possible<<\n";
    WaitEnter();
    system("chcp 437 > nul");   // Reset console to default character encoding (code page 437)
}
// Displays the Game Over screen for survival mode, showing how long the player survived
static void GameOverSurvivalMode(int duration)
{      
    while (_kbhit())  // Clear any pending key presses from the buffer
        _getch();

    system("cls");
    int minutes = duration / 60;  // Calculate time survived in minutes and seconds
    int seconds = duration % 60;
    system("chcp 65001 > nul"); // Set console code page to UTF-8 for proper character display

    const std::string text[6] = {
        " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗",
        "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗",
        "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝",
        "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗",
        "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║",
        " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝"};

    for (int i = 0; i < 6; ++i)  // Print each line of the GAME OVER art at position (25, 6+i)
    {
        gotoxy(25, 6 + i);
        std::cout << text[i] << "\n\n";
    }
    system("chcp 437 > nul");  // Restore default character encoding
    gotoxy(45, 17);
    std::cout << ">>Survived time: " << minutes << " min" << " " << seconds << " sec<<" << "\n"; // Display the survival time
    WaitEnter();  // Wait for the user to press Enter before returning to the main menu
}

void Timer(int time)  // Function to display the survival time in seconds
{
    gotoxy(5, 1);
    std::cout << "Time: " << time << " sec.";  // Print the elapsed time at position (5, 1)
}

static void SubmarineType(int style)  // Function to display the submarine type based on the selected style
{
    system("chcp 437 > nul");  // Set console code page to 437 for proper character display

    switch (style) // Switch case to handle different submarine styles
    {
    case 1:  // Style 1: Blue Submarine
        std::cout << "\033[1;34m       " << (char)95 << (char)218 << "\033[0m" << "\n";

        std::cout << "\033[1;34m " << (char)126 << (char)42 << (char)95 << (char)95 << (char)95 << (char)47 << (char)111 << (char)111 << (char)92 << (char)95 << "\033[0m" << "\n";

        std::cout << "\033[1;34m  " << (char)40 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)41 << "\033[0m" << "\n";
        break;
    case 2: // Style 2: Cyan Submarine
        std::cout << "\033[1;36m       " << (char)95 << (char)201 << "\033[0m" << "\n";

        std::cout << "\033[1;36m " << (char)177 << (char)62 << (char)95 << (char)95 << (char)219 << (char)47 << (char)240 << (char)240 << (char)92 << (char)92 << "\033[0m" << "\n";

        std::cout << "\033[1;36m  " << (char)40 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)41 << "\033[0m" << "\n";

        break;
    case 3: // Style 3: Magenta Submarine
        std::cout << "\033[1;35m       " << (char)95 << (char)254 << "\033[0m" << "\n";

        std::cout << "\033[1;35m " << (char)178 << (char)35 << (char)95 << (char)95 << (char)95 << (char)47 << (char)216 << (char)216 << (char)92 << (char)45 << "\033[0m" << "\n";

        std::cout << "\033[1;35m  " << (char)40 << (char)61 << (char)95 << (char)95 << (char)95 << (char)95 << (char)95 << (char)61 << (char)41 << "\033[0m" << "\n";
        break;
    case 4: // Style 4: Red Submarine
        std::cout << "\033[1;34m       " << (char)95 << (char)209 << "\033[0m" << "\n";

        std::cout << "\033[1;34m " << (char)177 << (char)62 << (char)95 << (char)95 << (char)45 << (char)47 << (char)248 << (char)248 << (char)92 << (char)45 << "\033[0m" << "\n";

        std::cout << "\033[1;34m  " << (char)40 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)223 << (char)41 << "\033[0m" << "\n";
        break;
    default:
        std::cout << "Error, invalid option\n";
        break;
    }
    system("chcp 65001 > nul");
}

static void Player()  // Function to select a player character from the database
{
    int count = 1, option;
    std::string line, selectedCaptain;
    std::ifstream file("database/characters.txt");  // Open the character file

    system("cls");
    system("chcp 65001 > nul");

    if (!file.is_open())
    {
        std::cout << "⚠️ Error: Could not open the character file.\n";  // If the file cannot be opened, display an error message
        WaitEnter();
        return;
    }

    // Show characters
    while (getline(file, line))  // Read each line from the file
    {
        int style = ((count - 1) % 6) + 1;
        // Display the character information with formatting
        std::cout << "\033[1;37m[🔔] Tactical Channel -- ID " << count << "\033[0m\n";      
        std::cout << "\033[1;37m--------------------------------------------\033[0m\n"; 
        std::cout << "\033[1;37m👤 Captain Record: " << line << "\033[0m\n";
        std::cout << "\033[1;37m🛠️ Assigned Submarine type-" << style << ":\033[0m\n";

        SubmarineType(style);  // Display the submarine type based on the style
       // Display the submarine style
        std::cout << "\033[1;37m--------------------------------------------\033[0m\n\n";
        count++;
    }
    file.close();    // Close the file after reading all characters

    // Request option
    do
    {    // Prompt the user to select a character
        std::cout << "🔱 Choose your character (1 to " << count - 1 << "): ";
        std::cin >> option;

        if (std::cin.fail() || option < 1 || option >= count)  // Validate user input
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "❌ Invalid selection. Please try again.\n";
        }
        else  
        {
            break;
        }
    } while (true);

    // Reopen the file to get the selected captain
    file.open("database/characters.txt");
    if (!file.is_open())
    {
        std::cout << "⚠️ Error: Could not reopen the file.\n";  // If the file cannot be reopened, display an error message
        WaitEnter();
        return;
    }

    count = 1;
    while (getline(file, line))  // Read each line again to find the selected captain
    {
        if (count == option)  // If the current line matches the selected option
        {
            selectedCaptain = line;// Set the selected captain
            break;
        }
        count++;
    }
    file.close(); // Close the file after reading the selected captain

    // Confirm selection
    if (selectedCaptain.empty())
    {
        std::cout << "❌ Selected captain not found.\n";  // If the selected captain is not found, display an error message
    }
    else
    {
        std::cout << "✅ Assigned captain: " << selectedCaptain << "\n";  // Confirm the selected captain
        captain = selectedCaptain;
        chosenSubmarineStyle = ((option - 1) % 4) + 1;  
    }

    system("pause");
    system("chcp 437 > nul");
    system("cls");
}

static void InitGameSurvivalMode() // Initializes the game for survival mode
{
    InitGameMessage();  // Display the game title and instructions
    Player();
    survivalSubmarine = {5, 15, 3, 1};
    PaintSubmarine(survivalSubmarine, chosenSubmarineStyle);  // Paint the submarine with the selected style
    PaintHearts(survivalSubmarine);

    survivalRockets[0] = {102, 3};
    survivalRockets[1] = {104, 20};
    survivalRockets[2] = {106, 15};
    survivalRockets[3] = {108, 9};
    survivalRockets[4] = {110, 6};
    survivalNumRockets = 5;
}

static void GameLoopSurvivalMode()  // Main game loop for survival mode
{
    GameLimits();

    // Save the current time when the game starts (start mark)
    auto startTime = std::chrono::high_resolution_clock::now();
    // Save the time of the "last frame update". Initially, it's the same as the start time
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    auto now = startTime;
    while (survivalSubmarine.lifes > 0)
    {
        // Get the current time at this moment in the loop
        now = std::chrono::high_resolution_clock::now();

        // Calculate the time elapsed since the last frame, in milliseconds
        // This allows adjusting movements and animations based on the real time between frames
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();

        // Update lastFrameTime for the next iteration of the loop
        lastFrameTime = now;

        // Calculate the total time elapsed since the game started (in seconds)
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

        // Update difficulty settings based on elapsed time and active rocket count
        auto settings = UpdateDifficulty(elapsed, survivalNumRockets);

        // Print the timer
        Timer(elapsed);

        if (kbhit())
        {
            char key = getch();
            MoveSubmarine(key, survivalSubmarine);  // Move the submarine based on user input
        }

        for (int i = 0; i < settings.activeRockets; i++)  // Loop through the active rockets
        {
            MoveRocket(survivalRockets[i], settings.rocketSpeed);
            CollisionRocket(survivalRockets[i], survivalSubmarine);
        }

        // FPS CONTROL:
        auto frameEndTime = std::chrono::high_resolution_clock::now();  // Get the time at the end of the frame
        auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - now).count();  // Calculate the duration of the frame in milliseconds

        if (frameDuration < settings.targetFrameTime)  // If the frame took less time than the target frame time
        {
            Sleep(settings.targetFrameTime - frameDuration);
        }

        if (survivalSubmarine.lifes < 0)
        {
            auto now = std::chrono::high_resolution_clock::now();
        }
    }

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

    SaveGameTimeToFile(duration, captain);  // Save the survival time to the file

    GameOverSurvivalMode(duration);  // Display the game over screen with the survival time
}

#endif
