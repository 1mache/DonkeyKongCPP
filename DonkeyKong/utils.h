#pragma once

#include "Point.h"
#include <conio.h>
#include <iostream>
#include <windows.h>


// modified gotoxy function from Amir's lesson. takes our point class instead of 
// the individual x and y
void gotoScreenPos(Point screenPosition);
// function from Amir's lesson that hides/ shows the curson on screen
void ShowConsoleCursor(bool showFlag);
// function used to clear the input buffer, the one that _getch takes from
// for use see Menu.print()
void flushInputBuffer();
// clears the console screen and places the cursor at (0,0)
void clearScreen();