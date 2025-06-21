#include "src/headers/menuprincipal.h"
#include "src/headers/hide_cursor.h"
#include "src/levels/level2.h"
using namespace std;
int main()
{
    HideCursor();
    //runMenu(); // Llama al menú y controla toda su ejecución
    InitGamelevel2();
    GameLooplevel2();

  
    return 0;
}