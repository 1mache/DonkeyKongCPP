#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"

// FIND A WAY TO MOVE INSIDE THE CLASS

class Barrel
{
    enum RollDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

    static constexpr char LEFT_FLOOR = '<';
    static constexpr char RIGHT_FLOOR = '>';
    static constexpr int EXPLODE_FALL_HEIGHT = 8;
    static constexpr int EXPLOSION_RADIUS = 2;
    static constexpr char EXPLOSION_CHAR = '*';

    //movement component
    Movement barrelMovement;
    char spriteChar;
    Board* gameBoard = nullptr;
    
    Point rollDirection;

    bool reachedWall() const;
    void setBarrelDirection();

                           // 1 <= phase <= EXPLOSION_RADIUS
    void drawExplosionPhase(int phase);
    void drawExplosion();
    void eraseExplosion();

public:
    Barrel(Board* _gameBoard, char _spriteChar, Point _startPos, Point _dir) :
        rollDirection(_dir), barrelMovement(Movement(_gameBoard, _spriteChar, _startPos)), spriteChar(_spriteChar), gameBoard(_gameBoard) {}
    
    void moveBarrel();

    bool needsToExplode()
    {
        return (((barrelMovement.getFallHeight() >= EXPLODE_FALL_HEIGHT) && barrelMovement.checkOnGround())
            || reachedWall());
    }
    
    void explode();
};
