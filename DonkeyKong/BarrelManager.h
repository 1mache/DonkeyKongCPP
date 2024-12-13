#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"
#include <vector>
#include "Barrel.h"
#include "Board.h"

class BarrelManager
{
    // =============================== MOVE TO BARREL CLASS? ============================
    static constexpr char BARREL_CHAR = 'O';
    static constexpr int SPAWN_DELAY = 20;

    Point dkPosition;
    int frameCounter = 0;
    // Duplicate code - the same as in Barrel
    /*enum RollDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };*/
    RollDirection curBarrelDir = RollDirection::RIGHT;
    //

    Board* gameBoard = nullptr;
    // ========= DO WE NEED TO FREE ? ==========
    std::vector<Barrel> barrelsVector;

public:
    BarrelManager(Board* _gameBoard, Point _dkPos) : dkPosition(_dkPos), gameBoard(_gameBoard) {}

    void spawnBarrel();
    void destroyBarrel(int index);
    void moveAllBarrels();
    void manageBarrels();
};