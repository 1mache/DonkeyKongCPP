#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (std::tolower(key) == KEYS[i]) {
            MoveState state = (MoveState)i;
            //set the curent state acordingly if were not mid jump 
            if(!midJump)
                curState = state;

            if ((state != DOWN) && (state != UP))
            {
                jumpDirection = state;
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
    Point position = playerMovement.getPosition();

    //     LEFT - (-1) || STAY = 0 || RIGHT = 1
    int moveX = directions[jumpDirection].x;
    int moveY = 0;
    
    if(curState == UP)
    {
        if (canClimb(position))
        {
            if (!midJump)
            {
                climb();
                return;
            }
        }
        else
            jump();
    }

    if(curState == DOWN)
    {
        if(!midJump)
        {
            climb();
            return;
        }
    }

    if(midJump)
        moveY = -1;
    //                               no gravity if were mid jump
    playerMovement.move(moveX, moveY, !midJump);
}

//returns if were mid jump right now
void Player::jump()
{
    // static variable !!!
    static int heightTraveled = 0;

    // if were on the ground and the move state is up OR were mid jump and havent reached jump height
    if ((onGround) || (midJump && (heightTraveled < jumpHeight)))
    {
        heightTraveled += 1;
        midJump = true;
    }
    else
    {
        heightTraveled = 0;
        midJump = false;
        curState = jumpDirection;
    }
}

void Player::climb()
{
    int moveX = 0;
    //      -1 if up, 1 if down
    int moveY = directions[curState].y;
    //                              no gravity on the ladder  
    playerMovement.move(moveX, moveY, false);
}
