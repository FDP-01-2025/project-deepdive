#ifndef GAME_TIME_H_INCLUDED
#define GAME_TIME_H_INCLUDED
#include <chrono>  //Permite trabajar con el tiempo.
#include <fstream> //Permite crear archivos .txt.

const int MAX_TIMES = 5;

void SaveGameTimeToFile(int duration)
{
    int times[MAX_TIMES + 1];
    int count = 0;

    // Leer los tiempos desde el archivo interno (solo los segundos)
    std::ifstream infile("database/db_deepdive_data.txt");
    if (infile.is_open())
    {
        while (count < MAX_TIMES && infile >> times[count])
        {
            count++;
        }
        infile.close();
    }

    // Agregar el nuevo tiempo
    times[count] = duration;
    count++;

    // Ordenar los tiempos de mayor a menor
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (times[j] > times[i])
            {
                int temp = times[i];
                times[i] = times[j];
                times[j] = temp;
            }
        }
    }

    // Limitar a los mejores 5
    if (count > MAX_TIMES)
        count = MAX_TIMES;

    // Guardar los tiempos antes de ser procesados en el archivo de datos
    std::ofstream datafile("database/db_deepdive_data.txt");
    if (datafile.is_open())
    {
        for (int i = 0; i < count; i++)
        {
            datafile << times[i] << "\n";
        }
        datafile.close();
        remove("database/db_deepdive_data.txt");
    }

    // Guardar el ranking en la base de datos
    std::ofstream outfile("database/db_deepdive.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < count; i++)
        {
            int minutes = times[i] / 60;
            int seconds = times[i] % 60;
            outfile << (i + 1) << "°: " << minutes << " min " << seconds << " sec\n";
        }
        outfile.close();
    }
    
}

#endif