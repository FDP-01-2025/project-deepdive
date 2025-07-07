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

static Missiles level3Missiles[MAX_MISSILES];
static int level3MissilesCount;

#define playerMissiles level3Missiles
#define playerMissilesCount level3MissilesCount
#define PLAYER_MISSILE_DAMAGE 10

static int score = 0;

static int availableMissiles = 10;
static const int maxMissilesPerReload = 10;
static bool canShoot = true;
static double reloadTime = 1000;
static clock_t lastShotTime;

static bool reloadPowerActive = false;
static double powerDuration = 5000;
static clock_t powerStartTime;

static BossSubmarine boss;
static bool bossActive = false;
static bool bossDefeated = false;
static clock_t bossAppearTime;
static const double bossAppearDelay = 30000;

// 🟢 NEW FUNCTION: Show boss intro message
static void bossFinalIntroMessage()
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

    while (true)
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

    for (int i = 0; i < 6; ++i)
    {
        gotoxy(30, 3 + i);
        std::cout << historyTitle[i];
    }

    // Narrative story
    gotoxy(20, 11);
    std::cout << "After passing all obstacles, the submarine ventures into unknown waters...";

    gotoxy(20, 13);
    std::cout << "The sea becomes silent. An immense shadow approaches.";

    gotoxy(20, 15);
    std::cout << "The submarine's systems detect a colossal hostile presence.";

    gotoxy(20, 17);
    std::cout << "It is the Mega Alien Ship, armed to the teeth and thirsty for destruction.";

    gotoxy(20, 19);
    std::cout << "You are the last hope to stop it.";

    gotoxy(20, 21);
    std::cout << "Controls: W ↑ ,  S ↓ ,  A ← ,  D →  |  SPACE to shoot";

    gotoxy(43, 23);
    std::cout << "[ Press ENTER to begin the final battle ]";

    while (true)
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

static void GameOverlevel3()
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

static void Victory()
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
        std::cout << "\033[1;32m" << victoryMessage[i] << "\033[0m";
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

static void showState(int score, int availableMissiles, int maxMissiles)
{
    gotoxy(2, 0);
    std::cout << "SCORE: " << score << "        ";

    gotoxy(2, 1);
    std::cout << "MISSILES: " << availableMissiles << "/" << maxMissiles << "       ";
}

// function to save the score

static void activateReloadPower()
{
    reloadPowerActive = true;
    reloadTime = 300;
    powerStartTime = clock();
    availableMissiles = maxMissilesPerReload;
    canShoot = true;
    showState(score, availableMissiles, maxMissilesPerReload);
}

static void updatePower()
{
    if (reloadPowerActive)
    {
        clock_t now = clock();
        if (now - powerStartTime >= powerDuration)
        {
            reloadPowerActive = false;
            reloadTime = 1000;
        }
    }
}

static void clearBossMissiles()
{
    for (int i = 0; i < bossMissilesCount; i++)
    {
        gotoxy(bossMissiles[i].x, bossMissiles[i].y);
        std::cout << "  ";
    }
    bossMissilesCount = 0;
}

static void bossShoot()
{
    if (bossMissilesCount < 10)
    {
        bossMissiles[bossMissilesCount].x = boss.x - 2;
        bossMissiles[bossMissilesCount].y = boss.y + 2;
        bossMissilesCount++;
    }
}

