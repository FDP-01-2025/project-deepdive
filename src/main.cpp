#include "../headers/position.h"
#include "../headers/hide_cursor.h"
#include "../headers/game_limits.h"
#include "../headers/submarine.h"
#include "../headers/fish.h"
#include "../headers/mines.h"
#include "../headers/missiles.h"

using namespace std;
int main()
{
    int num_fishes;
    system("mode con: cols=120 lines=30");
    GameLimits(); // LLamada a funciones para pintar el escenario, y ocultar el cursor
    HideCursor();

    Submarine submarine = {5, 15, 1, 3}; // Define la posición inicial del submarino, y la cantidad de vidas
    PaintSubmarine(&submarine);          // Pinta el submarino y sus vidas
    PaintHearts(&submarine);

    Fish fish1 = {90, 3}, fish2 = {80, 12}, fish3 = {100, 17};
    Fish fishes[] = {fish1, fish2, fish3};
    num_fishes = sizeof(fishes) / sizeof(fishes[0]);

    Mines mines1 = {100, 25};

    list<Missiles> Missil;
    list<Missiles>::iterator i; // Interador para recorrer la lista

    do
    {
        if (kbhit())
        {
            char tecla = getch();
            if (tecla == 112 || tecla == 80)
            {
                Missiles m;
                m.x = submarine.x + 12;
                m.y = submarine.y + 2;
                Missil.push_back(m);
            }
            MoveSubmarine(tecla, &submarine);
        }

        for (i = Missil.begin(); i != Missil.end();)
        {
            MoveMissil(*i);
            if (i->x >= 115)
            {
                gotoxy(i->x, i->y);
                cout << ("  ") << endl;
                i = Missil.erase(i); // Elimina el misil cuando ya pasó el borde de 115 en x.
            }
            else
            {
                i++;
            }
        }

        for (i = Missil.begin(); i != Missil.end();)
        {
            bool erasedMissil = false;

            for (int j = 0; j < num_fishes; j++)
            {
                if ((i->x == fishes[j].x || i->x == fishes[j].x + 3 || i->x == fishes[j].x + 6) && i->y == fishes[j].y)
                {
                    gotoxy(i->x, i->y);
                    cout << ("  ") << endl;
                    i = Missil.erase(i); // Elimina el misil.
                    erasedMissil = true;

                    gotoxy(fishes[j].x, fishes[j].y);
                    cout << ("         ") << endl;
                    fishes[j].x = 110;
                    fishes[j].y = rand() % 20 + 3;
                    break;
                }
            }
            if (!erasedMissil)
            {
                i++;
            }
        }

        MoveMines(&mines1);
        for (int i = 0; i < num_fishes; i++)
        {
            MoveFish(&fishes[i]);
            CollisionFish(&fishes[i], &submarine);
        }

        Sleep(5);
    } while (submarine.lifes > 0);

    //Holiwis i love u so much, muacks, muacks (att.Yukio)
    //mondongoooooo
    //buenas

    return 0;
}