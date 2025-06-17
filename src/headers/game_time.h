#ifndef GAME_TIME_H_INCLUDED
#define GAME_TIME_H_INCLUDED
#include <chrono>  //Permite trabajar con el tiempo.
#include <fstream> //Permite crear archivos .txt.

void SaveGameTimeToFile(long long seconds, const std::string &filename = "db_deepdive.txt")
{
    std::ofstream archivo(filename);
    if (archivo.is_open())
    {
        archivo << "Tiempo de supervivencia: " << seconds << " segundos" << "\n";
        archivo.close();
    }
    // else
    // {
    //     cerr << "No se pudo guardar el progreso" << filename << endl;
    // }
}
#endif