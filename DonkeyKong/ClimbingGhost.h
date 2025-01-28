#pragma once

#include "Point.h"
#include "Ghost.h"
#include "Constants.h"
#include <cstdlib>

class ClimbingGhost : public Ghost
{
    /*enum MoveDirection { UP, LEFT, DOWN, RIGHT };
    static constexpr Point DIRECTIONS[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };*/

    enum Modes { SCAN, LEFT, DOWN, RIGHT };

    char ghostChar = Board::CLIMBING_GHOST;

    //Board* gameBoard = nullptr;

    // tells us if were climbing a ladder right now 
    bool midClimb = false;

    static constexpr int MOVE_DELAY = 1;

    int delay = MOVE_DELAY;

    Point follow = getPosition();

    bool updatedFollow = false;

    bool canClimbUp(Point position) const
    {
        // while climbing up we need to be on the ladder or one tile above the ladder
        // which looks like were "in the ground"
        bool positionAllowsClimbing = gameBoard->isLadderAtPos(position) ||
            (gameBoard->isLadderAtPos(position.oneBelow()) && gameBoard->isObstacleAtPos(position));

        return positionAllowsClimbing;
    }

    bool canClimbDown(Point position) const
    {
        // while climbing down, we need to be on the ladder that is above ground
        // or on the floor above the ladder 
        bool positionAllowsClimbing = (gameBoard->isLadderAtPos(position) && !checkOnGround()) ||
            gameBoard->isLadderAtPos(position.oneBelow().oneBelow());

        return positionAllowsClimbing;
    }

    void climbUp()
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

    void climbDown()
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

    void setFollowPos()
    {
        Point player = gameBoard->getPlayerPos();
        int playerY = player.getY();
        int ghostY = getPosition().getY();

        // player is above ghost
        if (playerY < ghostY)
        {
            follow = gameBoard->getWayUpInRow(getPosition());
        }

        // player is below ghost
        else if (playerY > ghostY)
        {
            follow = gameBoard->getWayDownInRow(getPosition());
        }

        // player is in same row as ghost
        else
        {
            follow = player;
        }
    }

    void moveGhost() override
    {
        // remove ghost from board in its previous position
        gameBoard->resetCharAtPos(getPosition());

        if (delay == 0)
        {

            setFollowPos();

            /*Point dirVector = follow - getPosition();
            int dirY = dirVector.getY();
            int dirX = dirVector.getX();*/

            if (getPosition() == follow)
            {
                int playerY = gameBoard->getPlayerPos().getY();
                int ghostY = getPosition().getY();

                if ((playerY < ghostY) && (canClimbUp(getPosition())))
                {
                    climbUp();
                }

                else if ((playerY > ghostY) && (canClimbDown(getPosition())))
                {
                    climbDown();
                }

                // fallback
                /*else
                {
                    currentMoveDirection = MoveDirection::LEFT;
                    move(DIRECTIONS[currentMoveDirection], true);
                }*/
            }

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

public:

    ClimbingGhost(Board* _gameBoard, Point _startPos) :
        Ghost(_gameBoard, _startPos, Board::CLIMBING_GHOST)  {}
};
