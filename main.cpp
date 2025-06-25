#include "src/headers/menuprincipal.h"
#include "src/headers/hide_cursor.h"
#include "src/levels/level3.h"
using namespace std;
int main()
{
    HideCursor();
    //runMenu(); // Llama al menú y controla toda su ejecución
    InitGameLevel3();
    GameLoopLevel3();


    return 0;
}