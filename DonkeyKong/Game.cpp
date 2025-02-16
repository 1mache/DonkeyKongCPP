#include "Game.h"

bool Game::trySetCurrLevelByTag(const std::string& tag)
{
    std::string currTag;
    
    for (int i = 0; i < levelFileNames.size(); i++)
    {
        currTag = getLevelTag(levelFileNames[i]);
        if(currTag == tag)
        {
            currLevelId = i;
            return true;
        }
    }

    return false;
}

void Game::getPlayerConfirmation() const
{
    while (true)
    {
        if (_kbhit())
        {
            char key = static_cast<char>(_getch());
            if (key == ENTER)
                break;
        }
    }
}

bool Game::handleStrike(const PlayerEvent* event)
{
    // if the event passed is not a player event (technically should never happen)
    if(event == nullptr)
    {
        return true; // does nothing
    }

    using eventType = PlayerEvent::PlayerEventType; //to shorten the name a little :) 
  
    eventType type = static_cast<eventType>(event->getType()); // convert from int to Enum

    if (type == eventType::DIED)
    {
        if (recorded)
        {
            recResults.addResult(iterationCounter, Results::DIED);
            saveRecordings();
        }
        return false;
    }
    else if (type == eventType::LOST_A_LIFE)
    {
        if (recorded)
            recResults.addResult(iterationCounter, Results::LOST_LIFE);

        resetLevel();
        return true;
    }

    // if the above werent triggered contunue the loop
    return true;
}

void Game::levelWon()
{
    if (recorded)
    {
        recResults.addResult(iterationCounter, Results::FINISHED);
        saveRecordings();
    }

    addWinScoreReward();
    moveToNextLevel();
}

void Game::update()
{
    Event* latestEvent = nullptr;

    while (true)
    {
        KeyInput input = getInputKeys();

        if (!input.notSet())
        {
            if (input.key1 == ESC || input.key2 == ESC)
            {
                // when ESC is pressed alter between paused and not paused
                if (!isPaused) pauseGame();
                else continueGame();
            }
            else
            {
                // alter state by input if not paused 
                if (!isPaused)
                {
                    player->handleKeyboardInput(input.key1);

                    if (input.key2 != GameOptions::KEY_NOT_SET)
                        player->handleKeyboardInput(input.key2);

                    // if this is a recorded game save this step
                    if (recorded)
                        recSteps.addStep(iterationCounter, input.toPair());
                }
            }
        }

        if (!isPaused)
        {
            iterationCounter++;
            // First check if we hit something
            checkPlayerHitEnemy(); //TODO:EVENT 

            // then update the player (move him)
            player->update();

            //check for collisions and fall damage
            if (player->checkCollision() || player->checkFallDamage())
            {
                latestEvent = g_eventQueue.pop().get();
                if (handleStrike(dynamic_cast<PlayerEvent*>(latestEvent))) //should never get nullptr here but there is a check inside
                    continue; // continue the game loop, possibly game was reset
                else
                    break; // going to menu
            }

            if (ghostsManager)
                ghostsManager->manageGhosts();

            barrelManager->manageBarrels();

            drawHammer();

            //check again for barrel collisions - after barrels moved
            if (player->checkCollision())
            {
                latestEvent = g_eventQueue.pop().get();
                if (handleStrike(dynamic_cast<PlayerEvent*>(latestEvent)))
                    continue; // level was reset, continue the game loop
                else
                    break; // going to menu
            }

            //win check
            if (player->getPosition() == paulinePos) //TODO:EVENT
            {
                levelWon();
                break; // player reached pauline, exit loop 
            }

            updateLegend();
            
            // break the loop if the iteration was invalid
            if (!validateLastIteration())
                break;
        }

        Sleep(GameOptions::getRefreshRate());
    }
}

void Game::saveSteps()
{
    std::string currLevelTag = Game::getLevelTag(levelFileNames[currLevelId]);
    // building the full filename
    std::string filename = std::string(GameOptions::RECORDING_PATH) + GameOptions::FILENAME_PREFIX + currLevelTag + GameOptions::STEPS_FILE_EXT;
    recSteps.saveSteps(filename);
}

void Game::saveResults()
{
    std::string currLevelTag = Game::getLevelTag(levelFileNames[currLevelId]);
    std::string filename = std::string(GameOptions::RECORDING_PATH) + GameOptions::FILENAME_PREFIX + currLevelTag + GameOptions::RESULTS_FILE_EXT;
    recResults.saveResults(filename);
}

