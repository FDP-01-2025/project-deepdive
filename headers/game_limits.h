#ifndef GAME_LIMITS_H_INCLUDED
#define GAME_LIMITS_H_INCLUDED
#include "../headers/position.h"

/*Pinta los límites del escenario de juego*/
void GameLimits()
{
    //Parte orizontal
    for (int i = 2; i < 120; i++)
    {
        gotoxy(i, 2);
        cout<<("%c", 205)<<endl;
        gotoxy(i, 28);
        cout<<("%c", 205)<<endl;
    }

    //Parte vertical
    for (int j = 2; j < 28; j++)
    {
        gotoxy(2, j);
        cout<<("%c", 186)<<endl;
        gotoxy(119, j);
        cout<<("%c", 186)<<endl;
    }

    //Esquinas
    gotoxy(2, 2);
    cout<<("%c", 201)<<endl;
    gotoxy(119, 2);
    cout<<("%c", 187)<<endl;
    gotoxy(2, 28);
    cout<<("%c", 200)<<endl;
    gotoxy(119, 28);
    cout<<("%c", 188)<<endl;
}

#endif