#pragma once

#include "Point.h"
#include "MovingObject.h"
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

    std::vector<Point> ghostsStartPosVector;

    bool spawnedGhosts = false;
    //size_t ghostsNum = 0;

    //void spawnAllGhosts();

    void deleteGhost(int index)
    {
        //deletes the ghost from the ghosts vector
        ghostsVector.erase(ghostsVector.begin() + index);
    }

public:
    GhostsManager(Board* _gameBoard) : gameBoard(_gameBoard) {}

    // updates all existing barrels, and spawns new ones
    void manageGhosts();

    void destroyGhostAtPos(Point destroyPos);

    void spawnGhost(Point pos);

    void resetGhosts();
};
