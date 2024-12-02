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
    static constexpr char LADDER = 'H';
    static constexpr int jumpHeight = 3;


    //movement component
    Movement playerMovement;
    Board* gameBoard = nullptr;

    MoveState curState = STAY;
    MoveState jumpDirection = STAY;

    int lifes = 3;
    
    //   mid jump not falling
    bool midJump = false;
    bool onGround = true;
    
    //!!!!
    void jump();
    //Should be in Board.h ??
    bool canClimb(Point position) 
    {
        //checks if the player is on a ladder or can climb in the direction
        return gameBoard->getCharInPos(position.x, position.y) == LADDER ||
            gameBoard->getCharInPos(position.x, position.y + directions[curState].y) == LADDER;
    }
    void climb();
    bool checkPlayerOnGround();
public:
    Player(Board* _gameBoard, char _spriteChar, Point _startPos): 
        playerMovement(Movement(_gameBoard, _spriteChar, _startPos)), gameBoard(_gameBoard){}

    void movePlayer();
    void stateByKey(char key);
};
