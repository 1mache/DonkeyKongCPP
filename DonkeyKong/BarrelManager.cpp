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
        // roll direction has 2 values (index 0 or 1), and 1-direction gives the opposite value 
        curBarrelDir = Barrel::RollDirection(1 - curBarrelDir);
        spawnBarrel();
        frameCounter = getRandomDelay();
    }

    moveAllBarrels();
    frameCounter--;
}
