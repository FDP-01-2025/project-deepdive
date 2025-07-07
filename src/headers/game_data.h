#ifndef GAME_DATA_H
#define GAME_DATA_H
#include <iostream>
#include <fstream>
#include <string>
#include <chrono> //Permite trabajar con el tiempo.

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

    // Leer los registros existentes (capitán + tiempo)
    std::ifstream infile("database/temp.txt");
    if (infile.is_open())
    {
        while (count < MAX_TIMES && infile >> captains[count] >> times[count])
        {
            count++;
        }
        infile.close();
    }

    // Verificar si el capitán ya existe
    for (int i = 0; i < count; i++)
    {
        if (captains[i] == captain)
        {
            times[i] = duration; // Reemplaza su tiempo actual por el nuevo
            replaced = true;
            break;
        }
    }

    // Si no se reemplazó, agregar nuevo registro
    if (!replaced && count < MAX_TIMES + 1)
    {
        captains[count] = captain;
        times[count] = duration;
        count++;
    }

    // Ordenar los tiempos de mayor a menor
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

    // Limitar a los mejores 3
    if (count > MAX_TIMES)
        count = MAX_TIMES;

    // Guardar datos en archivo base (para lectura interna)
    std::ofstream datafile("database/temp.txt");
    if (datafile.is_open())
    {
        for (int i = 0; i < count; i++)
        {
            datafile << captains[i] << " " << times[i] << "\n";
        }
        datafile.close();
    }

    // Guardar ranking visible
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
        std::cout << "[DBG] No pude abrir: " << db_deepdive << "\n";
        std::cout << "Pulsa tecla...";
        int c = _getch();
        return;
    }
    std::string line;

    system("chcp 65001 > nul");
    std::cout << "\n===== 🏆 TABLE OF RANGES - SURVIVAL MODE 🏆 =====\n\n";
    std::cout << "╔═════════════════════╦════════════════════════╦══════════════════╗\n";
    std::cout << "║ Posición            ║ Username               ║ Time             ║\n";
    std::cout << "╠═════════════════════╬════════════════════════╣══════════════════╣\n";

    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }
    std::cout << "╚═════════════════════╩════════════════════════╩══════════════════╝\n";

    system("chcp 437 > nul");

    file.close();

    std::ifstream archivo("database/deepdive_puntajes.txt");
    if (!archivo.is_open())
    {
        std::cout << "[DBG] No pude abrir: database/deepdive_puntajes.txt\n";
        std::cout << "Pulsa tecla...";
        _getch();
        return;
    }

    system("chcp 65001 > nul");
    std::cout << "\n===== 🎯 HISTORIAL DE INTENTOS 🎯 =====\n\n";
    std::cout << "╔════════════╦═════════════════════════╗\n";
    std::cout << "║ Intento    ║ Resultado               ║\n";
    std::cout << "╠════════════╬═════════════════════════╣\n";

    std::string linea;
    int intento = 1;

    while (std::getline(archivo, linea))
    {
        std::cout << "    " << std::left << intento++
                  << "\t\t" << std::left << linea << "\n";
    }

    std::cout << "╚════════════╩═════════════════════════╝\n";
    system("chcp 437 > nul");

    std::cout << "\nPresione cualquier tecla para continuar...";
    _getch();
    archivo.close();
}

static void guardarPuntaje(int puntaje)
{
    std::ofstream archivo("database/deepdive_puntajes.txt", std::ios::app);
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo de puntajes." << std::endl;
    }
    archivo << puntaje << " score" << "\n";
    archivo.close();
}

#endif

// que muestre los datos en una tabla