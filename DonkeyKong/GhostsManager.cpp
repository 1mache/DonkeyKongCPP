#include "GhostsManager.h"

void GhostsManager::deleteGhost(int index)
{
    gameBoard->resetCharAtPos(ghostsVector[index].getPosition());
    // erases it from the screen
    ghostsVector[index].erase();
    //deletes the ghost from the ghosts vector
    ghostsVector.erase(ghostsVector.begin() + index);
}

Ghost* GhostsManager::findByPosition(Point position)
{
    for (Ghost& ghost : ghostsVector)
    {
        if (ghost.getPosition() == position)
            return &ghost;
    }

    return nullptr;
}

void GhostsManager::manageGhosts()
{
    for (Ghost& ghost : ghostsVector)
    {
        Ghost* other = nullptr;
        // case: xx they are close together
        if(ghost.reachedAnotherGhost())
        {
            other = findByPosition(ghost.getPosition() + ghost.getDirection());
        }
        ghost.update();
        // case: x x, after we updated it also becomes xx
        if(ghost.reachedAnotherGhost())
        {
            other = findByPosition(ghost.getPosition() + ghost.getDirection());
        }

        if(other)
        {
            // if they are moving one towards another
            if ((other->getDirection() + ghost.getDirection()) == Constants::POINT_ZERO)
            {
                // change the directions of both
                ghost.changeDirection();
                other->changeDirection();
            }
        }
    }
}

void GhostsManager::destroyGhostAtPos(Point destroyPos)
{
    for (size_t i = 0; i < ghostsVector.size(); i++)
    {
        if (ghostsVector[i].getPosition() == destroyPos)
        {
            deleteGhost(i);
            break;
        }
    }
}

void GhostsManager::resetGhosts(const std::vector<Point>& startPositions)
{
    // empty the current ghosts vector, and then refill it with the start positions of each ghost
    ghostsVector.clear();
    ghostsVector.shrink_to_fit();

    for (Point pos : startPositions)
    {
        spawnGhost(pos);
    }
}
