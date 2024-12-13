#pragma once

#include "Point.h"
#include <conio.h>
#include <iostream>
#include <windows.h>

void gotoScreenPos(Point screenPosition);
void ShowConsoleCursor(bool showFlag);
void flushInputBuffer();
void clearScreen();