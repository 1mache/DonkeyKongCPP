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
    // QUESTION =================================
    // KEEP THE VARIABLE OR JUST WHILE TRUE
    while (!gameOver)
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
            if (gameBoard.getCharAtPos(player.getPosition()) == BARREL_SPRITE
                || player.checkFallDamage())
            {
                player.takeDamage();
                lives--;
                //*updtate health UI*()

                if (lives == 0)
                {
                    gameOver = true;
                    break;
                }
                else
                {
                    resetLevel();
                    continue;
                }
            }

            barrelManager.manageBarrels();


            // if we want delay, we need to the split the manageBarrels to 2 functions with loops. One that spawns every delay, and one that checks hits every frame
            
            //if (delayCounter <= 0)
            //{
            //    // Spawn function here

            //    delayCounter = barrelsDelayAmount;
            //}
            //delayCounter--;


            //win check
            if(gameBoard.isPaulineAtPos(player.getPosition()))
            {
                break;
            }
        }

        Sleep(Constants::GAME_REFRESH_RATE);
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