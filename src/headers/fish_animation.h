#ifndef FISHANIMATION_H
#define FISHANIMATION_H

#include <iostream>
#include <windows.h>
#include <string>

extern const int FISH_OFFSET;
extern const std::string fishLR, fishRL;
void animateFish(int &fishX, bool &fishDir, int fishMaxX, DWORD &lastFish);

#endif