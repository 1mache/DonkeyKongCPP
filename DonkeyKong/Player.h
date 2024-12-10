#pragma once

#include "Point.h"
#include "Movement.h"

class Player
{
    enum MoveState { UP, LEFT, DOWN, RIGHT, STAY };
    static constexpr Point DIRECTIONS[]  = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
    static constexpr char KEYS[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t NUM_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);
    // Final height should be 2, I made it 3 so you can jump between platforms
    static constexpr int MAX_FALL_HEIGHT = 5;
    static const int jumpHeight = 2;

    //movement component
    Movement playerMovement;
    Board* gameBoard = nullptr;

    MoveState curState = STAY;
    //the player keeps the horizontal state if it is not changed
    MoveState horizontalState = STAY;

    int lives = 3;
    
    //   mid jump not falling
    bool midJump = false;
    // height traveled during a jump 
    int heightTraveled = 0;
    // tells us if were climbing a ladder right now 
    bool midClimb = false;
    
    void jump();

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

    void movePlayer();
    void stateByKey(char key);
    int getLives()
    {
        return lives;
    }
};
