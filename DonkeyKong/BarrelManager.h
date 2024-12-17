#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"
#include <vector>
#include "Barrel.h"
#include "Board.h"
#include <cstdlib>

class BarrelManager
{
    static constexpr int MIN_SPAWN_DELAY = 20;
    static constexpr int MAX_SPAWN_DELAY = 60;

    Point spawnerPosition;
    int frameCounter = 0;
    bool spawnToRight = true;

    enum SpawnDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

    SpawnDirection curBarrelDir = SpawnDirection::RIGHT;

    Board* gameBoard = nullptr;
    std::vector<Barrel> barrelsVector;

    void spawnBarrel()
    {
        // barrel constructor, creates barrel in the vector 
        barrelsVector.emplace_back(gameBoard, gameBoard->BARREL, spawnerPosition + DIRECTIONS[curBarrelDir], DIRECTIONS[curBarrelDir]);
    }

    void deleteBarrel(int index)
    {
        //deletes the barrel from the barrel vector
        barrelsVector.erase(barrelsVector.begin() + index);
    }

    void moveAllBarrels();

    int getRandomDelay() 
    { 
        return ((rand() % (MAX_SPAWN_DELAY + 1 - MIN_SPAWN_DELAY)) + MIN_SPAWN_DELAY); 
    }

public:
    BarrelManager(Board* _gameBoard, Point _spawnerPos) : spawnerPosition(_spawnerPos), gameBoard(_gameBoard) {}

    void manageBarrels();
};