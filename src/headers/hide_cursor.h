#ifndef HIDE_CURSOR_H_INCLUDED
#define HIDE_CURSOR_H_INCLUDED
#include <windows.h>
void HideCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    //Cursor size.
    cci.dwSize = 2;
    //Set to false to define that the cursor is not visible.
    cci.bVisible = FALSE;
    //Apply the settings to hide the cursor.
    SetConsoleCursorInfo(hCon, &cci);
}

#endif