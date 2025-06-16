#ifndef MENU_H
#define MENU_H
#include "../levels/survival_mode.h"
#include "../levels/test_level.h"
#include "../levels/level2.h"
#include "../levels/level3.h"
//fALTA 4 y 5 + el survival mode

void Menu()
{
    int option;

    do
    {
        cout << "======================" << endl;
        cout << "      DEEP DIVE       " << endl;
        cout << "======================" << endl;
        cout << "1. Level 1 - Easy" << endl;
        cout << "2. Level 2 - Normal" << endl;
        cout<<  "3. Level 3 - Hard"<<endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: "; 
        cin >> option;

        // Limpia la pantalla justo antes de ejecutar el case elegido
        #ifdef _WIN32
        system("cls"); // en Windows
        #endif

        switch (option)
        {
        case 1:
            cout << "Starting Level 1 - Easy...\n";
            GameLimits();
            HideCursor();
            InitGameSurvivalMode();
            GameLoopSurvivalMode();
            // Limpia pantalla
            #ifdef _WIN32
            system("cls");
            #endif

            // Muestra "GAME OVER"
            cout << "  GGGGG   AAA   MMM   MMM  EEEEE  " << endl;
            cout << " G       A   A  M M M M   E      " << endl;
            cout << " G  GG  AAAAA   M  M  M   EEEE   " << endl;
            cout << " G   G  A   A   M     M   E      " << endl;
            cout << "  GGGGG  A   A  M     M   EEEEE  " << endl;
            cout << endl;
            cout << "          GAME OVER!  " << endl;
            cout << "    Press ENTER to return to menu...";
            cin.ignore();
            cin.get();

            // Limpia pantalla antes de volver al menu
            #ifdef _WIN32
            system("cls");
            #endif

            break;

        

        case 2:
            cout << "Starting Level 2 - Hard...\n";
            GameLimits();
            HideCursor();
            InitGamelevel2();
            GameLooplevel2();

            // Limpia pantalla
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            cout << "  GGGGG   AAA   MMM   MMM  EEEEE  " << endl;
            cout << " G       A   A  M M M M   E      " << endl;
            cout << " G  GG  AAAAA   M  M  M   EEEE   " << endl;
            cout << " G   G  A   A   M     M   E      " << endl;
            cout << "  GGGGG  A   A  M     M   EEEEE  " << endl;
            cout << endl;
            cout << "          GAME OVER!  " << endl;
            cout << "    Press ENTER to return to menu...";
            cin.ignore();
            cin.get();

            // Limpia pantalla antes de volver al menu
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            break;

        case 3:
            cout << "Starting Level 3- Hard...\n";
            GameLimits();
            HideCursor();
            InitGamelevel3();
            GameLooplevel3();

            // Limpia pantalla
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            cout << "  GGGGG   AAA   MMM   MMM  EEEEE  " << endl;
            cout << " G       A   A  M M M M   E      " << endl;
            cout << " G  GG  AAAAA   M  M  M   EEEE   " << endl;
            cout << " G   G  A   A   M     M   E      " << endl;
            cout << "  GGGGG  A   A  M     M   EEEEE  " << endl;
            cout << endl;
            cout << "          GAME OVER!  " << endl;
            cout << "    Press ENTER to return to menu...";
            cin.ignore();
            cin.get();

            // Limpia pantalla antes de volver al menu
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif

            break;
            
            //Faltan case para otros niveles/////////////////////////////////
            //
        case 4:
            cout << "Exiting game. Goodbye!\n";
            break;

        default:
            cout << "Invalid option, please try again.\n";
        }
        cout << endl;

    } while (option != 3);
}

#endif
