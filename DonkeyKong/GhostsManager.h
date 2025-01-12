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

    // adds a new ghost to the vector and places it on board
    void spawnGhost(Point pos)
    {
        ghostsVector.emplace_back(gameBoard, pos);
        gameBoard->updateBoardWithChar(pos, Board::GHOST);
    }

    // deletes ghost at given index from vector, board and screen
    void deleteGhost(int index);

    // finds ghost that is at a given position
    Ghost* findByPosition(Point position);

public:
    GhostsManager(Board* _gameBoard) : gameBoard(_gameBoard) {}

    // moves all of the ghosts and hadles them meeting one another
    void manageGhosts();

    // deletes ghost in the give position (if there is a ghost there)
    void destroyGhostAtPos(Point destroyPos);

    // spawns all the ghosts given their start positions
    void resetGhosts(const std::vector<Point>& startPositions);
};
