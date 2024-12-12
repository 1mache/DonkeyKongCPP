#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"

// don't know if it's ok that they are outside the class, but DonkeyKong also uses them
enum RollDirection { LEFT, RIGHT };
static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

class Barrel
{
    static constexpr char LEFT_FLOOR = '<';
    static constexpr char RIGHT_FLOOR = '>';
    static constexpr int EXPLODE_FALL_HEIGHT = 8;

    //movement component
    Movement barrelMovement;
    Board* gameBoard = nullptr;

    bool barrelEnabled = true;

    RollDirection barrelDir = RollDirection::RIGHT;

    void setBarrelDirection();

public:
    Barrel(Board* _gameBoard, char _spriteChar, Point _startPos, RollDirection _startDir) :
        barrelDir(_startDir), barrelMovement(Movement(_gameBoard, _spriteChar, _startPos)), gameBoard(_gameBoard) {}
    
    void moveBarrel();
    bool checkExploded();
    bool checkHitMario();
};
