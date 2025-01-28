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
        ghost = std::make_unique<ClimbingGhost>(gameBoard, pos);
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

//Ghost* GhostsManager::findGhostByPosition(Point position)
//{
//    for (const auto& ghost : ghostsVector)
//    {
//        if (ghost->getPosition() == position)
//        {
//            return ghost.get();
//        }
//    }
//
//    return nullptr;
//}

void GhostsManager::manageGhosts()
{
    for (const auto& ghost : ghostsVector)
    {
        //Ghost* other = nullptr;
        //// case: xx they are close together
        //if(ghost->reachedAnotherGhost())
        //{
        //    other = findGhostByPosition(ghost->getPosition() + ghost->getDirection());
        //}

        ghost->update();

        //// case: x x, after we updated it also becomes xx
        //if(ghost->reachedAnotherGhost())
        //{
        //    other = findGhostByPosition(ghost->getPosition() + ghost->getDirection());
        //}

        //if(other)
        //{
        //    // if they are moving one towards another
        //    if ((other->getDirection() + ghost->getDirection()) == Constants::POINT_ZERO)
        //    {
        //        // change the directions of both
        //        ghost->changeHorizontalDirection();
        //        other->changeHorizontalDirection();
        //    }
        //}
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
    // empty the current ghosts vector, and then refill it with the start positions of each ghost
    ghostsVector.clear();
    ghostsVector.shrink_to_fit();

    for (std::pair<Point, char > pair : startPositions)
    {
        // spawn the ghost if there is a floor beneath him
        if(gameBoard->isObstacleAtPos(pair.first.oneBelow()))
            spawnGhost(pair.first, pair.second);
    }
}
