#pragma once

#include "Movement.h"

class Player
{
    Movement playerMovement;
    static constexpr char KEYS[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t NUM_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);
    MoveState curState;
    MoveState jumpDirState = MoveState::STAY;

    // Final height should be 2, I made it 3 so you can jump between platforms
    static constexpr int jumpHeight = 3;

    int lifes;
    //bool isJumping = false;
    bool wantJump = false;
    bool onGround = true;

public:
    Player(Movement _movement, int _lifes): playerMovement(_movement), lifes(_lifes){}

    void stateByKey(char key);
    void movePlayer();
    int jump();
    void checkPlayerOnGround();
    void checkPlayerReachedWall();
};
