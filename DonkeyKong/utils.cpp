#include "utils.h"

bool isScreenPosInBounds(Point screenPosition)
{
    int x = screenPosition.getX();
    int y = screenPosition.getY();
    return ((0 <= x && x < GameOptions::SCREEN_WIDTH) && (0 <= y && y < GameOptions::SCREEN_HEIGHT));
}

void gotoScreenPos(Point screenPosition)
{
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = screenPosition.getX(); // Set the X coordinate 
    coord.Y = screenPosition.getY(); // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

void drawSymbolOnScreen(char symbol, Point screenPosition)
{
    // dont draw if silent mode is on 
    if (GameOptions::isSilentModeOn())
        return;
    
    if(isScreenPosInBounds(screenPosition))
    {
        gotoScreenPos(screenPosition);
        std::cout << symbol;
    }
}

void drawLineOnScreen(const std::string& line, Point lineStartPosition)
{
    // dont draw if silent mode is on 
    if (GameOptions::isSilentModeOn())
        return;

    Point lineEndPosition = lineStartPosition + Point(line.size() ,0);
    // if the position of both start and end is in bounds priint the line
    if (isScreenPosInBounds(lineStartPosition))
    {
        gotoScreenPos(lineStartPosition);
        // if the end is not in bounds print only the part that is in bounds
        if(!isScreenPosInBounds(lineEndPosition))
        {
            std::string slicedLine = line.substr(0, GameOptions::SCREEN_WIDTH - lineStartPosition.getX());
            std::cout << slicedLine;
        }
        else std::cout << line;
    }
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

void readFileNames(std::vector<std::string>& outVector, std::string extension)
{
    // the dir iteration code was taken from here:
    // https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    // and changed to some extent

    // using regex: https://www.geeksforgeeks.org/how-to-match-a-pattern-in-a-string-in-cpp/

    // string defining the template that we use to find level files. regular expression that means any 
    // sequence of eng alphabet letters and digits after dkong_ that ends with .screen
    std::string levelFileNameTemplate = std::string(GameOptions::FILENAME_PREFIX) + ".+\\" + extension;

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