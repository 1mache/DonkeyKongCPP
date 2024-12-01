#include "MoveState.h"
#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (std::tolower(key) == KEYS[i]) {
            // runs without this line
            //playerMovement.setState((MoveState)i);

            curState = (MoveState)i;
            if ((curState != MoveState::DOWN) && (curState != MoveState::UP))
            {
                jumpDirection = curState;
            }
            return;
        }
    }
}

bool Player::checkPlayerOnGround()
{
    Point playerPos = playerMovement.getPosition();
    return !playerMovement.canMoveToNewPos(playerPos.x, playerPos.y + 1);
}

void Player::movePlayer()
{
    onGround = checkPlayerOnGround();
    //                        LEFT || STAY || RIGHT
    int moveX = directions[(int)jumpDirection].x;
    jump();
    int moveY = directions[(int)jumpDirection].y - midJump;

    playerMovement.move(moveX, moveY, !midJump);
}

int Player::jump()
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
        curState = jumpDirection;
    }

    return midJump;
}