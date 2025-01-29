#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "Constants.h"
#include <cstdlib>

class Ghost : public MovingObject
{
    // values for random direction change of 0.05 probability
    static constexpr int MAX_RANDOM_VAL = 100;
    static constexpr int DIR_CHANGE_CHANCE = 5;

    char ghostChar = Board::GHOST;

    // sets ghost's direction based on environment and other ghosts, if needed
    // returns whether this actually changed the direction
    bool adjustDirection();

    // return true if we got a random value in [0,DIR_CHANGE_CHANCE) out of [0,MAX_RANDOM_VAL)
    bool shouldRandomDirectionChange() const
    {
        return ((rand() % MAX_RANDOM_VAL) < DIR_CHANGE_CHANCE);
    }

    // return true if we reached another regular ghost in front of our movement direction
    bool reachedAnotherGhost() const
    {
        return (gameBoard->getCharAtPos(getPosition() + DIRECTIONS[currentMoveDirection]) == Board::GHOST);
    }

    // check if ghost reached end of a floor
    bool reachedEndOfFloor() const;

    // return true if ghost reached a wall in its movement direction
    bool reachedWall() const
    {
        return(!canMoveToPos(getPosition() + getDirection()));
    }

    void changeHorizontalDirection()
    {
        // LEFT and RIGHT are 2 values apart in MoveDirection (index 1, 3), and there are only 4 values in total.
        // So the calculation below gives the opposite horizontal direction 
        if (currentMoveDirection == MoveDirection::RIGHT || currentMoveDirection == MoveDirection::LEFT)
        {
            currentMoveDirection = MoveDirection((currentMoveDirection + 2) % 4);
        }
    }

    Point getDirection() const
    {
        return DIRECTIONS[currentMoveDirection];
    }

protected:
    enum MoveDirection { UP, LEFT, DOWN, RIGHT };
    static constexpr Point DIRECTIONS[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

    MoveDirection currentMoveDirection = MoveDirection::RIGHT;

    virtual void moveGhost();

public:
    Ghost(Board* _gameBoard, Point _startPos, char _ghostChar) :
        MovingObject(_gameBoard, _ghostChar, _startPos), ghostChar(_ghostChar) {}

    void update() override
    {
        moveGhost();
    }

    virtual ~Ghost() {}
};
