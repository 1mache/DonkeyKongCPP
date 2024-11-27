#include <iostream>
#include <windows.h>
#include <conio.h>

#include "utils.h"
#include "Board.h"
#include "Game.h"
#include "Player.h"

constexpr int ESC = 27;

int main(int argc, char* argv[]) 
{
    Player mario;
    mario.startPlayer('@', 0, 0);
    
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