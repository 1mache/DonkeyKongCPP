#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "GameOptions.h"

class Barrel : public MovingObject
{
public:
    enum RollDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

private:
    static constexpr char LEFT_FLOOR = '<';
    static constexpr char RIGHT_FLOOR = '>';
    static constexpr int EXPLODE_FALL_HEIGHT = 8;
    static constexpr int EXPLOSION_RADIUS = 2;

    Board* gameBoard = nullptr;

    // are we rolling left or right
    RollDirection currentRollDirection;

    // 0 <= phase <= EXPLOSION_RADIUS + 1
    int explosionPhase = 0;

    // decides current roll direction based on floor below us '<' or '>'
    void setBarrelDirection();

    bool needsToExplode() const
    {
        // barrel needs to explode if it fell more than x tiles or if it reached wall
        return (((getFallHeight() >= EXPLODE_FALL_HEIGHT) && checkOnGround())
            || reachedWall());
    }

    void moveBarrel();
    // starts the explosion cycle
    void explode();
    void drawExplosionPhase();
    void eraseExplosion();

    bool reachedWall() const
    {
        return((!canMoveToPos(getPosition() + DIRECTIONS[currentRollDirection])) && checkOnGround());
    }

public:

    Barrel(Board* _gameBoard, Point _startPos, RollDirection _dir) :
        currentRollDirection(_dir), MovingObject(_gameBoard, Board::BARREL, _startPos), gameBoard(_gameBoard) {}

    // updates barrel based on what its doing right now, whether its
    // moving or exploding
    void update() override;

    bool exploded() const
    {
        //when we see the explosion in its full size on the screen explosionPhase
        // will actually be greater than radius by one, see: drawExplosionPhase() 
        return explosionPhase == EXPLOSION_RADIUS + 1;
    }
};
