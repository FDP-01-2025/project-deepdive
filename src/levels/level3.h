#ifndef LEVEL3_H
#define LEVEL3_H
#define MAX_MISSILES 100

// --- INCLUDES ---
#include "../headers/position.h"
#include "../headers/hide_cursor.h"
#include "../headers/submarine.h"
#include "../headers/missiles.h"
#include "../headers/fish.h"
#include "../headers/power_item.h"
#include "../headers/invulnerability.h"
#include "../headers/submarine_boss.h"
#include "../headers/game_data.h"

#include <conio.h>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>

// --- variables ---
static Submarine level3Submarine;
static Fish level3Fishes[3];
static int level3NumFishes;
static int chosenSubmarineStylelevel3 = 1;
// --- MISSILES ---
static Missiles level3Missiles[MAX_MISSILES];
static int level3MissilesCount;
// --- POWER-UP ITEM ---
#define playerMissiles level3Missiles
#define playerMissilesCount level3MissilesCount
#define PLAYER_MISSILE_DAMAGE 10
// --- VARIABLES ---
static int score = 0;
// --- TIME ---
static int availableMissiles = 10;
static const int maxMissilesPerReload = 10;
static bool canShoot = true;
static double reloadTime = 1000;
static clock_t lastShotTime;
// --- RELOAD POWER-UP ---
static bool reloadPowerActive = false;
static double powerDuration = 5000;
static clock_t powerStartTime;
// --- INVULNERABILITY POWER-UP ---
static BossSubmarine boss;
static bool bossActive = false;
static bool bossDefeated = false;
static clock_t bossAppearTime;
static const double bossAppearDelay = 30000;

// 🟢 NEW FUNCTION: Show boss intro message
static void bossFinalIntroMessage()        // Function to show the boss intro message
{
    system("cls");
    system("chcp 65001 > nul");

    const std::string title[] = {
        "███████╗██╗███╗   ██╗ █████╗ ██║            ███████╗   ████╗  ██████╗ ██████╗ ",
        "██╔════╝██║████╗  ██║██╔══██╗██║            ██╔═══██╗ ██╔═██╗ ██╔═══╝ ██╔═══╝ ",
        "█████╗  ██║██╔██╗ ██║███████║██║            ███████╔╝ ██║ ██║ ╚█████╗ ╚█████╗ ",
        "██╔══╝  ██║██║╚██╗██║██╔══██║██║            ██╔═══██╗ ██║ ██║ ╚═══██╗ ╚═══██╗ ",
        "██║     ██║██║ ╚████║██║  ██║███████╗       ███████╔╝ ╚████╔╝ █████╔╝ █████╔╝ ",
        "╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝        ╚═════╝   ╚═══╝  ╚════╝  ╚═══╝    ",
    };

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(25, 6 + i);
        std::cout << title[i];
    }

    gotoxy(43, 15);
    std::cout << "[ Press ENTER to face the Final Boss ]";

    while (true)  // Wait for user to press ENTER
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 13)
                break;
        }
    }

    // 🟡 Show history with title
    system("cls");

    const std::string historyTitle[] = {
        "██╗  ██╗██╗ ███████╗████████╗ ██████╗ ██████╗ ██╗   ██╗",
        "██║  ██║██║ ██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝",
        "███████║██║ ███████╗   ██║   ██║   ██║██████╔╝ ╚████╔╝ ",
        "██╔══██║██║ ╚════██║   ██║   ██║   ██║██╔══██╗  ╚██╔╝  ",
        "██║  ██║██║ ███████║   ██║   ╚██████╔╝██   ██║   ██║   ",
        "╚═╝  ╚═╝╚═╝ ╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   "};

    for (int i = 0; i < 6; ++i)   // Show history with title
    {
        gotoxy(30, 3 + i);
        std::cout << historyTitle[i];
    }

    // Narrative story
    gotoxy(20, 11);
    std::cout << "After passing all obstacles, the submarine ventures into unknown waters...";  // Narrative story

    gotoxy(20, 13);
    std::cout << "The sea becomes silent. An immense shadow approaches.";

    gotoxy(20, 15);
    std::cout << "The submarine's systems detect a colossal hostile presence.";

    gotoxy(20, 17);
    std::cout << "It is the Mega Alien Ship, armed to the teeth and thirsty for destruction.";

    gotoxy(20, 19);
    std::cout << "You are the last hope to stop it.";

    gotoxy(20, 21); 
    std::cout << "Controls: W ↑ ,  S ↓ ,  A ← ,  D →  |  SPACE to shoot";  // Controls message

    gotoxy(43, 23);
    std::cout << "[ Press ENTER to begin the final battle ]";

    while (true)  // Wait for user to press ENTER
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 13)
                break;
        }
    }

    system("cls");
}

