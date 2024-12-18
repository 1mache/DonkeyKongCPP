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
                if (!isPaused) pauseGame();
                else continueGame();
            }
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
    gameBoard.reset();
    gameBoard.print();
    updateLivesCounter();

    flushInputBuffer();
    update();

    return (lives == 0);
}

void Game::resetLevel()
{
    clearScreen();

    gameBoard.reset();
    gameBoard.print();
    updateLivesCounter();

    // for explanation of this function see: Menu.print()
    flushInputBuffer();

    player = Player(&gameBoard, MARIO_SPRITE, MARIO_START_POS);
    barrelManager = BarrelManager(&gameBoard, DONKEY_KONG_POS);
}