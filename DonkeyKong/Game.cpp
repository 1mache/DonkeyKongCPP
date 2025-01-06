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
                player->stateByKey(key);
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
    int screenHeight = Constants::SCREEN_HEIGHT, screenWidth = Constants::SCREEN_WIDTH;
    //TODO: set ghost start positions

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
            //if line ended before board at that line was filled
            if (lineEnded || fileEnded)
            {
                if (row == screenHeight - 1)
                    // fill last line with floor
                    (*map)[row][col] = Board::DEFAULT_FLOOR;
                else
                    // fill with blank space
                    (*map)[row][col] = Board::BLANK_SPACE;

                continue;
            }

            char c = levelFile.get();

            switch (c)
            {
            //TODO: add case for ghosts
            case MARIO_SPRITE:
                marioStartPos = {col, row};
                (*map)[row][col] = Board::BLANK_SPACE;
                continue; // we dont want to have the mario char on board, skip to next iteration
                
            case Board::DONKEY_KONG:
                donkeyKongPos = {col, row};
                break;

            case Board::PAULINE:
                paulinePos = {col, row};
                break;
            
            case EOF: 
                fileEnded = true;
                break;

            case '\n':
                lineEnded = true;
                break;

            default:
                break;
            }

            (*map)[row][col] = c;
        }

        (*map)[row][screenWidth] = '\0'; // terminate the line that we read
        
        // if we have more than 80 chars in one of the lines in a file we want to discard them 
        char discard = levelFile.get();
        while(discard != '\n' && !levelFile.eof())
        {
            discard = levelFile.get();
        }
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
            // throw the biggest fucking exception!!!!!
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
}