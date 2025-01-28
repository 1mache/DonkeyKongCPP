#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "Constants.h"
#include <cstdlib>
//#include "GhostsManager.h"

//class GhostsManager; // forward declaration

class Ghost : public MovingObject
{
    /*enum MoveDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };*/

    // values for random direction change of 0.05 probability
    static constexpr int MAX_RANDOM_VAL = 100;
    static constexpr int DIR_CHANGE_CHANCE = 5;

    char ghostChar = Board::GHOST;
    //Board* gameBoard = nullptr;

    //GhostsManager* ghostsManager;

    // sets ghosts direction based on environment (not including other ghosts) , if needed
    // returns whether this actually changed the direction
    bool adjustDirection();

    // return true if we got a random value in [0,DIR_CHANGE_CHANCE) out of [0,MAX_RANDOM_VAL)
    bool shouldRandomDirectionChange() const
    {
        return ((rand() % MAX_RANDOM_VAL) < DIR_CHANGE_CHANCE);
    }

    bool reachedAnotherGhost() const;

protected:
    enum MoveDirection { UP, LEFT, DOWN, RIGHT };
    static constexpr Point DIRECTIONS[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

    MoveDirection currentMoveDirection = MoveDirection::RIGHT;

    Point getDirection() const
    {
        return DIRECTIONS[currentMoveDirection];
    }

    virtual void moveGhost();

    // check if ghost reached end of a floor
    bool reachedEndOfFloor() const;

    // return true if ghost reached a wall in its movement direction
    bool reachedWall() const
    {
        return(!canMoveToPos(getPosition() + getDirection()));
    }

    void changeHorizontalDirection()
    {
        //// move direction has 2 values (index 0 or 1), and 1-direction gives the opposite value 
        //currentMoveDirection = MoveDirection(1 - currentMoveDirection);

        if (currentMoveDirection == MoveDirection::RIGHT || currentMoveDirection == MoveDirection::LEFT)
        {
            currentMoveDirection = MoveDirection((currentMoveDirection + 2) % 4);
        }
    }

public:
    Ghost(Board* _gameBoard, Point _startPos, char _ghostChar) :
        MovingObject(_gameBoard, _ghostChar, _startPos), ghostChar(_ghostChar) {}

    void update() override
    {
        moveGhost();
    }
};
