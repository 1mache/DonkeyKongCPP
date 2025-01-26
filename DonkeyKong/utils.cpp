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

void readFileNames(std::vector<std::string>& outVector, std::string extension)
{
    // the dir iteration code was taken from here:
    // https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    // and changed to some extent

    // using regex: https://www.geeksforgeeks.org/how-to-match-a-pattern-in-a-string-in-cpp/

    // string defining the template that we use to find level files. regular expression that means any 
    // sequence of eng alphabet letters and digits after dkong_ that ends with .screen
    std::string levelFileNameTemplate = std::string(Constants::FILENAME_PREFIX) + ".+\\" + extension;

    std::regex pattern(levelFileNameTemplate);

    namespace fs = std::filesystem;
    std::string path = fs::current_path().string();

    for (const auto& entry : fs::directory_iterator(path))
    {
        std::string filename = entry.path().filename().string();
        //if filename matches the pattern
        if (std::regex_match(filename, pattern))
            outVector.push_back(filename); // push it to the vector
    }
}