static void GameOverlevel3()  // Function to display the game over message for level 3
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

    gotoxy(45, 13);
    std::cout << "[Press ENTER twice to continue]" << "\n\n";

    while (true)
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 13)
                break;
        }
    }
}

static void Victory()  // Function to display the victory message for level 3
{
    system("chcp 65001 > nul");
    const std::string victoryMessage[6] = {

        "██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗   ██╗",
        "██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝",
        "██║   ██║██║██║        ██║   ██║   ██║██████╔╝ ╚████╔╝ ",
        "╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗  ╚██╔╝  ",
        " ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║   ██║   ",
        "  ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ",
    };
    system("cls");
    for (int i = 0; i < 6; ++i)
    {
        gotoxy(35, 6 + i);
        std::cout << "\033[1;32m" << victoryMessage[i] << "\033[0m";  // Display victory message in green
    }
    system("chcp 437 > nul");

    gotoxy(45, 17);
    std::cout << "\033[1;32m[ Press ENTER to continue ]\033[0m";

    while (true)
    {
        if (kbhit() && getch() == 13)
            break;
    }
} 
  
static void showState(int score, int availableMissiles, int maxMissiles)  // Function to display the score and available missiles
{
    gotoxy(2, 0);
    std::cout << "SCORE: " << score << "        ";  // Display score

    gotoxy(2, 1);
    std::cout << "MISSILES: " << availableMissiles << "/" << maxMissiles << "       ";    // Display available missiles
}

// function to save the score

static void activateReloadPower()  // Function to activate the reload power-up
{
    reloadPowerActive = true;  // Set the reload power-up state to active
    reloadTime = 300;
    powerStartTime = clock();
    availableMissiles = maxMissilesPerReload;  // Reset available missiles to max after power-up activation
    canShoot = true;
    showState(score, availableMissiles, maxMissilesPerReload);
}
 
static void updatePower()  // Function to update the reload power-up state
{
    if (reloadPowerActive)
    {
        clock_t now = clock();  // Get the current time
        if (now - powerStartTime >= powerDuration)  // Check if power-up duration has expired
        {
            reloadPowerActive = false;  // Set the reload power-up state to inactive
            reloadTime = 1000;
        }
    }
}

static void clearBossMissiles()  // Function to clear boss missiles from the screen
{
    for (int i = 0; i < bossMissilesCount; i++) // Loop through all boss missiles
    {
        gotoxy(bossMissiles[i].x, bossMissiles[i].y); // Move the cursor to the missile position
        std::cout << "  ";  // Clear the missile from the screen
    }
    bossMissilesCount = 0;
}

static void bossShoot()  // Function to make the boss submarine shoot missiles
{
    if (bossMissilesCount < 10) // Check if the boss can shoot more missiles
    {
        bossMissiles[bossMissilesCount].x = boss.x - 2;
        bossMissiles[bossMissilesCount].y = boss.y + 2;
        bossMissilesCount++;
    }
}

static void moveBossMissiles()  // Function to move the boss missiles towards the player submarine
{
    for (int i = 0; i < bossMissilesCount;)  // Loop through all boss missiles
    {
        gotoxy(bossMissiles[i].x, bossMissiles[i].y);  // Move the cursor to the missile position
        std::cout << "  ";
        bossMissiles[i].x -= 2;
        if (bossMissiles[i].x > 2)
        {
            gotoxy(bossMissiles[i].x, bossMissiles[i].y);
            std::cout << "\033[1;31m<<\033[0m";
            i++;
        }
        else
        {
            for (int j = i; j < bossMissilesCount - 1; j++)
            {
                bossMissiles[j] = bossMissiles[j + 1];
            }
            bossMissilesCount--;
        }
    }
}
static void DetectSubmarineBossCollision(Submarine &sub, BossSubmarine &boss)// Function to detect collision between the submarine and the boss submarine
{
    // Check if the submarine and boss areas overlap
    if ((sub.x + 12 >= boss.x && sub.x <= boss.x + 18) && // width
        (sub.y + 2 >= boss.y && sub.y <= boss.y + 3))     // height
    {
        // If they collide, submarine dies instantly
        sub.heart = 0;
        sub.lifes = 0;
    }
}

static void initializeBoss() // Function to initialize the boss submarine
{
    boss.x = 100;    // Set initial x position of the boss submarine
    boss.y = 10;
    boss.health = 100;
    boss.isAngry = false;
    boss.fireRate = 50;  // Set the fire rate of the boss submarine
    bossActive = true;
    bossDefeated = false;
    DrawBossSubmarine(boss);
    DrawBossHealth(boss);  // Draw the boss submarine and its health bar
}

