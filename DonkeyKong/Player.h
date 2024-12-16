#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"

class Player
{
    enum MoveState { UP, LEFT, DOWN, RIGHT, STAY };
    static constexpr Point DIRECTIONS[]  = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
    static constexpr char KEYS[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t NUM_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);
    
    static constexpr int MAX_FALL_HEIGHT = 5;
    static constexpr int JUMP_HEIGHT = 2;
    static constexpr int DEATH_ANIMATION_FRAMES = 5;

    //movement component
    Movement playerMovement;
    Board* gameBoard = nullptr;

    MoveState curState = STAY;
    //the player keeps the horizontal state if it is not changed
    MoveState horizontalState = STAY;

    
    //  mid jump not falling
    bool midJump = false;
    // height traveled during a jump 
    int heightTraveled = 0;
    // tells us if were climbing a ladder right now 
    bool midClimb = false;
    
    void jump();

    bool horizontalMovesOnLadder()
    {
        //checks if were trying to move sideways or pressed stay on ladder
        return (curState == STAY || curState == RIGHT || curState == LEFT) && midClimb;
    }

    bool canClimbUp(Point position) 
    {
        // while climbing up we need to be on the ladder or one tile above the ladder
        // which looks like were "in the ground"
        return gameBoard->isLadderAtPos(position) ||
            (gameBoard->isLadderAtPos(position.oneBelow()) && gameBoard->isObstacleAtPos(position));
    }
    bool canClimbDown(Point position)
    {
        // while climbing down, we need to be on the ladder that is above ground
        // or on the floor above the ladder 
        Point twoBelow = position.oneBelow().oneBelow();
        return (gameBoard->isLadderAtPos(position) && !playerMovement.checkOnGround()) ||
            gameBoard->isLadderAtPos(twoBelow);
    }

    void climbUp();
    void climbDown();

public:
    Player(Board* _gameBoard, char _spriteChar, Point _startPos): 
        playerMovement(Movement(_gameBoard, _spriteChar, _startPos)), gameBoard(_gameBoard){}

    Point getPosition()
    {
        return playerMovement.getPosition();
    }
    
    void movePlayer();
    void stateByKey(char key);

    bool checkFallDamage() 
    {
        //return true if we just fell more than X tiles
        return (playerMovement.checkOnGround() && (playerMovement.getFallHeight() >= MAX_FALL_HEIGHT));
    }

    bool checkCollision() const
    {
        Point position = playerMovement.getPosition();
        return gameBoard->isHazardAtPos(position);
    }

    void takeDamage();
};
