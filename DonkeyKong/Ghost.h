#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "Constants.h"
#include <cstdlib>

class Ghost : public MovingObject
{
public:
    enum MoveDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

private:

    static constexpr int MAX_RANDOM_VAL = 100;
    static constexpr int MAX_DIR_CHANGE_VAL = 0;

    Board* gameBoard = nullptr;

    // are we moving left or right
    MoveDirection currentMoveDirection = MoveDirection::RIGHT;

    void setGhostDirection()
    {
        if (reachedEndOfFloor() || reachedWall() || shouldRandomDirectionChange())
        {
            changeDirection();
        }
    }
    
    // check if ghost reached end of a floor
    bool reachedEndOfFloor() const;


    bool shouldRandomDirectionChange() const
    {
        return ((rand() % MAX_RANDOM_VAL) < MAX_DIR_CHANGE_VAL);
    }

    void moveGhost();
public:

    Ghost(Board* _gameBoard, Point _startPos) :
        MovingObject(_gameBoard, Board::GHOST, _startPos), gameBoard(_gameBoard) {}

    // decides current movement direction based on floor below us and other ghosts nearby

    Point getGhostDirection()
    {
        return DIRECTIONS[currentMoveDirection];
    }

    void changeDirection()
    {
        // move direction has 2 values (index 0 or 1), and 1-direction gives the opposite value 
        currentMoveDirection = MoveDirection(1 - currentMoveDirection);
    }

    bool reachedAnotherGhost() const;

    void update() override
    {
        moveGhost();
    }
};