static void moveBossMissiles()
{
    for (int i = 0; i < bossMissilesCount;)
    {
        gotoxy(bossMissiles[i].x, bossMissiles[i].y);
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
static void DetectSubmarineBossCollision(Submarine &sub, BossSubmarine &boss)
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

static void initializeBoss()
{
    boss.x = 100;
    boss.y = 10;
    boss.health = 100;
    boss.isAngry = false;
    boss.fireRate = 50;
    bossActive = true;
    bossDefeated = false;
    DrawBossSubmarine(boss);
    DrawBossHealth(boss);
}

static void DetectPlayerMissileImpact(BossSubmarine &boss)
{
    const int bossWidth = 18;
    const int bossHeight = 4;
    for (int i = 0; i < level3MissilesCount;)
    {
        bool impact =
            level3Missiles[i].x >= boss.x &&
            level3Missiles[i].x <= boss.x + bossWidth &&
            level3Missiles[i].y >= boss.y &&
            level3Missiles[i].y <= boss.y + bossHeight - 1;

        if (impact)
        {
            BossTakeDamage(boss, PLAYER_MISSILE_DAMAGE);
            gotoxy(level3Missiles[i].x, level3Missiles[i].y);
            std::cout << "  ";
            level3Missiles[i] = level3Missiles[level3MissilesCount - 1];
            level3MissilesCount--;
            DrawBossHealth(boss);
            if (boss.health <= 0)
            {
                bossDefeated = true;
                clearBossMissiles();
                BossExplosion(boss);
                score += 100;
                showState(score, availableMissiles, maxMissilesPerReload);
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
    if (!bossActive || bossDefeated)
        return;
    static int moveCounter = 0;
    moveCounter++;
    if (moveCounter % 2 == 0)
    {
        EraseBossSubmarine(boss);
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
        DrawBossSubmarine(boss);
    }
    if (rand() % boss.fireRate == 0)
    {
        bossShoot();
    }
    moveBossMissiles();
    for (int i = 0; i < bossMissilesCount;)
    {
        if ((bossMissiles[i].x >= level3Submarine.x && bossMissiles[i].x <= level3Submarine.x + 12) &&
            (bossMissiles[i].y >= level3Submarine.y && bossMissiles[i].y <= level3Submarine.y + 3))
        {
            if (!invulnerabilityActive)
            {
                level3Submarine.heart--;
                if (level3Submarine.heart > 0)
                {
                    CollisionSubmarine(level3Submarine);
                }
                DestroySubmarine(level3Submarine);
                PaintSubmarine(level3Submarine, chosenSubmarineStylelevel3);
                PaintHearts(level3Submarine);
            }
            gotoxy(bossMissiles[i].x, bossMissiles[i].y);
            std::cout << "  ";
            for (int j = i; j < bossMissilesCount - 1; j++)
                bossMissiles[j] = bossMissiles[j + 1];
            bossMissilesCount--;
        }
        else
            i++;
    }
    // Check collision between submarine and boss
    DetectSubmarineBossCollision(level3Submarine, boss);
    if (!invulnerabilityActive &&
        ((level3Submarine.x + 12 >= boss.x && level3Submarine.x <= boss.x + 18) &&
         (level3Submarine.y + 2 >= boss.y && level3Submarine.y <= boss.y + 3)))
    {
        CollisionSubmarine(level3Submarine);
        PaintHearts(level3Submarine);
    }
}
// 🟢 NEW FUNCTION: Update missile reload
static void updateReload(char key)
{
    if (key == 32 && canShoot && availableMissiles > 0 && level3MissilesCount < MAX_MISSILES)
    {
        level3Missiles[level3MissilesCount].x = level3Submarine.x + 12;
        level3Missiles[level3MissilesCount].y = level3Submarine.y + 2;
        level3MissilesCount++;
        availableMissiles--;
        if (availableMissiles == 0)
        {
            canShoot = false;
            lastShotTime = clock();
        }
        showState(score, availableMissiles, maxMissilesPerReload);
    }
}

void InitGamelevel3()
{
    bossFinalIntroMessage(); // 🟢 NEW FUNCTION: Show boss intro message
    level3Submarine = {5, 15, 3, 3};
    PaintSubmarine(level3Submarine, chosenSubmarineStylelevel3);
    PaintHearts(level3Submarine);
    level3Fishes[0] = {90, 3};
    level3Fishes[1] = {80, 12};
    level3Fishes[2] = {100, 17};
    level3NumFishes = 3;
    level3MissilesCount = 0;
    bossMissilesCount = 0;
    score = 0;
    availableMissiles = maxMissilesPerReload;
    canShoot = true;
    bossActive = false;
    bossDefeated = false;
    bossAppearTime = clock();
    resetItem();
    showState(score, availableMissiles, maxMissilesPerReload);
}

void GameLooplevel3()
{
    char key = 0;
    bool paint = false;
    do
    {
        HideCursor();
        if (kbhit())
        {
            key = getch();
            updateReload(key);
            MoveSubmarine(key, level3Submarine);
        }

        if (!bossActive && !bossDefeated && (clock() - bossAppearTime) >= bossAppearDelay)
        {
            initializeBoss();
        }

        showItem();
        checkItemRespawn();
        if (detectItemCollision(level3Submarine))
        {
            hideItem();
            activateReloadPower();
        }

        showInvulnerableItem();
        checkInvulnerableItemRespawn();
        if (detectInvulnerableItemCollision(level3Submarine))
        {
            hideInvulnerableItem();
            activateInvulnerability();
        }
        updateInvulnerability();

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
            DetectPlayerMissileImpact(boss);
            updateBoss();
        }

        for (int i = 0; i < level3MissilesCount;)
        {
            bool erasedMissil = false;
            for (int j = 0; j < level3NumFishes; j++)
            {
                if ((level3Missiles[i].x == level3Fishes[j].x || level3Missiles[i].x == level3Fishes[j].x + 3 || level3Missiles[i].x == level3Fishes[j].x + 6) &&
                    level3Missiles[i].y == level3Fishes[j].y)
                {
                    gotoxy(level3Missiles[i].x, level3Missiles[i].y);
                    std::cout << "  ";
                    level3Missiles[i] = level3Missiles[level3MissilesCount - 1];
                    level3MissilesCount--;
                    erasedMissil = true;
                    gotoxy(level3Fishes[j].x, level3Fishes[j].y);
                    std::cout << "         ";
                    level3Fishes[j].x = 110;
                    level3Fishes[j].y = rand() % 20 + 3;
                    score += 10;
                    showState(score, availableMissiles, maxMissilesPerReload);
                    break;
                }
            }
            if (!erasedMissil)
                i++;
        }

        for (int i = 0; i < level3NumFishes; i++)
        {
            MoveFish(level3Fishes[i]);
            if (!invulnerabilityActive)
                CollisionFish(level3Fishes[i], level3Submarine);
            else if (CollisionWithInvulnerability(level3Fishes[i], level3Submarine))
                paint = true;
        }
        if (paint)
            PaintSubmarine(level3Submarine, chosenSubmarineStylelevel3);

        updatePower();
        updateInvulnerability();

        Sleep(10);

    } while (level3Submarine.lifes > 0 && !bossDefeated);
  
    if (!bossDefeated)
    {
        GameOverlevel3();
    }
    else
    {
        saveScore(score);
        Victory();
    }
}

#endif