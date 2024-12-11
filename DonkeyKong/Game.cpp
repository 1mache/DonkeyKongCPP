#include "Game.h"

void Game::startGame()
{
    ShowConsoleCursor(false);
    //================================MENU==========================
    // this loop returns us to the main menu after a win/ gameOver
    while(true)
    {
        Menu menu;

        //menu.start returns 1 if the user chose the exit option in the menu
        bool exitflag = menu.displayMainMenu();
        if (exitflag)
        {
            break;
        }

        gameBoard.reset();
        gameBoard.print();


        update();

        if (gameOver)
        {
            menu.displayGameOver();
            gameOver = false;
        }
        else
        {
            menu.displayWinScreen();
        }

        player = Player(&gameBoard, MARIO_SPRITE, START_POS);
    }   

    //TEST===================================================================
    //int frameCounter = 0;
    //Movement some = Movement(&gameBoard, '*', { 1, 6 });
}

void Game::update()
{
    // QUESTION =================================
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
        
        if(!isPaused)
        {
            player.movePlayer();

            //game over check
            if (player.getLives() == 0)
            {
                clearScreen();
                gameOver = true;
                break;
            }

            //win check
            if(gameBoard.isPaulineAtPos(player.getPosition()))
            {
                clearScreen();
                break;
            }
        }
        //TEST=====================================================================
        //frameCounter++;
        ////move the other object every second frame
        //if(frameCounter % 2 == 0)
        //  some.move(1, 0, false);

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
    //erase pause game message  
    for (int i = 0; i < strlen(PAUSE_MESSAGE); i++)
    {
        gotoxy(PAUSEMESSAGE_POS.getX() + i, PAUSEMESSAGE_POS.getY());
        std::cout << ' ';
    }
}