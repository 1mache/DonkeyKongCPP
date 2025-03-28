#include "BarrelManager.h"

void BarrelManager::deleteBarrel(int index)
{
    gameBoard->resetCharAtPos(barrelsVector[index].getPosition());
    // erase it from the screen
    barrelsVector[index].erase();
    //deletes the barrel from the barrel vector
    barrelsVector.erase(barrelsVector.begin() + index);
}

void BarrelManager::updateAllBarrels()
{
    for (size_t i = 0; i < barrelsVector.size(); i++)
    {
        // if the current barrel exploded
        if (barrelsVector[i].exploded())
        {
            // the barrel needs one last update to erase the explosion
            barrelsVector[i].update();
            // then delete it
            deleteBarrel(i);
        }
                              // if we erased the last barrel we need to check that i is still in bounds
        if(!barrelsVector.empty() && (i < barrelsVector.size()))
        {
            barrelsVector[i].update();
        }
    }
}

void BarrelManager::manageBarrels()
{
    if (frameCounter <= 0)
    {
        spawnBarrel();
        
        // roll direction has 2 values (index 0 or 1), and 1-direction gives the opposite value 
        curBarrelDir = Barrel::RollDirection(1 - curBarrelDir);
        frameCounter = getRandomDelay();
    }

    updateAllBarrels();
    frameCounter--;
}

void BarrelManager::destroyBarrelAtPos(Point destroyPos)
{
    for (size_t i = 0; i < barrelsVector.size(); i++)
    {
        if (barrelsVector[i].getPosition() == destroyPos)
        {
            deleteBarrel(i);
            break;
        }
    }
}
