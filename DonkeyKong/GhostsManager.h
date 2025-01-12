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

    void spawnGhost(Point pos)
    {
        ghostsVector.emplace_back(gameBoard, pos);
        gameBoard->updateBoardWithChar(pos, Board::GHOST);
    }

    void deleteGhost(int index);

    Ghost* findOther(Point position);

public:
    GhostsManager(Board* _gameBoard) : gameBoard(_gameBoard) {}

    void manageGhosts();

    void destroyGhostAtPos(Point destroyPos);

    void resetGhosts(const std::vector<Point>& startPositions);
};
