#include "DonkeyKong.h"

void DonkeyKong::spawnBarrel()
{
    barrelsVector.emplace_back(gameBoard, barrelChar, dkPosition + DIRECTIONS[curBarrelDir], curBarrelDir);
}

void DonkeyKong::destroyBarrel(int index)
{
    barrelsVector.emplace_back(gameBoard, barrelChar, dkPosition + DIRECTIONS[curBarrelDir], curBarrelDir);
}

void DonkeyKong::moveAllBarrels()
{
    for (size_t i = 0; i < barrelsVector.size(); i++)
    {
        barrelsVector[i].moveBarrel();

        if (barrelsVector[i].checkExploded())
        {
            barrelsVector.erase(barrelsVector.begin() + i);
        }
    }
}

void DonkeyKong::barrelsManager()
{
    if (frameCounter <= 0)
    {
        spawnBarrel();
        frameCounter = spawnDelay;
    }

    moveAllBarrels();
    
    frameCounter--;
}




