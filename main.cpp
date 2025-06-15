#include "src/game_processes.h"
using namespace std;
int main()
{
    HideCursor();
    GameLimits();
    InitGame();
    GameLoop();
    
    return 0;
}