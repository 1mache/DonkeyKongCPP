#pragma once

#include "Point.h"
#include "Ghost.h"
#include "Constants.h"
#include <cstdlib>

class ClimbingGhost : public Ghost
{
    char ghostChar = Board::CLIMBING_GHOST;

    // tells us if we're climbing a ladder right now 
    bool midClimb = false;

    // max frames delay for climbing ghost movement (too hard for player to avoid ghost without it)
    static constexpr int MOVE_DELAY = 1;

    // current delay frame counter
    int delay = MOVE_DELAY;

    // position for climbing ghost to follow 
    Point follow = getPosition();

    bool canClimbUp(Point position) const;

    bool canClimbDown(Point position) const;

    void climbUp();

    void climbDown();

    void setFollowPos();

    void moveGhost() override;

public:

    ClimbingGhost(Board* _gameBoard, Point _startPos, char _ghostChar) :
        Ghost(_gameBoard, _startPos, _ghostChar), ghostChar(_ghostChar)  {}

    virtual ~ClimbingGhost() {}
};
