#include "DonkeyKong.h"

void DonkeyKong::spawnBarrel()
{   //                          barrel constructor 
    barrelsVector.emplace_back(gameBoard, BARREL_CHAR, dkPosition + DIRECTIONS[curBarrelDir], curBarrelDir);
}

void DonkeyKong::destroyBarrel(int index)
{
    barrelsVector.erase(barrelsVector.begin() + index);
}

void DonkeyKong::moveAllBarrels()
{
    for (size_t i = 0; i < barrelsVector.size(); i++)
    {
        if (barrelsVector[i].checkExploded())
        {
            destroyBarrel(i);
        }

        barrelsVector[i].moveBarrel();
    }
}

void DonkeyKong::barrelsManager()
{
    if (frameCounter <= 0)
    {
        spawnBarrel();
        frameCounter = SPAWN_DELAY;
    }

    moveAllBarrels();
    
    frameCounter--;
}




