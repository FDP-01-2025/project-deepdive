#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include "position.h"

void Timer(int time)
{
    gotoxy(5, 1);
    std::cout << "Time: " << time <<" sec.";
}
#endif