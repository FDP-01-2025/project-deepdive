#ifndef GAME_DATA_H
#define GAME_DATA_H
#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // Allows working with time.

const int MAX_TIMES = 4;

static void GameCharacters()
{
    std::ofstream file("database/characters.txt");
    file << "Armand Cortez\n"
         << "Silvia Marlowe\n"
         << "Theo Vázquez\n"
         << "Ingrid Falkner\n";
    file.close();
}

void SaveGameTimeToFile(int duration, std::string captain)
{
    std::string captains[MAX_TIMES + 1];
    int times[MAX_TIMES + 1];
    int count = 0;
    bool replaced = false;

    // Read existing records (captain + time)
    std::ifstream infile("database/temp.txt");
    if (infile.is_open())
    {
        while (count < MAX_TIMES && infile >> captains[count] >> times[count])
        {
            count++;
        }
        infile.close();
    }

    // Check if the captain already exists
    for (int i = 0; i < count; i++)
    {
        if (captains[i] == captain)
        {
            times[i] = duration; // Replace their current time with the new one
            replaced = true;
            break;
        }
    }

    // If not replaced, add new record
    if (!replaced && count < MAX_TIMES + 1)
    {
        captains[count] = captain;
        times[count] = duration;
        count++;
    }

    // Sort times from highest to lowest
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (times[j] > times[i])
            {
                std::swap(times[i], times[j]);
                std::swap(captains[i], captains[j]);
            }
        }
    }

    // Limit to the top 3
    if (count > MAX_TIMES)
        count = MAX_TIMES;

    // Save data to base file (for internal reading)
    std::ofstream datafile("database/temp.txt");
    if (datafile.is_open())
    {
        for (int i = 0; i < count; i++)
        {
            datafile << captains[i] << " " << times[i] << "\n";
        }
        datafile.close();
    }

    // Save visible ranking
    std::ofstream outfile("database/db_deepdive.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < count; i++)
        {
            int minutes = times[i] / 60;
            int seconds = times[i] % 60;
            outfile << "\t" << (i + 1) << "°\t\t\t" << captains[i]
                    << "\t\t  " << minutes << " min " << seconds << " sec\n";
        }
        outfile.close();
    }
    remove("database/temp.txt");
}

void readFile(const std::string &db_deepdive)
{
    system("cls");
    setColor(11);
    gotoxy(0, 0);

    std::ifstream file(db_deepdive);
    if (!file.is_open())
    {
        std::cout << "[DBG] Could not open: " << db_deepdive << "\n";
        std::cout << "Press any key...";
        int c = _getch();
        return;
    }
    std::string line;

    system("chcp 65001 > nul");
    std::cout << "\n===== 🏆 TABLE OF RANKINGS - SURVIVAL MODE 🏆 =====\n\n";
    std::cout << "╔═════════════════════╦════════════════════════╦══════════════════╗\n";
    std::cout << "║ Position            ║ Username               ║ Time             ║\n";
    std::cout << "╠═════════════════════╬════════════════════════╣══════════════════╣\n";

    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }
    std::cout << "╚═════════════════════╩════════════════════════╩══════════════════╝\n";

    system("chcp 437 > nul");

    file.close();

    std::ifstream historyFile("database/deepdive_puntajes.txt");
    if (!historyFile.is_open())
    {
        std::cout << "[DBG] Could not open: database/deepdive_puntajes.txt\n";
        std::cout << "Press any key...";
        _getch();
        return;
    }

    system("chcp 65001 > nul");
    std::cout << "\n===== 🎯 ATTEMPT HISTORY 🎯 =====\n\n";
    std::cout << "╔════════════╦═════════════════════════╗\n";
    std::cout << "║ Attempt    ║ Result                  ║\n";
    std::cout << "╠════════════╬═════════════════════════╣\n";

    std::string lineHistory;
    int attempt = 1;

    while (std::getline(historyFile, lineHistory))
    {
        std::cout << "    " << std::left << attempt++
                  << "\t\t" << std::left << lineHistory << "\n";
    }

    std::cout << "╚════════════╩═════════════════════════╝\n";
    system("chcp 437 > nul");

    std::cout << "\nPress any key to continue...";
    _getch();
    historyFile.close();
}

static void saveScore(int score)
{
    std::ofstream file("database/deepdive_puntajes.txt", std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "Error opening the score file." << std::endl;
    }
    file << score << " score" << "\n";
    file.close();
}

#endif