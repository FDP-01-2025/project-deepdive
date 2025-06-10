#include "../headers/move_cursor.h"
#include "../headers/hide_cursor.h"
#include "../headers/game_limits.h"
#include "../headers/submarine.h"
#include "../headers/fish.h"
#include "../headers/mines.h"

int main()
{
    int num_fishes;
    system("mode con: cols=120 lines=30");
    // LLamada a funciones para pintar el escenario, y ocultar el cursor
    GameLimits();
    HideCursor();

    // Define la posición inicial del submarino, y la cantidad de vidas
    Submarine submarine = {5, 15, 1, 3};
    // Pinta el submarino y sus vidas
    PaintSubmarine(&submarine);
    PaintHearts(&submarine);
    Fish fish1 = {90, 3}, fish2 = {80, 12}, fish3 = {100, 17};

    Fish fishes[] = {fish1, fish2, fish3};
    num_fishes = sizeof(fishes) / sizeof(fishes[0]);
    Mines mines1 = {100, 25};

    do
    {
        // Mueve el submarino en la posición de "x" y "y".
        MoveSubmarine(&submarine);
        MoveMines(&mines1);
        for (int i = 0; i < num_fishes; i++)
        {
            MoveFish(&fishes[i]);
            collision_fish(&fishes[i], &submarine);
        }
        /*Detiene la ejecución por 50 milisegundos para no saturar el procesador*/
        Sleep(5);
    } while (submarine.lifes > 0);

    //Holiwis i love u so much, muacks, muacks

    return 0;
}