static void DetectPlayerMissileImpact(BossSubmarine &boss) // Function to detect impact of player missiles on the boss submarine
{
    const int bossWidth = 18;  // Width of the boss submarine
    const int bossHeight = 4;
    for (int i = 0; i < level3MissilesCount;)
    {
        bool impact =
            level3Missiles[i].x >= boss.x &&
            level3Missiles[i].x <= boss.x + bossWidth &&
            level3Missiles[i].y >= boss.y &&
            level3Missiles[i].y <= boss.y + bossHeight - 1;
            // Check if the missile is within the boss submarine's area
        if (impact)
        {
            BossTakeDamage(boss, PLAYER_MISSILE_DAMAGE);
            gotoxy(level3Missiles[i].x, level3Missiles[i].y);
            std::cout << "  ";
            level3Missiles[i] = level3Missiles[level3MissilesCount - 1];  // Move the last missile to the current position
            level3MissilesCount--;
            DrawBossHealth(boss);
            if (boss.health <= 0)
            {        /// If the boss submarine's health is zero, it is defeated
                bossDefeated = true;
                clearBossMissiles();
                BossExplosion(boss);
                score += 100;
                showState(score, availableMissiles, maxMissilesPerReload);  // Update the score display
                break;
            }
        }
        else
            i++;
    }
}
// 🟢 NEW FUNCTION: Update boss submarine
static void updateBoss()
{
    if (!bossActive || bossDefeated) // If the boss is not active or already defeated, return
        return;
    static int moveCounter = 0;
    moveCounter++;
    if (moveCounter % 2 == 0)
    {
        EraseBossSubmarine(boss);  // Erase the boss submarine from the screen
        static bool movingDown = true;
        if (movingDown)
        {
            boss.y += (rand() % 2);
            if (boss.y >= 20)
                movingDown = false;
        }
        else
        {
            boss.y -= (rand() % 2);
            if (boss.y <= 3)
                movingDown = true;
        }
        DrawBossSubmarine(boss);  // Draw the boss submarine at the new position
    }
    if (rand() % boss.fireRate == 0)  // Randomly decide when the boss will shoot
    {
        bossShoot();
    }
    moveBossMissiles();
    for (int i = 0; i < bossMissilesCount;)  // Check for collisions between boss missiles and the player submarine
    {
        if ((bossMissiles[i].x >= level3Submarine.x && bossMissiles[i].x <= level3Submarine.x + 12) &&
            (bossMissiles[i].y >= level3Submarine.y && bossMissiles[i].y <= level3Submarine.y + 3))
        {
            if (!invulnerabilityActive)   // If the player submarine is not invulnerable
            {
                level3Submarine.heart--;
                if (level3Submarine.heart > 0)
                {
                    CollisionSubmarine(level3Submarine);  // Handle collision with the submarine
                }
                DestroySubmarine(level3Submarine);  // Destroy the submarine
                PaintSubmarine(level3Submarine, chosenSubmarineStylelevel3);  // Repaint the submarine
                PaintHearts(level3Submarine); // Repaint the hearts
            }
            gotoxy(bossMissiles[i].x, bossMissiles[i].y); // Move the cursor to the missile position
            std::cout << "  ";
            for (int j = i; j < bossMissilesCount - 1; j++) // Shift the remaining missiles to fill the gap
                bossMissiles[j] = bossMissiles[j + 1];  // Move the last missile to the current position
            bossMissilesCount--;
        }
        else
            i++;
    }
    // Check collision between submarine and boss
    DetectSubmarineBossCollision(level3Submarine, boss);
    if (!invulnerabilityActive &&
        ((level3Submarine.x + 12 >= boss.x && level3Submarine.x <= boss.x + 18) &&  // Check if the submarine's area overlaps with the boss's area
         (level3Submarine.y + 2 >= boss.y && level3Submarine.y <= boss.y + 3)))
    {
        CollisionSubmarine(level3Submarine);  // Handle collision with the submarine
        PaintHearts(level3Submarine);  // Repaint the hearts
    }
}
// 🟢 NEW FUNCTION: Update missile reload
static void updateReload(char key)  // Function to update missile reload based on user input
{
    if (key == 32 && canShoot && availableMissiles > 0 && level3MissilesCount < MAX_MISSILES)    
    {
        level3Missiles[level3MissilesCount].x = level3Submarine.x + 12; // Set the missile's x position to the submarine's right side
        level3Missiles[level3MissilesCount].y = level3Submarine.y + 2;  // Set the missile's y position to the submarine's middle
        level3MissilesCount++;
        availableMissiles--;
        if (availableMissiles == 0)
        {
            canShoot = false;
            lastShotTime = clock();
        }
        showState(score, availableMissiles, maxMissilesPerReload);  // Update the score display
    }
}

