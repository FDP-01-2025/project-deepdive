#ifndef GAME_TIME_H
#define GAME_TIME_H
#include "../libraries/libraries.h"
using namespace std;
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