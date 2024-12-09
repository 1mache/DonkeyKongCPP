#include "Game.h"

void Game::startGame()
{
    ShowConsoleCursor(false);
    
    Menu menu;

    menu.start();

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

        //TEST=====================================================================
        //frameCounter++;
        ////move the other object every second frame
        //if(frameCounter % 2 == 0)
        //  some.move(1, 0, false);
        Sleep(65);
    }
}