void InitGamelevel3()  // Function to initialize the game for level 3
{
    bossFinalIntroMessage(); // 🟢 NEW FUNCTION: Show boss intro message
    level3Submarine = {5, 15, 3, 3};
    PaintSubmarine(level3Submarine, chosenSubmarineStylelevel3);  // Paint the submarine with the chosen style
    PaintHearts(level3Submarine);  // Paint the hearts representing the submarine's lives
    level3Fishes[0] = {90, 3};
    level3Fishes[1] = {80, 12};
    level3Fishes[2] = {100, 17};
    level3NumFishes = 3;
    level3MissilesCount = 0;
    bossMissilesCount = 0;
    score = 0;
    availableMissiles = maxMissilesPerReload;  // Reset available missiles to the maximum per reload
    canShoot = true;
    bossActive = false;
    bossDefeated = false;
    bossAppearTime = clock();  // Initialize the boss appearance time
    resetItem();
    showState(score, availableMissiles, maxMissilesPerReload);  // Show the initial state of the game
}

void GameLooplevel3()  // Function to run the game loop for level 3
{
    char key = 0;
    bool paint = false;
    do
    {
        HideCursor();  // Hide the cursor for a cleaner display
        if (kbhit())
        {
            key = getch();
            updateReload(key);
            MoveSubmarine(key, level3Submarine);
        }

        if (!bossActive && !bossDefeated && (clock() - bossAppearTime) >= bossAppearDelay)  // Check if the boss should appear
        {
            initializeBoss();  // Initialize the boss submarine
        }

        showItem();
        checkItemRespawn();
        if (detectItemCollision(level3Submarine)) 
        {
            hideItem();
            activateReloadPower(); // Activate the reload power-up
        }

        showInvulnerableItem(); // Show the invulnerability item on the screen
        checkInvulnerableItemRespawn();
        if (detectInvulnerableItemCollision(level3Submarine))   // Check if the submarine has collided with the invulnerability item
        {
            hideInvulnerableItem();
            activateInvulnerability();
        }
        updateInvulnerability(); // Update the invulnerability state

        for (int i = 0; i < level3MissilesCount;)
        {
            MoveMissil(level3Missiles[i]);
            if (level3Missiles[i].x >= 115)
            {
                gotoxy(level3Missiles[i].x, level3Missiles[i].y);
                std::cout << "  ";
                level3Missiles[i] = level3Missiles[level3MissilesCount - 1];
                level3MissilesCount--;
            }
            else
                i++;
        }

        if (bossActive && !bossDefeated)
        {
            DetectPlayerMissileImpact(boss);  // Check for missile impact on the boss
            updateBoss();  // Update the boss submarine
        }

        for (int i = 0; i < level3MissilesCount;)  // Loop through all missiles
        {
            bool erasedMissil = false;  // Flag to check if a missile was erased
            for (int j = 0; j < level3NumFishes; j++)
            {
                if ((level3Missiles[i].x == level3Fishes[j].x || level3Missiles[i].x == level3Fishes[j].x + 3 || level3Missiles[i].x == level3Fishes[j].x + 6) &&
                    level3Missiles[i].y == level3Fishes[j].y)
                {
                    gotoxy(level3Missiles[i].x, level3Missiles[i].y);
                    std::cout << "  ";
                    level3Missiles[i] = level3Missiles[level3MissilesCount - 1];  // Move the last missile to the current position
                    level3MissilesCount--;   
                    erasedMissil = true;
                    gotoxy(level3Fishes[j].x, level3Fishes[j].y);  // Move the cursor to the fish position
                    std::cout << "         ";
                    level3Fishes[j].x = 110;
                    level3Fishes[j].y = rand() % 20 + 3;
                    score += 10;
                    showState(score, availableMissiles, maxMissilesPerReload);  // Update the score display
                    break;
                }
            }
            if (!erasedMissil)  // If no fish was hit by the missile
                i++;
        }

        for (int i = 0; i < level3NumFishes; i++)  // Loop through all fishes in the level
        {
            MoveFish(level3Fishes[i]);
            if (!invulnerabilityActive)
                CollisionFish(level3Fishes[i], level3Submarine);
            else if (CollisionWithInvulnerability(level3Fishes[i], level3Submarine))  // Check if the fish collides with the submarine while invulnerable
                paint = true;
        }
        if (paint)
            PaintSubmarine(level3Submarine, chosenSubmarineStylelevel3);  // Repaint the submarine if it was invulnerable

        updatePower();  // Update the reload power-up state
        updateInvulnerability();  // Update the invulnerability state

        Sleep(10);

    } while (level3Submarine.lifes > 0 && !bossDefeated); // Continue the game loop until the submarine runs out of lives or the boss is defeated
  
    if (!bossDefeated)  
    {
        GameOverlevel3();  // Display the game over message
    }
    else
    {
        saveScore(score);  // Save the score to the file
        Victory();  // Display the victory message
    }
}

#endif