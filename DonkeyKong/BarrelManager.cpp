#include "BarrelManager.h"

void BarrelManager::spawnBarrel()
{   

    //                          barrel constructor 
    barrelsVector.emplace_back(gameBoard, gameBoard->BARREL, spawnerPosition + DIRECTIONS[curBarrelDir], DIRECTIONS[curBarrelDir]);
}

void BarrelManager::destroyBarrel(int index)
{
    barrelsVector.erase(barrelsVector.begin() + index);
}

void BarrelManager::moveAllBarrels()
{
    //move barrels every other frame so that they are slower than mario 
    /*if(frameCounter % 2 == 0)*/
    {
        for (size_t i = 0; i < barrelsVector.size(); i++)
        {
            if (barrelsVector[i].exploded())
            {
                barrelsVector[i].update();
                destroyBarrel(i);
            }
            
            if(!barrelsVector.empty())
            {
                barrelsVector[i].update();
            }
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
