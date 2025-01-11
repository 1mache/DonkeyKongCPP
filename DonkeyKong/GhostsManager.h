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
    Board* gameBoard = nullptr;
    std::vector<Ghost> ghostsVector;

    bool spawnedGhosts = false;

    void spawnGhost(Point pos)
    {
        ghostsVector.emplace_back(gameBoard, pos);
    }

    void deleteGhost(int index)
    {
        //deletes the ghost from the ghosts vector
        gameBoard->resetCharAtPos(ghostsVector[index].getPosition());
        ghostsVector.erase(ghostsVector.begin() + index);
    }

public:
    GhostsManager(Board* _gameBoard) : gameBoard(_gameBoard) {}

    void manageGhosts();

    void destroyGhostAtPos(Point destroyPos);

    void resetGhosts(const std::vector<Point>& startPositions);
};
