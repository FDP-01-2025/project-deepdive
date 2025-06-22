#include "src/headers/menuprincipal.h"
#include "src/headers/hide_cursor.h"
using namespace std;
int main()
{
    HideCursor();
    runMenu(); // Llama al menú y controla toda su ejecución  
    return 0;
}