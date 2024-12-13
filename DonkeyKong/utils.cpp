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
    // "flush" all input that was previously there
    while (_kbhit())
    {
        //store it so ignored return value warning doesnt pop up
        char ignored = _getch();
    }
}

void clearScreen()
{
    //empties the console screen
    system("cls");
}
