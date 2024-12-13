#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"

// FIND A WAY TO MOVE INSIDE THE CLASS
enum RollDirection { LEFT, RIGHT };
static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

class Barrel
{
    static constexpr char LEFT_FLOOR = '<';
    static constexpr char RIGHT_FLOOR = '>';
    static constexpr int EXPLODE_FALL_HEIGHT = 8;

    //movement component
    Movement barrelMovement;
    char spriteChar;
    Board* gameBoard = nullptr;
    
    RollDirection rollDirection = RollDirection::RIGHT;

    void setBarrelDirection();

public:
    Barrel(Board* _gameBoard, char _spriteChar, Point _startPos, RollDirection _dir) :
        rollDirection(_dir), barrelMovement(Movement(_gameBoard, _spriteChar, _startPos)), spriteChar(_spriteChar), gameBoard(_gameBoard) {}
    
    void moveBarrel();

    bool reachedWall() const;
    
    // NAME??
    bool checkExploded();

    void rollLeft()
    {
        rollDirection = RollDirection::LEFT;
    }

    void rollRight()
    {
        rollDirection = RollDirection::RIGHT;
    }
};
