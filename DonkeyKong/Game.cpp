#include "Game.h"

void Game::startGame()
{
	gameBoard.reset();
	gameBoard.print();

    ShowConsoleCursor(false);
    update();
    //DEBUG===================================================================
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

        //DEBUG=====================================================================
        //frameCounter++;
        ////move the other object every second frame
        //if(frameCounter % 2 == 0)
        //  some.move(1, 0, false);
        Sleep(65);
    }
}
