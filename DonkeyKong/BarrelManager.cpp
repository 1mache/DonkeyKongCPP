#include "BarrelManager.h"

void BarrelManager::spawnBarrel()
{   //                          barrel constructor 
    barrelsVector.emplace_back(gameBoard, gameBoard->BARREL, spawnPosition + DIRECTIONS[curBarrelDir], curBarrelDir);
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
        if (spawnToRight)
        {
            curBarrelDir = RollDirection::RIGHT;
        }
        else
        {
            curBarrelDir = RollDirection::LEFT;
        }
        spawnBarrel();
        frameCounter = getRandomDelay();

        spawnToRight = !spawnToRight;
    }

    moveAllBarrels();
    frameCounter--;
}
