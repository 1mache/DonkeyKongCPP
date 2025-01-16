#include "Game.h"

void Game::update()
{
    constexpr char KEY_NOT_SET = -1;

    while (true)
    {
        if (_kbhit())
        {
            char key1 = _getch();
            char key2 = KEY_NOT_SET;
           
            if(_kbhit())
                key2 = _getch();

            if (key1 == ESC || key2 == ESC)
            {
                // when ESC is pressed alter between paused and not paused
                if (!isPaused) pauseGame();
                else continueGame();
            }
            // alter state by input if not paused 
            if(!isPaused)
            {
                player->handleKeyboardInput(key1);
                
                if(key2 != KEY_NOT_SET)
                    player->handleKeyboardInput(key2);
            }
        }
        
        if (!isPaused)
        {
            // First check if we hit something
            checkPlayerHitEnemy();
            
            // then update the player (move him)
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

            if(ghostsManager)
                ghostsManager->manageGhosts();

            barrelManager->manageBarrels();

            drawHammer();

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

void Game::getPlayerConfirmation()
{
    while(true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == ENTER)
                break;
        }
    }
}

void Game::drawHammer()
{
    // if the hammer exists on the level and player hasnt picked it up yet
    if (hammerPos != Constants::POS_NOT_SET && !player->isHoldingHammer())
    {
        // draw the hammer
        gotoScreenPos(hammerPos);
        std::cout << Board::HAMMER;
        // add it to current board
        gameBoard->updateBoardWithChar(hammerPos, Board::HAMMER);
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

void Game::resetGhostsManager()
{
    if (!ghostsStartPositions.empty())
    {
        delete ghostsManager;
        ghostsManager = new GhostsManager(gameBoard);
        ghostsManager->resetGhosts(ghostsStartPositions);
    }
    else
    {
        delete ghostsManager;
    }
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
    resetEntitiesPositions();

    int screenHeight = Constants::SCREEN_HEIGHT, screenWidth = Constants::SCREEN_WIDTH;
    // create a vector that represents the board, see Board::posToIndex on how we access its elements
    std::vector<char> map(screenHeight * screenWidth);

    std::ifstream levelFile(filename);

    if(!levelFile.is_open())
    {
        throw LevelFileException("File error. Couldn't open the file: " + filename);
    }

    bool fileEnded = false;
    for (int row = 0; row < screenHeight; row++)
    {
        bool lineEnded = false;
        for (int col = 0; col < screenWidth; col++)
        {
            Point pos = {col, row};
            //if line ended or file ended "prematurely"
            if (lineEnded || fileEnded)
            {
                // fill with blank space
                map[Board::posToIndex(pos)] = Board::BLANK_SPACE;
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
                    map[Board::posToIndex(pos)] = Board::BLANK_SPACE;
                    continue;
                }
            }
            
            map[Board::posToIndex(pos)] = c;
        }

        //(*map)[row][screenWidth] = '\0'; // terminate the line that we read
        discardRestOfLine(levelFile);

        // if we reached eof and its not the last row
        if (levelFile.eof() && row != screenHeight - 1)
            fileEnded = true;
    }

    std::string entityMissing;
    if(isEntityMissing(entityMissing))
    {
        levelFile.close();
        throw LevelFileException("File error. " + entityMissing + " not found in the file");
    }
    
    levelFile.close();

    return new Board(std::move(map));
}

void Game::resetEntitiesPositions()
{
    marioStartPos = Constants::POS_NOT_SET;
    donkeyKongPos = Constants::POS_NOT_SET;
    paulinePos = Constants::POS_NOT_SET;
    legendPos = Constants::POS_NOT_SET;
    hammerPos = Constants::POS_NOT_SET;
    ghostsStartPositions.clear();
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
    
    case Board::GHOST:
        ghostsStartPositions.push_back(position);
        isAddedToBoard = false;
        break;

    case Board::HAMMER:
        if (hammerPos == Constants::POS_NOT_SET)
            hammerPos = position;
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


void Game::checkPlayerHitEnemy()
{
    Point destroyPos = player->handleHammer();
    if (destroyPos != Constants::POS_NOT_SET)
    {
        if (gameBoard->getCharAtPos(destroyPos) == Board::BARREL)
        {
            barrelManager->destroyBarrelAtPos(destroyPos);
        }
        if (gameBoard->getCharAtPos(destroyPos) == Board::GHOST)
        {
            ghostsManager->destroyGhostAtPos(destroyPos);
        }

        addScore(ENEMY_SCORE_AMOUNT);
    }
}

bool Game::start()
{
    if(levelFileNames.size() == 0)
    {
        std::cout << "No levels for the game to load, check: " << std::filesystem::current_path() << " for level files" << std::endl;
        std::cout << "Press ENTER to go back to main menu";
        getPlayerConfirmation();
        return true;
    }

    // iterate until we`ve read all files
    while(currLevel < levelFileNames.size())
    {
        std::string nextLevelFilename = levelFileNames[currLevel];

        delete gameBoard;
        try        
        {
            gameBoard = readLevelFromFile(nextLevelFilename);
        }
        catch (LevelFileException& e)
        {
            clearScreen();
            std::cout << "Level number " << currLevel + 1 << ", filename: "<< nextLevelFilename << " is invalid" << std::endl;
            std::cout << e.what() << std::endl;
            // if the last level is invalid game over
            if (currLevel == levelFileNames.size() - 1)
            {
                std::cout << "This was the last level, press ENTER to end game";
                getPlayerConfirmation();
                return true;
            }
            else
            {
                std::cout << "Press ENTER to load next level";
                getPlayerConfirmation();
            }
            
            currLevel++;
            continue;
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

    srand(time(0)); // gets us a new seed for use in rand

    gameBoard->resetBoard();
    
    if(hammerPos != Constants::POS_NOT_SET)
    {
        gameBoard->updateBoardWithChar(hammerPos, Board::HAMMER);
    }

    gameBoard->print();

    updateLegend();

    //need to clear input buffer after animation  
    flushInputBuffer();

    // reset player and barrel manager
    delete player;
    player = new Player(gameBoard, MARIO_SPRITE, marioStartPos);
    delete barrelManager;
    barrelManager = new BarrelManager(gameBoard, donkeyKongPos);
    
    resetGhostsManager();
}