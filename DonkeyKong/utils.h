#pragma once

#include "GameOptions.h"
#include "Point.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <filesystem>
#include <regex>

namespace DK_utils
{
    //checks if given screen pos in bounds
    bool isScreenPosInBounds(Point screenPosition);
    // modified gotoxy function from Amir's lesson. takes our point class instead of 
    // the individual x and y
    void gotoScreenPos(Point screenPosition);
    // draws given char to the screen in given position
    void drawSymbolOnScreen(char symbol, Point screenPosition);
    // draws sequence of chars to the screen in given position
    void drawLineOnScreen(const std::string& line, Point lineStartPosition);
    // function from Amir's lesson that hides/ shows the curson on screen
    void ShowConsoleCursor(bool showFlag);
    // function used to clear the input buffer, the one that _getch takes from
    // for use see Menu.print()
    void flushInputBuffer();
    // clears the console screen and places the cursor at (0,0)
    inline void clearScreen()
    {
        // command that tells cmd to clear the screen
        system("cls");
    }
    // gets the path to dir where the executable sits 
    inline std::filesystem::path getExePath()
    { 
        return std::filesystem::path(__argv[0]).parent_path();
    }
    // reads all the file names that are in the game format with the specified extension into the specified vector  
    void readFileNames(std::vector<std::string>& outVector, std::string extension, std::string pathOffset = "");
    // returns the working directory path as a string
    inline std::string getWorkingDirectoryStr()
    {
        return std::filesystem::current_path().string();
    }
}