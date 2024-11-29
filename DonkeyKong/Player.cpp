#include <conio.h>
#include "MoveState.h"
#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (std::tolower(key) == KEYS[i]) {
            playerMovement.setState((MoveState)i);

            curState = (MoveState)i;
            if ((curState != MoveState::DOWN) && (curState != MoveState::UP))
            {
                jumpDirState = curState;
            }
            return;
        }
    }
}

void Player::checkPlayerOnGround()
{
    Point playerPos = playerMovement.getPosition();
    onGround = !playerMovement.canMoveToNewPos(playerPos.x, playerPos.y + 1);
}

void Player::movePlayer()
{
    checkPlayerOnGround();

    int moveX = directions[(int)jumpDirState].x;
    int moveY = directions[(int)jumpDirState].y - jump();

    playerMovement.move(moveX, moveY, !wantJump);
}

int Player::jump()
{
    static int heightTraveled = 0;

    if ((curState == MoveState::UP && onGround) || (wantJump && (heightTraveled < jumpHeight)))
    {
        heightTraveled += 1;
        wantJump = true;
    }
    else
    {
        heightTraveled = 0;
        wantJump = false;
        curState = jumpDirState;
    }

    return wantJump;
}