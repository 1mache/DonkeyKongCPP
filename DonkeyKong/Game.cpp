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
                player.stateByKey(key);
            }
        }
        
        if (!isPaused)
        {
            player.movePlayer();

            //check for barrel collisions and fall damage
            if (player.checkCollision() || player.checkFallDamage())
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

            barrelManager.manageBarrels();
            ghostsManager.manageGhosts();

            //check again for barrel collisions - after barrels moved
            if (player.checkCollision())
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
            if(gameBoard.isPaulineAtPos(player.getPosition()))
            {
                break; // player reach pauline, exit loop 
            }
        }

        Sleep(Constants::GAME_REFRESH_RATE);
    }
}

bool Game::handleStrike()
{
    player.takeDamage();
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
        std::cout << gameBoard.getCharAtPos(restorePos);
        restorePos = restorePos.oneRight();
    }
}

bool Game::start()
{
    gameBoard.resetBoard();
    gameBoard.print();
    updateLivesCounter();

    //need to clear input buffer after animation 
    flushInputBuffer();
    update();

    // returns true if game is over
    return (lives == 0);
}

void Game::resetLevel()
{
    clearScreen();

    gameBoard.resetBoard();
    gameBoard.print();
    updateLivesCounter();

    //need to clear input buffer after animation  
    flushInputBuffer();

    // reset player and barrel manager
    player = Player(&gameBoard, MARIO_SPRITE, MARIO_START_POS);
    barrelManager = BarrelManager(&gameBoard, DONKEY_KONG_POS);
}