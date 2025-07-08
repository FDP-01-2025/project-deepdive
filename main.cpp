
#include "src/headers/hide_cursor.h"
#include "src/headers/principalmenu.h"
#include "src/headers/game_data.h"
using namespace std;
int main()
{
    HideCursor(); // Hide the console cursor for a cleaner interface
    GameCharacters(); // Initialize game characters by writing them to a file
    runMenu(); // Run the main menu of the game

    return 0;
}