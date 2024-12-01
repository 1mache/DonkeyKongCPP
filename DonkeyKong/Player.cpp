#include "MoveState.h"
#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (std::tolower(key) == KEYS[i]) {
            //set the curent state acordingly to
            curState = (MoveState)i;
            if ((curState != MoveState::DOWN) && (curState != MoveState::UP))
            {
                jumpDirection = directions[curState];
            }

            return;
        }
    }
}

bool Player::checkPlayerOnGround()
{
    Point playerPos = playerMovement.getPosition();
    // if you cant move to the postion thats one below the player, theres an obstacle there
    return !playerMovement.canMoveToNewPos(playerPos.x, playerPos.y + 1);
}

void Player::movePlayer()
{
    onGround = checkPlayerOnGround();
    //     LEFT - (-1) || STAY = 0 || RIGHT = 1
    int moveX = jumpDirection.x;
    
    jump();

    int moveY = 0;
    if(midJump)
        moveY = -1;

    playerMovement.move(moveX, moveY, !midJump);
}

//returns if were mid jump right now
void Player::jump()
{
    // static variable !!!
    static int heightTraveled = 0;

    // if were on the ground and the move state is up OR were mid jump and havent reached jump height
    if ((curState == MoveState::UP && onGround) || (midJump && (heightTraveled < jumpHeight)))
    {
        heightTraveled += 1;
        midJump = true;
    }
    else
    {
        heightTraveled = 0;
        midJump = false;
        curState = (MoveState)jumpDirection.x;
    }
}