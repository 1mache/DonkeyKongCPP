#include "BarrelManager.h"

void BarrelManager::moveAllBarrels()
{
    for (size_t i = 0; i < barrelsVector.size(); i++)
    {
        if (barrelsVector[i].exploded())
        {
            barrelsVector[i].update();
            deleteBarrel(i);
        }
            
        if(!barrelsVector.empty())
        {
            barrelsVector[i].update();
        }
    }
}

void BarrelManager::manageBarrels()
{
    if (frameCounter <= 0)
    {
        if (spawnToRight)
        {
            curBarrelDir = SpawnDirection::RIGHT;
        }
        else
        {
            curBarrelDir = SpawnDirection::LEFT;
        }
        spawnBarrel();
        frameCounter = getRandomDelay();

        spawnToRight = !spawnToRight;
    }

    moveAllBarrels();
    frameCounter--;
}
