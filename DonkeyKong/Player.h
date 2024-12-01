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
    static constexpr int jumpHeight = 3;

    //movement component
    Movement playerMovement;
    Board* gameBoard = nullptr;

    MoveState curState = MoveState::STAY;
    Point jumpDirection = directions[STAY];

    int lifes = 3;
    
    //   mid jump not falling
    bool midJump = false;
    bool onGround = true;

public:
    Player(Board* _gameBoard, char _spriteChar, Point _startPos): playerMovement(Movement(_gameBoard, _spriteChar, _startPos)), gameBoard(_gameBoard) {}

    void stateByKey(char key);
    void movePlayer();
    void jump();
    bool checkPlayerOnGround();
};
