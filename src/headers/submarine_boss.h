#ifndef BOSS_SUBMARINE_H_INCLUDED
#define BOSS_SUBMARINE_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "position.h"
#include "missiles.h"
#include "submarine.h"

typedef struct {
    int x, y;
    int health;
    bool isAngry;
    int fireRate;
    int moveRate;
    clock_t lastShot;
} BossSubmarine;

static Missiles bossMissiles[10];
static int bossMissilesCount = 0;

void InitializeBoss(BossSubmarine &boss) {
    boss.x = 100;
    boss.y = 10;
    boss.health = 100;
    boss.isAngry = false;
    boss.fireRate = 20;
    boss.moveRate = 2;
    boss.lastShot = clock();
}

void DrawBossHealth(BossSubmarine &boss) {
    gotoxy(40, 1);
    std::cout << "\033[1;31mBOSS: [";

    int healthLeft = (boss.health * 20) / 100;
    for (int i = 0; i < healthLeft; i++) {
        std::cout << "|";
    }
    for (int i = healthLeft; i < 20; i++) {
        std::cout << " ";
    }
    std::cout << "] " << boss.health << "/100\033[0m";
}

void DrawBossSubmarine(BossSubmarine &boss) {
    gotoxy(boss.x, boss.y);
    std::cout << "\033[1;31m    .--.___.--.    \033[0m";
    gotoxy(boss.x, boss.y + 1);
    std::cout << "\033[1;31m   /===(====)===\\  \033[0m";
    gotoxy(boss.x, boss.y + 2);
    std::cout << "\033[1;31m   \\============/  \033[0m";
    gotoxy(boss.x, boss.y + 3);
    std::cout << "\033[1;31m    '--'____'--'   \033[0m";

    DrawBossHealth(boss);
}

void EraseBossSubmarine(BossSubmarine &boss) {
    for (int i = 0; i < 4; i++) {
        gotoxy(boss.x, boss.y + i);
        std::cout << "                     ";
    }
    gotoxy(50, 1);
    std::cout << "                                             ";
}

void MoveBoss(BossSubmarine &boss) {
    static int moveCounter = 0;
    moveCounter++;

    if (moveCounter % boss.moveRate == 0) {
        EraseBossSubmarine(boss);

        static bool movingDown = true;
        if (movingDown) {
            boss.y += 1;
            if (boss.y >= 20) movingDown = false;
        } else {
            boss.y -= 1;
            if (boss.y <= 3) movingDown = true;
        }

        DrawBossSubmarine(boss);
    }
}

void BossShoot(BossSubmarine &boss) {
    clock_t now = clock();
    int timeBetweenShots = boss.isAngry ? 200 : 400;

    if ((now - boss.lastShot) >= timeBetweenShots && bossMissilesCount < 10) {
        int shotsCount = boss.isAngry ? (rand() % 2 + 2) : 1;

        for (int i = 0; i < shotsCount && bossMissilesCount < 10; i++) {
            bossMissiles[bossMissilesCount].x = boss.x - 2;
            bossMissiles[bossMissilesCount].y = boss.y + (rand() % 4);
            bossMissilesCount++;
        }

        boss.lastShot = now;
    }
}

void MoveBossMissiles() {
    for (int i = 0; i < bossMissilesCount;) {
        gotoxy(bossMissiles[i].x, bossMissiles[i].y);
        std::cout << "  ";

        bossMissiles[i].x -= 2;

        if (bossMissiles[i].x > 2) {
            gotoxy(bossMissiles[i].x, bossMissiles[i].y);
            std::cout << "\033[1;31m<<\033[0m";
            i++;
        } else {
            for (int j = i; j < bossMissilesCount - 1; j++) {
                bossMissiles[j] = bossMissiles[j + 1];
            }
            bossMissilesCount--;
        }
    }
}

void ClearBossMissiles() {
    for (int i = 0; i < bossMissilesCount; i++) {
        gotoxy(bossMissiles[i].x, bossMissiles[i].y);
        std::cout << "  ";
    }
    bossMissilesCount = 0;
}

void BossTakeDamage(BossSubmarine &boss, int damage) {
    boss.health -= damage;
    if (boss.health < 0) boss.health = 0;

    if (boss.health < 30 && !boss.isAngry) {
        boss.isAngry = true;
        boss.fireRate = 10;
        gotoxy(boss.x, boss.y + 4);
        std::cout << "\033[1;91mANGRY MODE!\033[0m";
    }

    DrawBossHealth(boss);
}

void BossExplosion(BossSubmarine &boss) {
    for (int frame = 0; frame < 3; frame++) {
        EraseBossSubmarine(boss);

        gotoxy(boss.x - 2, boss.y);
        std::cout << "\033[1;33m*** BOOM ***\033[0m";
        gotoxy(boss.x - 2, boss.y + 1);
        std::cout << "\033[1;33m  *******  \033[0m";
        Sleep(150);

        gotoxy(boss.x - 4, boss.y - 1);
        std::cout << "\033[1;33m**       **\033[0m";
        gotoxy(boss.x - 2, boss.y);
        std::cout << "\033[1;33m*  BOOM  *\033[0m";
        gotoxy(boss.x - 4, boss.y + 1);
        std::cout << "\033[1;33m**       **\033[0m";
        Sleep(150);

        gotoxy(boss.x - 6, boss.y - 2);
        std::cout << "\033[1;33m*           *\033[0m";
        gotoxy(boss.x - 6, boss.y - 1);
        std::cout << "\033[1;33m *  BOOOOM  *\033[0m";
        gotoxy(boss.x - 6, boss.y);
        std::cout << "\033[1;33m*           *\033[0m";
        Sleep(150);
    }
    EraseBossSubmarine(boss);
    ClearBossMissiles();
}

#endif // BOSS_SUBMARINE_H_INCLUDED