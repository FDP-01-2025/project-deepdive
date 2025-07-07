#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED
#include <windows.h> //it allows you to position the cursor.

/*Function to move the console cursor, in "x" and "y".*/
void gotoxy(int x, int y)
{
    HANDLE hCon;
    //Gets the console handle.
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    //Moves the cursor to the position "x" and "y".
    SetConsoleCursorPosition(hCon, dwPos);
}

#endif