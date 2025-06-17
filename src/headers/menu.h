#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

const int TITLE_ROWS = 8;
extern const string titleLines[TITLE_ROWS];
extern const string menuOptions[];
extern const int numOptions;

void drawTitle(int color);
void drawMenuOption(int row, bool selected);
void MenuBorder();

#endif