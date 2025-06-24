//#include "src/headers/menuprincipal.h"
#include "src/headers/hide_cursor.h"
#include "src/levels/level4.h"
using namespace std;
int main()
{
    HideCursor();
    //runMenu(); // Llama al menú y controla toda su ejecución
    InitGameLevel4(); // Inicializa el nivel 4 del juego
    GameLoopLevel4(); // Inicia el bucle del juego para el nivel 4

    return 0;
}