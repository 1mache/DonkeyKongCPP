#include "utils.h"

void gotoScreenPos(Point screenPosition)
{
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = screenPosition.getX(); // Set the X coordinate 
    coord.Y = screenPosition.getY(); // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void flushInputBuffer()
{
    while (_kbhit())
    {
        //we want to explicitly ignore return value without the warning popping up
        // this is the approach we found here: https://stackoverflow.com/questions/689677/why-cast-unused-return-values-to-void 
        (void)_getch();
    }
}

void clearScreen()
{
    // command that tells cmd to clear the screen
    system("cls");
}
