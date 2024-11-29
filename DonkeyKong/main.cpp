#include <iostream>
#include <windows.h>
#include <conio.h>

#include "utils.h"
#include "Board.h"
#include "Player.h"

constexpr int ESC = 27;

int main(int argc, char* argv[]) 
{
    Board gameBoard;
    gameBoard.reset();
    gameBoard.print();

    Movement playerMovement = Movement(&gameBoard, '@', { 2,22 });
    Player mario = Player(playerMovement, 3);
    
    ShowConsoleCursor(false);

    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == ESC) break;
            mario.stateByKey(key);
        }

        mario.movePlayer();
        Sleep(50);
    }
}