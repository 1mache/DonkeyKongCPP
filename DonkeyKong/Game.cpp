#include "Game.h"

bool Game::start()
{
    gameBoard.reset();
    gameBoard.print();

    flushInputBuffer();
    update();

    return gameOver;
}

void Game::resetLevel()
{
    clearScreen();

    gameBoard.reset();
    gameBoard.print();
    flushInputBuffer();

    player = Player(&gameBoard, MARIO_SPRITE, MARIO_START_POS);
    barrelManager = BarrelManager(&gameBoard, DONKEY_KONG_POS);
}

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
            if (player.checkCollision()
                || player.checkFallDamage())
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
                break;
            }
        }

        Sleep(Constants::GAME_REFRESH_RATE);
    }
}

bool Game::handleStrike()
{
    player.takeDamage();
    lives--;
    //*updtate health UI*()

    if (lives == 0)
    {
        gameOver = true;
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
    gotoxy(PAUSEMESSAGE_POS.getX(), PAUSEMESSAGE_POS.getY());
    std::cout << PAUSE_MESSAGE;
}

void Game::continueGame()
{
    isPaused = false;
    //erase pause game message and restore what has been on the board 
    Point restorePos = PAUSEMESSAGE_POS;
    for (int i = 0; i < strlen(PAUSE_MESSAGE); i++)
    {
        gotoxy(restorePos.getX(), restorePos.getY());
        std::cout << gameBoard.getCharAtPos(restorePos);
        restorePos = restorePos.oneRight();
    }
}