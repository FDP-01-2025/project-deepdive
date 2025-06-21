// #include "src/headers/menuprincipal.h"
#include "src/headers/hide_cursor.h"
#include "src/levels/survival_mode.h"
using namespace std;
int main()
{
    HideCursor();
    // runMenu(); // Llama al menú y controla toda su ejecución
    InitGameSurvivalMode();
    GameLoopSurvivalMode();
    return 0;
}