void Game::saveRecordings()
{
    try
    {
        saveSteps();
        saveResults();
    }
    catch (LevelFileException& e)
    {
        handleError(std::string(e.what()) + "\nCouldn`t save recording files");
    }
}

void Game::displayLevelException(LevelFileException& e)
{
    DK_utils::clearScreen();
    std::ostringstream errorMsgStream;
    errorMsgStream << "Level number " << currLevelId + 1 << ", filename: " << levelFileNames[currLevelId] << " is invalid" << std::endl;
    errorMsgStream << e.what() << std::endl;
    // if the last level is invalid game over
    if (currLevelId == levelFileNames.size() - 1)
    {
        errorMsgStream << "This was the last level, press ENTER to end game"; 
    }
    else
    {
        errorMsgStream << "Press ENTER to load next level";
    }
    handleError(errorMsgStream.str());
}

void Game::drawHammer()
{
    // if the hammer exists on the level and player hasnt picked it up yet
    if (hammerPos != GameOptions::POS_NOT_SET && !player->isHoldingHammer())
    {
        DK_utils::drawSymbolOnScreen(Board::HAMMER, hammerPos);
        // add it to current board
        gameBoard->updateBoardWithChar(hammerPos, Board::HAMMER);
    }
}

void Game::updateLegend() const
{
    std::ostringstream scoreMsg;
    std::ostringstream livesMsg;
    scoreMsg << "Score: " << score;
    livesMsg << "Lives <3: " << lives;
    DK_utils::drawLineOnScreen(scoreMsg.str(), legendPos);
    DK_utils::drawLineOnScreen(livesMsg.str(), legendPos.oneBelow());

    // if player is holding hammer, draw a hammer symbol
    if(player->isHoldingHammer())
    {
        DK_utils::drawSymbolOnScreen(Board::HAMMER, legendPos.oneBelow().oneBelow());
    }
}

void Game::resetGhostsManager()
{
    delete ghostsManager;
    
    if (!ghostsStartPositions.empty())
    {
        ghostsManager = new GhostsManager(gameBoard);
        ghostsManager->resetGhosts(ghostsStartPositions);
    }
}

void Game::pauseGame()
{
    isPaused = true;
    Point pauseMessagePos = legendPos.oneBelow().oneBelow();
    // print pause message
    DK_utils::drawLineOnScreen(PAUSE_MESSAGE, pauseMessagePos);
}

void Game::continueGame()
{
    isPaused = false;
    //erase pause game message and restore what has been on the board 
    Point restorePos = legendPos.oneBelow().oneBelow();

    auto eraseLine = std::string(strlen(PAUSE_MESSAGE), Board::BLANK_SPACE);
    DK_utils::drawLineOnScreen(eraseLine, restorePos);
}

bool Game::moveToNextLevel()
{
    setRandSeed();
    resetIterationCounter();
    // clear the results and steps if we are recording, this is a new level
    if (recorded)
    {
        recSteps.clear();
        recResults.clear();
    }
    currLevelId++;

    return currLevelId < levelFileNames.size();
}

Board* Game::readLevelFromFile(const std::string& filename)
{
    resetEntitiesPositions();

    int screenHeight = GameOptions::SCREEN_HEIGHT, screenWidth = GameOptions::SCREEN_WIDTH;
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

            char c = static_cast<char>(levelFile.get());
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

        discardRestOfLine(levelFile);

        // if we reached eof and its not the last row
        if (levelFile.eof() && row != screenHeight - 1)
            fileEnded = true;
    }

    // save the name of whoever is missing to the string
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
    marioStartPos = GameOptions::POS_NOT_SET;
    donkeyKongPos = GameOptions::POS_NOT_SET;
    paulinePos = GameOptions::POS_NOT_SET;
    legendPos = GameOptions::POS_NOT_SET;
    hammerPos = GameOptions::POS_NOT_SET;
    ghostsStartPositions.clear();
}

