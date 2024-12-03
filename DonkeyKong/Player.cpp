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
                horizontalState = state;
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
    int moveX = directions[horizontalState].x;
    int moveY = 0;
    
    if(curState == UP)
    {
        if (canClimbUp(position))
        {
            if (!midJump)
            {
                climbUp();
                return;
            }
        }
        else
            jump();
    }

    if(curState == DOWN)
    {
        if(canClimbDown(position))
        {
            climbDown();
            return;   
        }
    }

    //if were on a ladder in one of the current states
    if(curState == STAY || curState == RIGHT || curState == LEFT)
    {
        if (gameBoard->isLadderAtPos(position.x, position.y) && !onGround)
        {
            //dont move and dont apply gravity
            playerMovement.move(0, 0, false);
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
        curState = horizontalState;
    }
}

void Player::climbUp()
{
    static bool midClimb = false;
    int moveX = 0;
    //      -1 if up, 1 if down
    int moveY = -1;
    if(midClimb)
    {
        playerMovement.move(moveX, moveY, false, true);
        onGround = checkPlayerOnGround();

        if(onGround)
        {
            midClimb = false;
            curState = horizontalState;
        }
    }
    else
    {
        playerMovement.move(moveX, moveY, false, true);
        midClimb = true;
    }

    
}

void Player::climbDown()
{
    static bool midClimb = false;
    int moveX = 0;
    int moveY = 1;

    if (midClimb)
    {
        playerMovement.move(moveX, moveY, false, false);
        //if we reached ground were no longer climbing
        onGround = checkPlayerOnGround();

        if (onGround)
        {
            midClimb = false;
            curState = horizontalState;
        }
    }
    else
    {
        playerMovement.move(moveX, moveY, false, true);
        midClimb = true;
    }
}