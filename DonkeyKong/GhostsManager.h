#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"
#include <vector>
#include "Ghost.h"
#include "Board.h"
#include <cstdlib>

class GhostsManager
{
    /*static constexpr int MIN_SPAWN_DELAY = 20;
    static constexpr int MAX_SPAWN_DELAY = 60;*/

    // which way to push the next created barrel
    //Barrel::RollDirection curBarrelDir = Barrel::RollDirection::RIGHT;

    Board* gameBoard = nullptr;
    std::vector<Ghost> ghostsVector;

    bool spawnedGhosts = false;
    size_t ghostsNum = 0;

    void spawnAllGhosts()
    {
        // check each char in the board if it's a ghost
        for (int y = 0; y < Constants::SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < Constants::SCREEN_WIDTH; x++)
            {
                Point curPosition = { x, y };

                if (gameBoard->getCharAtPos(curPosition) == gameBoard->GHOST)
                {
                    // erase original ghost in board
                    gotoScreenPos(curPosition);
                    gameBoard->updateCurrentBoardWithChar(curPosition, ' ');
                    std::cout << ' ';

                    // ghost constructor, creates ghost in the vector 
                    ghostsVector.emplace_back(gameBoard, curPosition);
                    ghostsNum += 1;
                }
            }
        }
    }

public:
    GhostsManager(Board* _gameBoard) : gameBoard(_gameBoard) {}

    // updates all existing barrels, and spawns new ones
    void manageGhosts();
};
