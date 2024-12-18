#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"

class Barrel
{

    static constexpr char LEFT_FLOOR = '<';
    static constexpr char RIGHT_FLOOR = '>';
    static constexpr int EXPLODE_FALL_HEIGHT = 8;
    static constexpr int EXPLOSION_RADIUS = 2;
    
    //movement component
    Movement barrelMovement;
    Board* gameBoard = nullptr;
    
    // are we rolling left or right
    Point currentRollDirection;

    // 0 <= phase <= EXPLOSION_RADIUS + 1
    int explosionPhase = 0;

    bool reachedWall() const
    {
        Point position = barrelMovement.getPosition();
        return(((!barrelMovement.canMoveToPos(position.oneLeft())) || (!barrelMovement.canMoveToPos(position.oneRight())))
            && barrelMovement.checkOnGround());
    }
    
    // decides current roll direction based on floor below us '<' or '>'
    void setBarrelDirection();  
    
    bool needsToExplode()
    {
        // barrel needs to explode if it fell more than x tiles or if it reached wall
        return (((barrelMovement.getFallHeight() >= EXPLODE_FALL_HEIGHT) && barrelMovement.checkOnGround())
            || reachedWall());
    }

    void moveBarrel();
    // starts the explosion cycle
    void explode();
    void drawExplosionPhase();
    void eraseExplosion();

public:
    enum RollDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

    Barrel(Board* _gameBoard, Point _startPos, Point _dir) :
        currentRollDirection(_dir), barrelMovement(Movement(_gameBoard, Board::BARREL, _startPos)), gameBoard(_gameBoard) {}
    
    // updates barrel based on what its doing right now, whether its
    // moving or exploding
    void update();

    bool exploded()
    {
        //when we see the explosion in its full size on the screen explosionPhase
        // will actually be greater than radius by one, see: drawExplosionPhase() 
        return explosionPhase == EXPLOSION_RADIUS + 1;
    }
};
