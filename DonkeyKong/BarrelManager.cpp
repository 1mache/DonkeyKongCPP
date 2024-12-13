#include "BarrelManager.h"

void BarrelManager::spawnBarrel()
{   //                          barrel constructor 
    barrelsVector.emplace_back(gameBoard, BARREL_CHAR, dkPosition + DIRECTIONS[curBarrelDir], curBarrelDir);
}

void BarrelManager::destroyBarrel(int index)
{
    barrelsVector[index].explode();
    barrelsVector.erase(barrelsVector.begin() + index);
}

void BarrelManager::moveAllBarrels()
{
    for (size_t i = 0; i < barrelsVector.size(); i++)
    {
        if (barrelsVector[i].needsToExplode())
        {
            destroyBarrel(i);
        }

        barrelsVector[i].moveBarrel();
    }
}

void BarrelManager::manageBarrels()
{
    if (frameCounter <= 0)
    {
        spawnBarrel();
        frameCounter = SPAWN_DELAY;
    }

    moveAllBarrels();

    frameCounter--;
}
