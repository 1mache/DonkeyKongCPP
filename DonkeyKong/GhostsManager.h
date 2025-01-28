#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "Constants.h"
#include <vector>
#include "Ghost.h"
#include "ClimbingGhost.h"
#include "Board.h"
#include <cstdlib>

//class Ghost; // forward declaration

class GhostsManager
{
    Board* gameBoard = nullptr;
    std::vector<std::unique_ptr<Ghost>> ghostsVector;

    // adds a new ghost to the vector and places it on board
    void spawnGhost(Point pos, char ghostChar);

    // deletes ghost at given index from vector, board and screen
    void deleteGhost(int index);

public:
    GhostsManager(Board* _gameBoard) : gameBoard(_gameBoard) {}

    // finds ghost that is at a given position
    //Ghost* findGhostByPosition(Point position);

    // moves all of the ghosts and hadles them meeting one another
    void manageGhosts();

    // deletes ghost in the given position (if there is a ghost there)
    void destroyGhostAtPos(Point destroyPos);

    // spawns all the ghosts given their start positions
    void resetGhosts(const std::vector<std::pair<Point, char>>& startPositions);
};
