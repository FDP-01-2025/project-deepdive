#include "../headers/move_cursor.h"
#include "../headers/hide_cursor.h"
#include "../headers/game_limits.h"
#include "../headers/submarine.h"

int main()
{
    system("mode con: cols=120 lines=30");
    // LLamada a funciones para pintar el escenario, y ocultar el cursor
    GameLimits();
    HideCursor();

    //Define la posición inicial del submarino, y la cantidad de vidas
    Submarine submarine = {5, 15, 1, 3};
    //Pinta el submarino y sus vidas
    PaintSubmarine(&submarine);
    PaintHearts(&submarine);

    do
    {
        //Mueve el submarino en la posición de "x" y "y".
        MoveSubmarine(&submarine);
        /*Detiene la ejecución por 50 milisegundos para no saturar el procesador*/
        Sleep(5);
    } while (submarine.lifes > 0);

    return 0;
}