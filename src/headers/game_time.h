#ifndef GAME_TIME_H
#define GAME_TIME_H
#include <chrono> //Permite trabajar con el tiempo.
#include <fstream> //Permite crear archivos .txt.

void SaveGameTimeToFile(long long seconds, const string &filename = "db_deepdive.txt")
{
    ofstream archivo(filename);
    if (archivo.is_open())
    {
        archivo << "Tiempo de supervivencia: " << seconds << " segundos" << endl;
        archivo.close();
    }
    else
    {
        cerr << "No se pudo guardar el progreso" << filename << endl;
    }
}
#endif