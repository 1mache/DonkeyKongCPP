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

    Point spawnPosition;
    int frameCounter = 0;
    bool spawnToRight = true;
    // Duplicate code - the same as in Barrel
    /*enum RollDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };*/
    RollDirection curBarrelDir = RollDirection::RIGHT;
    //

    Board* gameBoard = nullptr;
    std::vector<Barrel> barrelsVector;

    void spawnBarrel();
    void destroyBarrel(int index);
    void moveAllBarrels();

    int getRandomDelay() { return ((rand() % (MAX_SPAWN_DELAY + 1 - MIN_SPAWN_DELAY)) + MIN_SPAWN_DELAY); };

public:
    BarrelManager(Board* _gameBoard, Point _spawnPos) : spawnPosition(_spawnPos), gameBoard(_gameBoard) {}

    void manageBarrels();
};