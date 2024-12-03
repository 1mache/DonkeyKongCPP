#pragma once

#include "Point.h"
#include "Movement.h"

class Player
{
    enum MoveState { UP, LEFT, DOWN, RIGHT, STAY };
    static constexpr Point directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
    static constexpr char KEYS[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t NUM_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);
    // Final height should be 2, I made it 3 so you can jump between platforms
    static constexpr int jumpHeight = 2;


    //movement component
    Movement playerMovement;
    Board* gameBoard = nullptr;

    MoveState curState = STAY;
    //the player keeps the horizontal state if it is not changed
    MoveState horizontalState = STAY;

    int lifes = 3;
    
    //   mid jump not falling
    bool midJump = false;
    bool onGround = true;
    
    void jump();

    bool canClimbUp(Point position) 
    {
        // while climbing up we need to be on the ladder or one tile above the ladder
        // which looks like were "in the ground"
        return gameBoard->isLadderAtPos(position.x, position.y) ||
            gameBoard->isLadderAtPos(position.x, position.y + 1);
    }
    bool canClimbDown(Point position)
    {
        // while climbing down, we need to be on the ladder that is above ground
        // or on the floor above the ladder 
        return (gameBoard->isLadderAtPos(position.x, position.y) && !onGround) ||
            gameBoard->isLadderAtPos(position.x, position.y + 2);
    }

    void climbUp();
    void climbDown();
    bool checkPlayerOnGround();

public:
    Player(Board* _gameBoard, char _spriteChar, Point _startPos): 
        playerMovement(Movement(_gameBoard, _spriteChar, _startPos)), gameBoard(_gameBoard){}

    void movePlayer();
    void stateByKey(char key);
};
