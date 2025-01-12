#include "GhostsManager.h"

void GhostsManager::deleteGhost(int index)
{
    gameBoard->resetCharAtPos(ghostsVector[index].getPosition());
    // erases it from the screen
    ghostsVector[index].erase();
    //deletes the ghost from the ghosts vector
    ghostsVector.erase(ghostsVector.begin() + index);
}

Ghost* GhostsManager::findOther(Point position)
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
/*    for (size_t i = 0; i < ghostsVector.size(); i++)
    {
        ghostsVector[i].setGhostDirection();
    }*/    
    for (Ghost& ghost : ghostsVector)
    {
        Ghost* other = nullptr;
        // case: xx
        if(ghost.reachedAnotherGhost())
        {
            other = findOther(ghost.getPosition() + ghost.getGhostDirection());
        }
        ghost.update();
        // case: x x
        if(ghost.reachedAnotherGhost())
        {
            other = findOther(ghost.getPosition() + ghost.getGhostDirection());
        }

        if(other)
        {
            // if they are moving one towards another
            if ((other->getGhostDirection() + ghost.getGhostDirection()) == Point(0, 0))
            {
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
