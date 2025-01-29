#include "GhostsManager.h"

void GhostsManager::spawnGhost(Point pos, char ghostChar)
{
    std::unique_ptr<Ghost> ghost;

    if (ghostChar == Board::GHOST)
    {
        ghost = std::make_unique<Ghost>(gameBoard, pos, ghostChar);
    }

    else if (ghostChar == Board::CLIMBING_GHOST)
    {
        ghost = std::make_unique<ClimbingGhost>(gameBoard, pos, ghostChar);
    }

    ghostsVector.push_back(std::move(ghost));
    gameBoard->updateBoardWithChar(pos, ghostChar);
}

void GhostsManager::deleteGhost(int index)
{
    gameBoard->resetCharAtPos(ghostsVector[index]->getPosition());
    // erases it from the screen
    ghostsVector[index]->erase();
    //deletes the ghost from the ghosts vector
    ghostsVector.erase(ghostsVector.begin() + index);
}

void GhostsManager::manageGhosts()
{
    for (const auto& ghost : ghostsVector)
    {
        ghost->update();
    }
}

void GhostsManager::destroyGhostAtPos(Point destroyPos)
{
    for (size_t i = 0; i < ghostsVector.size(); i++)
    {
        if (ghostsVector[i]->getPosition() == destroyPos)
        {
            deleteGhost(i);
            break;
        }
    }
}

void GhostsManager::resetGhosts(const std::vector<std::pair<Point, char>>& startPositions)
{
    // empty the current ghosts vector, and then refill it according to the start position and type of each ghost
    ghostsVector.clear();
    ghostsVector.shrink_to_fit();

    for (std::pair<Point, char > pair : startPositions)
    {
        // spawn the ghost if there is a floor beneath him
        if(gameBoard->isObstacleAtPos(pair.first.oneBelow()))
            spawnGhost(pair.first, pair.second);
    }
}
