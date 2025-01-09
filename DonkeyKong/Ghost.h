#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"
#include <cstdlib>

class Ghost : public Movement
{
public:
    enum MoveDirection { LEFT, RIGHT };
    static constexpr Point DIRECTIONS[] = { {-1, 0}, {1, 0} };

private:

    static constexpr int MAX_RANDOM_VAL = 100;
    static constexpr int MAX_DIR_CHANGE_VAL = 5;

    Point startPos = Constants::POS_NOT_SET;

    //movement component
    //Movement ghostMovement;
    Board* gameBoard = nullptr;

    // are we moving left or right
    MoveDirection currentMoveDirection = MoveDirection::RIGHT;

    // check if ghost reached end of a floor
    bool reachedEndOfFloor() const;

    bool reachedAnotherGhost() const;

    // decides current movement direction based on floor below us and other ghosts nearby
    void setGhostDirection()
    {
        if (reachedAnotherGhost() || reachedEndOfFloor() || reachedWall() || shouldRandomDirectionChange())
        {
            changeDirection();
        }
    }

    void changeDirection()
    {
        // move direction has 2 values (index 0 or 1), and 1-direction gives the opposite value 
        currentMoveDirection = MoveDirection(1 - currentMoveDirection);
    }

    bool shouldRandomDirectionChange() const
    {
        return ((rand() % MAX_RANDOM_VAL) < MAX_DIR_CHANGE_VAL);
    }

public:

    Ghost(Board* _gameBoard, Point _startPos) :
        Movement(_gameBoard, Board::GHOST, _startPos), gameBoard(_gameBoard), startPos(_startPos) {}

    void moveGhost();

    void resetGhostPos()
    {
        setPosition(startPos);
    }
};
