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

bool Game::readLevelFromFile()
{
    int screenHeight = Constants::SCREEN_HEIGHT, screenWidth = Constants::SCREEN_WIDTH;
    // set ghost start positions

    char (*map)[Constants::SCREEN_HEIGHT][Constants::SCREEN_WIDTH + 1] = new char[1][Constants::SCREEN_HEIGHT][Constants::SCREEN_WIDTH + 1];
    
    ifstream levelFile("dkong_01.screen", std::ios_base::in);
    //vs
    //ifstream levelFile("dkong_01.screen"); (ASK AMIR) ===========================

    if(!levelFile.is_open())
    {
        //let the player know there is an issue with a the level files.
        return false;
    }

    for (int row = 0; row < screenHeight; row++)
    {
        for (int col = 0; col < screenWidth; col++)
        {
            char c = levelFile.get();
            switch (c)
            {
            // add case for ghosts
            case MARIO_SPRITE:
                marioStartPos = {col, row};
                (*map)[row][col] = ' ';
                continue; // we dont want to have the mario char on board, skip to next iteration
                
            case Board::DONKEY_KONG:
                donkeyKongPos = {col, row};
                break;

            case Board::PAULINE:
                paulinePos = {col, row};
                break;
            
            case EOF: 
                return false; // file ended before we read the entire dimensions of the level
            default:
                break;
            }
            
            (*map)[row][col] = c;
        }

        levelFile.ignore(1); // ignore newline char '\n' at the end of a line
        (*map)[row][screenWidth] = '\0'; // terminate the lines that we read
    }

    if (marioStartPos == POS_NOT_SET || donkeyKongPos == POS_NOT_SET ||
        paulinePos == POS_NOT_SET)
    {
        //there were no info on the positions essential for the game in the file
        return false;
    }

    gameBoard = new Board(map);
    
    return true;
}

bool Game::start()
{
    bool levelReadSuccess = readLevelFromFile();

    if(!levelReadSuccess)
    {
        // throw the biggest fucking exception!!!!!
        std::cout << "Yo something wrong with the level!!!!!!!" << std::endl;
        return false;
    }

    resetLevel();
    
    update();

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