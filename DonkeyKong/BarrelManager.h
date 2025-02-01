#pragma once

#include <vector>
#include <cstdlib>

#include "Point.h"
#include "MovingObject.h"
#include "GameOptions.h"
#include "Barrel.h"
#include "Board.h"

class BarrelManager
{
    static constexpr int MIN_SPAWN_DELAY = 20;
    static constexpr int MAX_SPAWN_DELAY = 60;

    // our spawner is donkey kong
    Point spawnerPosition;
    int frameCounter = 0;

    // which way to push the next created barrel
    Barrel::RollDirection curBarrelDir = Barrel::RollDirection::RIGHT;

    Board* gameBoard = nullptr;
    std::vector<Barrel> barrelsVector;

    void spawnBarrel()
    {
        Point barrelSpawnPos = spawnerPosition + Barrel::DIRECTIONS[curBarrelDir];
        // barrel constructor, creates barrel in the vector 
        barrelsVector.emplace_back(gameBoard, barrelSpawnPos, curBarrelDir);
        gameBoard->updateBoardWithChar(barrelSpawnPos, Board::BARREL);
    }

    void deleteBarrel(int index);
    
    void updateAllBarrels();

    // gives "random" spawn delay for barrels
    int getRandomDelay() const
    {
        // its the same every run
        // it will be between MAX_SPAWN_DELAY and MIN_SPAWN_DELAY
        return ((rand() % (MAX_SPAWN_DELAY + 1 - MIN_SPAWN_DELAY)) + MIN_SPAWN_DELAY); 
    }

public:
    BarrelManager(Board* _gameBoard, Point _spawnerPos) : spawnerPosition(_spawnerPos), gameBoard(_gameBoard) {}

    // updates all existing barrels, and spawns new ones
    void manageBarrels();

    void destroyBarrelAtPos(Point destroyPos);
};