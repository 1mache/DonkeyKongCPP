#include "GhostsManager.h"

void GhostsManager::manageGhosts()
{
    if (!spawnedGhosts)
    {
        spawnAllGhosts();
        spawnedGhosts = true;
    }

    else
    {
        for (size_t i = 0; i < ghostsNum; i++)
        {
            ghostsVector[i].moveGhost();
        }
    }
}
