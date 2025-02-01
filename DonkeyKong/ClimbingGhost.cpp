#include "ClimbingGhost.h"

bool ClimbingGhost::canClimbUp(Point position) const
{
    // while climbing up we need to be on the ladder or one tile above the ladder
    // which looks like were "in the ground"
    bool positionAllowsClimbing = gameBoard->isLadderAtPos(position) ||
        (gameBoard->isLadderAtPos(position.oneBelow()) && gameBoard->isObstacleAtPos(position));

    return positionAllowsClimbing;
}

bool ClimbingGhost::canClimbDown(Point position) const
{
    // while climbing down, we need to be on the ladder that is above ground
    // or on the floor above the ladder 
    bool positionAllowsClimbing = (gameBoard->isLadderAtPos(position) && !checkOnGround()) ||
        gameBoard->isLadderAtPos(position.oneBelow().oneBelow());

    return positionAllowsClimbing;
}

void ClimbingGhost::climbUp()
{
    // midClimb tells us whether to continue climb or not
    if (midClimb)
    {                             //dont use gravity on ladder and allow passing through floor
        move(DIRECTIONS[MoveDirection::UP], false, true);

        //if we reached ground we`re no longer climbing
        if (checkOnGround())
        {
            midClimb = false;
        }
    }
    else
    {
        //start climbing
        move(DIRECTIONS[MoveDirection::UP], false, true);
        midClimb = true;
    }
}

void ClimbingGhost::climbDown()
{
    // midClimb tells us whether to continue climb or not
    if (midClimb)
    {

        move(DIRECTIONS[MoveDirection::DOWN], false, false);

        //if we reached ground we're no longer climbing
        if (checkOnGround())
        {
            midClimb = false;
        }
    }
    else
    {
        // start climbing
        move(DIRECTIONS[MoveDirection::DOWN], false, true);
        midClimb = true;
    }
}

void ClimbingGhost::setFollowPos()
{
    Point player = gameBoard->getPlayerPos();
    int playerY = player.getY();
    int ghostY = getPosition().getY();

    Point temp;

    // set new follow pos only if ghost is on floor
    if (checkOnGround())
    {
        // player is above ghost
        if (playerY < ghostY)
        {
            temp = gameBoard->getWayUpInRow(getPosition());
            // follow doesnt change if there is no way up
            follow = (temp != GameOptions::POS_NOT_SET ? temp : follow);
        }

        // player is below ghost
        else if (playerY > ghostY)
        {
            temp = gameBoard->getWayDownInRow(getPosition());
            // follow doesnt change if there is no way down
            follow = (temp != GameOptions::POS_NOT_SET ? temp : follow);
        }

        // player is in same row as ghost
        else
        {
            follow = player;
        }
    }
}

void ClimbingGhost::moveGhost()
{
    // remove ghost from board in its previous position
    gameBoard->resetCharAtPos(getPosition());

    if (delay == 0)
    {
        setFollowPos();

        // if ghost reached ladder or hole
        if (getPosition().getX() == follow.getX())
        {
            int playerY = gameBoard->getPlayerPos().getY();
            int ghostY = getPosition().getY();

            // if player is above ghost and ghost is on ladder or mid climb up
            if ((playerY < ghostY) && (canClimbUp(getPosition())))
            {
                climbUp();
            }

            // if player is below ghost and ghost is on ladder or mid climb down
            else if ((playerY > ghostY) && (canClimbDown(getPosition())))
            {
                climbDown();
            }

            // player is in same row as ghost
            else
            {
                move(GameOptions::POINT_ZERO, true);
            }
        }

        // else continue moving horizontaly to follow pos
        else
        {
            Point dirVector = follow - getPosition();

            currentMoveDirection = (dirVector.getX() > 0) ? MoveDirection::RIGHT : MoveDirection::LEFT;
            move(DIRECTIONS[currentMoveDirection], true);
        }

        delay = MOVE_DELAY;
    }

    else
    {
        --delay;
    }

    // place ghost on board in its new position
    gameBoard->updateBoardWithChar(getPosition(), ghostChar);
}