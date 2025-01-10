#include "GhostsManager.h"

void GhostsManager::manageGhosts()
{
    for (size_t i = 0; i < ghostsVector.size(); i++)
    {
        ghostsVector[i].update();
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
