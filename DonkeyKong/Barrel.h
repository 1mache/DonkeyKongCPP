#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"

class Barrel
{
    enum RollDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

    static constexpr char LEFT_FLOOR = '<';
    static constexpr char RIGHT_FLOOR = '>';
    static constexpr int EXPLODE_FALL_HEIGHT = 8;
    static constexpr int EXPLOSION_RADIUS = 2;
    static constexpr char EXPLOSION_CHAR = Board::EXPLOSION;

    //movement component
    Movement barrelMovement;
    char spriteChar;
    Board* gameBoard = nullptr;
    
    Point rollDirection;

    // 1 <= phase <= EXPLOSION_RADIUS + 1
    int explosionPhase = 0;

    bool reachedWall() const
    {
        Point position = barrelMovement.getPosition();
        return(((!barrelMovement.canMoveToPos(position.oneLeft())) || (!barrelMovement.canMoveToPos(position.oneRight())))
            && barrelMovement.checkOnGround());
    }

    void setBarrelDirection();

    bool needsToExplode()
    {
        return (((barrelMovement.getFallHeight() >= EXPLODE_FALL_HEIGHT) && barrelMovement.checkOnGround())
            || reachedWall());
    }

    void moveBarrel();
    void explode();
    void drawExplosionPhase();
    void eraseExplosion();

public:
    Barrel(Board* _gameBoard, char _spriteChar, Point _startPos, Point _dir) :
        rollDirection(_dir), barrelMovement(Movement(_gameBoard, _spriteChar, _startPos)), spriteChar(_spriteChar), gameBoard(_gameBoard) {}
    
    void update();

    bool exploded()
    {
        return explosionPhase == EXPLOSION_RADIUS + 1;
    }
};
