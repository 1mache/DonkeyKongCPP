#include "Game.h"

void Game::update()
{
    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == ESC)
            {
                // when ESC is pressed alter between paused and not paused
                if (!isPaused) pauseGame();
                else continueGame();
            }
            // alter state by input if not paused 
            if(!isPaused)
            {
                player->handleKeyboardInput(key);
            }
        }
        
        if (!isPaused)
        {
            player->movePlayer();

            //check for barrel collisions and fall damage
            if (player->checkCollision() || player->checkFallDamage())
            {
                if(handleStrike())
                {
                    continue; // level was reset, continue the game loop
                }
                else
                {
                    break; // going to menu
                }
            }

            barrelManager->manageBarrels();
            ghostsManager->manageGhosts();

            //check again for barrel collisions - after barrels moved
            if (player->checkCollision())
            {
                if (handleStrike())
                {
                    continue; // level was reset, continue the game loop
                }
                else
                {
                    break; // going to menu
                }
            }

            //win check
            if(player->getPosition() == paulinePos)
            {
                currLevel++; // move to next level
                break; // player reached pauline, exit loop 
            }
        }

        Sleep(Constants::GAME_REFRESH_RATE);
    }
}

bool Game::handleStrike()
{
    player->takeDamage();
    lives--;

    if (lives == 0)
    {
        return false;
    }
    else
    {
        resetLevel();
        return true;
    }
}

void Game::pauseGame()
{
    isPaused = true;
    // print pause message
    gotoScreenPos(PAUSEMESSAGE_POS);
    std::cout << PAUSE_MESSAGE;
}

void Game::continueGame()
{
    isPaused = false;
    //erase pause game message and restore what has been on the board 
    Point restorePos = PAUSEMESSAGE_POS;
    for (int i = 0; i < strlen(PAUSE_MESSAGE); i++)
    {
        gotoScreenPos(restorePos);
        std::cout << gameBoard->getCharAtPos(restorePos);
        restorePos = restorePos.oneRight();
    }
}

Board* Game::readLevelFromFile(const std::string& filename)
{
    marioStartPos = POS_NOT_SET;
    donkeyKongPos = POS_NOT_SET;
    paulinePos = POS_NOT_SET;

    int screenHeight = Constants::SCREEN_HEIGHT, screenWidth = Constants::SCREEN_WIDTH;
    // dynamic allocation of pointer to a 2D array, we will pass this to board, and the board will handle it 
    char (*map)[Constants::SCREEN_HEIGHT][Constants::SCREEN_WIDTH + 1] = new char[1][Constants::SCREEN_HEIGHT][Constants::SCREEN_WIDTH + 1];
    
    std::ifstream levelFile(filename);

    if(!levelFile.is_open())
    {
        // TODO: exception, file not found
        return nullptr;
    }

    bool fileEnded = false;
    for (int row = 0; row < screenHeight; row++)
    {
        bool lineEnded = false;
        for (int col = 0; col < screenWidth; col++)
        {
            //if line ended or file ended "prematurely"
            if (lineEnded || fileEnded)
            {
                if (row == screenHeight - 1)
                    // fill last line with floor
                    (*map)[row][col] = Board::DEFAULT_FLOOR;
                else
                    // by default fill with blank space
                    (*map)[row][col] = Board::BLANK_SPACE;

                continue;
            }

            char c = levelFile.get();
            if (c == EOF)
            {
                fileEnded = true;
            }
            else if (c == '\n')
            {
                lineEnded = true;
            }
            // the function decides whether the char should be added to board
            else if (setEntityPositionByChar(c, { col, row })) 
            {
                (*map)[row][col] = c;
            }
            else
            {
                (*map)[row][col] = Board::BLANK_SPACE;
            }

        }

        (*map)[row][screenWidth] = '\0'; // terminate the line that we read
        discardRestOfLine(levelFile);

        // if we reached eof and its not the last row
        if (levelFile.eof() && row != screenHeight - 1)
            fileEnded = true;
    }

    if (marioStartPos == POS_NOT_SET || donkeyKongPos == POS_NOT_SET ||
        paulinePos == POS_NOT_SET)
    {
        // TODO: exception there were no info on the positions essential for the game in the file
        return nullptr;
    }
    
    levelFile.close();

    return new Board(map);    
}

bool Game::setEntityPositionByChar(char c, Point position)
{
    // return val
    bool isAddedToBoard = true;
    switch (c)
    {
        //TODO: add case for ghosts
        //TODO: add case for legend
    case MARIO_SPRITE:
        if (marioStartPos == POS_NOT_SET)
            marioStartPos = position;
        // if this function returned false:
        isAddedToBoard = false; // we dont want to have the mario char on board
        break;

    case Board::DONKEY_KONG:
        if (donkeyKongPos == POS_NOT_SET)
            donkeyKongPos = position;
        else
            isAddedToBoard = false;
        break;

    case Board::PAULINE:
        if (paulinePos == POS_NOT_SET)
            paulinePos = position;
        else
            isAddedToBoard = false;
        break;

    default:
        break;
    }

    return isAddedToBoard;
}

void Game::discardRestOfLine(std::ifstream& levelFile)
{
    // if we have more than 80 chars in one of the lines in a file we want to discard them 
    char discard = levelFile.get();
    while (discard != '\n' && !levelFile.eof())
    {
        discard = levelFile.get();
    }
}

bool Game::start()
{
    if(levelFileNames.size() == 0)
    {
        // throw exception, no levels
        return true;
    }
    // iterate until we`ve read all files
    while(currLevel < levelFileNames.size())
    {
        std::string nextLevelFilename = levelFileNames[currLevel];

        //TODO: handling exceptions 
        gameBoard = readLevelFromFile(nextLevelFilename);

        if (!gameBoard)
        {
            // throw the biggest exception!!!!!
            std::cout << "Yo something wrong with the level!!!!!!!" << std::endl;
            return true;
        }

        resetLevel();

        update();
        // game over check
        if (lives == 0)
            return true;   
    }

    // returns true if game is over
    return (lives == 0);
}

void Game::resetLevel()
{
    clearScreen();

    srand(time(0)); // we use rand for barrel spawning, so this gets us a new seed

    gameBoard->resetBoard();
    gameBoard->print();
    updateLivesCounter();

    //need to clear input buffer after animation  
    flushInputBuffer();

    // reset player and barrel manager
    delete player;
    player = new Player(gameBoard, MARIO_SPRITE, marioStartPos);
    delete barrelManager;
    barrelManager = new BarrelManager(gameBoard, donkeyKongPos);
    delete ghostsManager;
    ghostsManager = new GhostsManager(gameBoard);
}