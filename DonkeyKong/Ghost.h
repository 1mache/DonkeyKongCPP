#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "Constants.h"
#include <cstdlib>

class Ghost : public MovingObject
{
    enum MoveDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

    static constexpr int MAX_RANDOM_VAL = 100;
    static constexpr int DIR_CHANGE_CHANCE = 5;

    Board* gameBoard = nullptr;

    // are we moving left or right
    MoveDirection currentMoveDirection = MoveDirection::LEFT;

    // sets ghosts direction based on environment (not including other ghosts) , if needed
    // returns whether this actually changed the direction
    bool adjustDirection();
    
    // check if ghost reached end of a floor
    bool reachedEndOfFloor() const;


    bool shouldRandomDirectionChange() const
    {
        return ((rand() % MAX_RANDOM_VAL) < DIR_CHANGE_CHANCE);
    }

    void moveGhost();
public:

    Ghost(Board* _gameBoard, Point _startPos) :
        MovingObject(_gameBoard, Board::GHOST, _startPos), gameBoard(_gameBoard) {}

    Point getDirection() const
    {
        return DIRECTIONS[currentMoveDirection];
    }

    bool reachedAnotherGhost() const;

    void changeDirection()
    {
        // move direction has 2 values (index 0 or 1), and 1-direction gives the opposite value 
        currentMoveDirection = MoveDirection(1 - currentMoveDirection);
    }

    void update() override
    {
        moveGhost();
    }
};
