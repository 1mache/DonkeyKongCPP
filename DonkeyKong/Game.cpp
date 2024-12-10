#include "Game.h"

void Game::startGame()
{
    ShowConsoleCursor(false);
    //================================MENU==========================
    //Menu menu;

    ////menu.start returns 1 if the user chose the exit option in the menu
    //bool exitFlag = menu.start();
    //if (exitFlag)
    //{
    //    return;
    //}

	gameBoard.reset();
	gameBoard.print();


    update();
    //TEST===================================================================
    //int frameCounter = 0;
    //Movement some = Movement(&gameBoard, '*', { 1, 6 });
}

void Game::update()
{
    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == ESC) break;
            player.stateByKey(key);
        }

        player.movePlayer();

        if(player.getLives() == 0)
        {
            clearScreen();
            break;
        }
        //TEST=====================================================================
        //frameCounter++;
        ////move the other object every second frame
        //if(frameCounter % 2 == 0)
        //  some.move(1, 0, false);

        Sleep(Constants::REFRESH_RATE);
    }
}
