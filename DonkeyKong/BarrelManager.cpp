#include "BarrelManager.h"

int BarrelManager::randomizeBarrelSpawnTime()
{
    srand(time(NULL));

    return rand() % 20 + SPAWN_DELAY;
}

void BarrelManager::spawnBarrel()
{   //                          barrel constructor 
    barrelsVector.emplace_back(gameBoard, gameBoard->BARREL, dkPosition + DIRECTIONS[curBarrelDir], curBarrelDir);
}

void BarrelManager::destroyBarrel(int index)
{
    barrelsVector[index].explode();
    barrelsVector.erase(barrelsVector.begin() + index);
}

void BarrelManager::moveAllBarrels()
{
    //move barrels every other frame so that they are slower than mario 
    if(frameCounter % 2 == 0)
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
}

void BarrelManager::manageBarrels()
{
    if (frameCounter <= 0)
    {
        spawnBarrel();
        frameCounter = randomizeBarrelSpawnTime();
    }

    moveAllBarrels();

    frameCounter--;
}
