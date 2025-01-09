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
            player->update();

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

void Game::updateLegend() const
{
    gotoScreenPos(legendPos);
    std::cout << "Score: " << score;
    gotoScreenPos(legendPos.oneBelow());
    std::cout << "<3 : " << lives;
}

void Game::pauseGame()
{
    isPaused = true;
    Point pauseMessagePos = legendPos.oneBelow().oneBelow();
    // print pause message
    gotoScreenPos(pauseMessagePos);
    std::cout << PAUSE_MESSAGE;
}

void Game::continueGame()
{
    isPaused = false;
    //erase pause game message and restore what has been on the board 
    Point restorePos = legendPos.oneBelow().oneBelow();

    for (int i = 0; i < strlen(PAUSE_MESSAGE); i++)
    {
        gotoScreenPos(restorePos);
        std::cout << gameBoard->getCharAtPos(restorePos);
        restorePos = restorePos.oneRight();
    }
}

Board* Game::readLevelFromFile(const std::string& filename)
{
    marioStartPos = Constants::POS_NOT_SET;
    donkeyKongPos = Constants::POS_NOT_SET;
    paulinePos = Constants::POS_NOT_SET;

    int screenHeight = Constants::SCREEN_HEIGHT, screenWidth = Constants::SCREEN_WIDTH;
    // dynamic allocation of pointer to a 2D array, we will pass this to board 
    char (*map)[Constants::SCREEN_HEIGHT][Constants::SCREEN_WIDTH + 1] = new char[1][Constants::SCREEN_HEIGHT][Constants::SCREEN_WIDTH + 1];
    // create a smart pointer out of it so it is safe, because we will pass ownership of it to board
    std::unique_ptr<const char[Constants::SCREEN_HEIGHT][Constants::SCREEN_WIDTH + 1]> mapPtr(map);

    std::ifstream levelFile(filename);

    if(!levelFile.is_open())
    {
        throw LevelFileException("File invalid. Couldn't open the file:" + filename);
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
                // fill with blank space
                (*map)[row][col] = Board::BLANK_SPACE;
            }

            char c = levelFile.get();
            if (c == EOF)
            {
                fileEnded = true;
                continue;
            }
            else if (c == '\n')
            {
                lineEnded = true;
                continue;
            }
            else if (c != Board::BLANK_SPACE) 
            {
                // the function decides whether the char should be added to board
                if(!setEntityPositionByChar(c, { col, row }))
                {
                    (*map)[row][col] = Board::BLANK_SPACE;
                    continue;
                }
            }
            
            (*map)[row][col] = c;
        }

        (*map)[row][screenWidth] = '\0'; // terminate the line that we read
        discardRestOfLine(levelFile);

        // if we reached eof and its not the last row
        if (levelFile.eof() && row != screenHeight - 1)
            fileEnded = true;
    }

    std::string entityMissing;
    if(isEntityMissing(entityMissing))
    {
        levelFile.close();
        throw LevelFileException("File invalid. " + entityMissing + " not found in the file");
    }
    
    levelFile.close();

    return new Board(std::move(mapPtr));
}

bool Game::setEntityPositionByChar(char c, Point position)
{
    // return val
    bool isAddedToBoard = true;
    switch (c)
    {
    case MARIO_SPRITE:
        if (marioStartPos == Constants::POS_NOT_SET)
            marioStartPos = position;
        // if this function returned false:
        isAddedToBoard = false; // we dont want to have the mario char on board
        break;

    case Board::DONKEY_KONG:
        if (donkeyKongPos == Constants::POS_NOT_SET)
            donkeyKongPos = position;
        else
            isAddedToBoard = false;
        break;

    case Board::PAULINE:
        if (paulinePos == Constants::POS_NOT_SET)
            paulinePos = position;
        else
            isAddedToBoard = false;
        break;

    case LEGEND_CHAR:
        if (legendPos == Constants::POS_NOT_SET)
            legendPos = position;
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

bool Game::isEntityMissing(std::string& outEntityMissing)
{
    if (marioStartPos == Constants::POS_NOT_SET)
    {
        outEntityMissing = "Mario";
        return true;
    }
    if (donkeyKongPos == Constants::POS_NOT_SET)
    {
        outEntityMissing = "Donkey Kong";
        return true;
    }
    if (paulinePos == Constants::POS_NOT_SET)
    {
        outEntityMissing = "Pauline";
        return true;
    }
    if (legendPos == Constants::POS_NOT_SET)
    {
        outEntityMissing = "Legend";
        return true;
    }

    return false;
}

bool Game::start()
{
    if(levelFileNames.size() == 0)
    {
        throw LevelFileException("The list of levels passed to Game is empty.");
        return true;
    }

    // iterate until we`ve read all files
    while(currLevel < levelFileNames.size())
    {
        std::string nextLevelFilename = levelFileNames[currLevel];

        delete gameBoard;
        gameBoard = readLevelFromFile(nextLevelFilename);

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

    srand(time(0)); // gets us a new seed for use in rand

    gameBoard->resetBoard();
    gameBoard->print();

    score = 0;
    updateLegend();

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

void Game::checkPlayerHitHammerEnemy()
{
    Point destroyPos = player->handleHammer();
    if (destroyPos != Constants::POS_NOT_SET)
    {
        if(gameBoard->getCharAtPos(destroyPos) == Board::BARREL)
            barrelManager->destroyBarrelAtPos(destroyPos);
        else
            ghostsManager->destroyGhostAtPos(destroyPos);
    }
}