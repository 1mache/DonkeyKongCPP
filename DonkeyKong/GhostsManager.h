#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "GameOptions.h"
#include <vector>
#include "Ghost.h"
#include "ClimbingGhost.h"
#include "Board.h"
#include <cstdlib>

class GhostsManager
{
    Board* gameBoard = nullptr;
    std::vector<std::unique_ptr<Ghost>> ghostsVector;

    // adds a new ghost to the vector and places it on board
    void spawnGhost(Point pos, char ghostChar);

    // deletes ghost at given index from vector, board and screen
    void deleteGhost(size_t index);

public:
    GhostsManager(Board* _gameBoard) : gameBoard(_gameBoard) {}

    // moves all of the ghosts
    void manageGhosts();

    // deletes ghost in the given position (if there is a ghost there)
    void destroyGhostAtPos(Point destroyPos);

    // spawns all the ghosts given their start position and type (regular or climbing)
    void resetGhosts(const std::vector<std::pair<Point, char>>& startPositions);
};