bool Game::setEntityPositionByChar(char c, Point position)
{
    // return val
    bool isAddedToBoard = true;
    switch (c)
    {
    case Board::MARIO_SPRITE:
        if (marioStartPos == GameOptions::POS_NOT_SET)
            marioStartPos = position;
        // if this function returned false:
        isAddedToBoard = false; // we dont want to have the mario char on board
        break;

    case Board::DONKEY_KONG:
        if (donkeyKongPos == GameOptions::POS_NOT_SET)
            donkeyKongPos = position;
        else
            isAddedToBoard = false;
        break;

    case Board::PAULINE:
        if (paulinePos == GameOptions::POS_NOT_SET)
            paulinePos = position;
        else
            isAddedToBoard = false;
        break;

    case Board::LEGEND_CHAR:
        if (legendPos == GameOptions::POS_NOT_SET)
            legendPos = position;
        isAddedToBoard = false;
        break;
    
    case Board::GHOST:
        ghostsStartPositions.push_back({ position, Board::GHOST });
        isAddedToBoard = false;
        break;

    case Board::FILE_CLIMBING_GHOST:
        ghostsStartPositions.push_back({ position, Board::CLIMBING_GHOST });
        isAddedToBoard = false;
        break;

    case Board::HAMMER:
        if (hammerPos == GameOptions::POS_NOT_SET)
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
    int discard = levelFile.get();
    while (discard != '\n' && !levelFile.eof())
    {
        discard = levelFile.get();
    }
}

bool Game::isEntityMissing(std::string& outEntityMissing)
{
    if (marioStartPos == GameOptions::POS_NOT_SET)
    {
        outEntityMissing = "Mario";
        return true;
    }
    if (donkeyKongPos == GameOptions::POS_NOT_SET)
    {
        outEntityMissing = "Donkey Kong";
        return true;
    }
    if (paulinePos == GameOptions::POS_NOT_SET)
    {
        outEntityMissing = "Pauline";
        return true;
    }
    if (legendPos == GameOptions::POS_NOT_SET)
    {
        outEntityMissing = "Legend";
        return true;
    }

    return false;
}


void Game::checkPlayerHitEnemy()
{
    // get the position that the player wants to destroy
    Point destroyPos = player->handleHammer();

    if (destroyPos != GameOptions::POS_NOT_SET)
    {
        // if its a barrel
        if (gameBoard->getCharAtPos(destroyPos) == Board::BARREL)
        {
            barrelManager->destroyBarrelAtPos(destroyPos);
        }
        // if its a ghost
        if (gameBoard->getCharAtPos(destroyPos) == Board::GHOST 
            || gameBoard->getCharAtPos(destroyPos) == Board::CLIMBING_GHOST)
        {
            ghostsManager->destroyGhostAtPos(destroyPos);
        }

        hitScoreAnimation(destroyPos.oneAbove());
        score += ENEMY_SCORE_AMOUNT;
    }
}

void Game::hitScoreAnimation(Point position)
{
    std::string msg = "+" + std::to_string(ENEMY_SCORE_AMOUNT);
    DK_utils::drawLineOnScreen(msg, position);
    Sleep(GameOptions::getRefreshRate());
    // erase the line we just drew
    for (size_t i = 0; i < msg.size(); i++)
    {
        DK_utils::drawSymbolOnScreen(gameBoard->getCharAtPos(position), position);
        position = position.oneRight();
    }
}

Game::KeyInput Game::getInputKeys()
{
    KeyInput input;

    if (_kbhit())
    {
        input.key1 = static_cast<char>(_getch());
        
        if (_kbhit())
            input.key2 = static_cast<char>(_getch());
    }

    return input;
}

bool Game::start()
{
    if(levelFileNames.size() == 0)
    {
        std::ostringstream errorMsgStream;
        errorMsgStream << "No levels for the game to load, check: " << DK_utils::getWorkingDirectoryStr() + GameOptions::LEVELS_PATH
            << " for level files" << std::endl << "Press ENTER to go back to main menu";
        handleError(errorMsgStream.str());
        return true;
    }

    setRandSeed();
    // iterate until we`ve read all files
    while(hasMoreLevels())
    {
        std::string nextLevelFilename = levelFileNames[currLevelId];

        delete gameBoard;
        try        
        {
            gameBoard = readLevelFromFile(nextLevelFilename);
        }
        catch (LevelFileException& e)
        {
            displayLevelException(e);
            
            if (currLevelId == levelFileNames.size() - 1)
                return true;

            moveToNextLevel();
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
    DK_utils::clearScreen();

    gameBoard->resetBoard();
    
    if(hammerPos != GameOptions::POS_NOT_SET)
    {
        gameBoard->updateBoardWithChar(hammerPos, Board::HAMMER);
    }

    gameBoard->print();

    //need to clear input buffer after animation  
    DK_utils::flushInputBuffer();

    // reset player and barrel manager
    delete player;
    player = new Player(gameBoard, Board::MARIO_SPRITE, marioStartPos);
    delete barrelManager;
    barrelManager = new BarrelManager(gameBoard, donkeyKongPos);
    
    resetGhostsManager();

    updateLegend();
}
