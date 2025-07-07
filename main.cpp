
#include "src/headers/hide_cursor.h"
#include "src/headers/principalmenu.h"
#include "src/headers/game_data.h"
using namespace std;
int main()
{
    HideCursor();
    GameCharacters();
    runMenu(); // Llama al menú y controla toda su ejecución

    return 0;
}