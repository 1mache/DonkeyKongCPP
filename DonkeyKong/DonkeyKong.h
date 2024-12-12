#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"
#include <vector>
#include "Barrel.h"
#include "Board.h"

class DonkeyKong
{
    Point dkPosition;
    static constexpr char dkChar = '&';
    static constexpr char barrelChar = 'O';
    static constexpr int spawnDelay = 20;
    int frameCounter = 0;
    // Duplicate code - the same as in Barrel
    /*enum RollDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };*/
    RollDirection curBarrelDir = RollDirection::RIGHT;
    //

    Board* gameBoard = nullptr;
    std::vector<Barrel> barrelsVector;

public:
    DonkeyKong(Board* _gameBoard, char _dkChar, Point _dkPos) : dkPosition(_dkPos), gameBoard(_gameBoard) {}

    void spawnBarrel();
    void destroyBarrel(int index);
    void moveAllBarrels();
    void barrelsManager();
};
