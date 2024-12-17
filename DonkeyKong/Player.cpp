#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (std::tolower(key) == KEYS[i]) {
            MoveState state = (MoveState)i;
            
            //set the curent state acordingly if were not mid jump 
            if(!midJump)
            {
                curState = state;
            }
            //update the horizontal state if needed
            if ((state != DOWN) && (state != UP))
            {
                horizontalState = state;
            }
            
            return;
        }
    }
}

void Player::takeDamage()
{
    //little animation 
    for (size_t i = 0; i < DEATH_ANIMATION_FRAMES; i++)
    {
        playerMovement.erase();
        Sleep(Constants::GAME_REFRESH_RATE * 2);
        playerMovement.draw();
        Sleep(Constants::GAME_REFRESH_RATE * 2);
    }
}

void Player::movePlayer()
{
    bool onGround = playerMovement.checkOnGround();
    Point position = playerMovement.getPosition();

    bool gravity = true;

    if (horizontalMovesOnLadder())
    {
        // stop the player and dont apply gravity
        gravity = false;
        playerMovement.move(DIRECTIONS[STAY], gravity);
        return;
    }

    if (curState == UP)
    {   
        if (canClimbUp(position))
        {
            climbUp();
            return;
        }
        else
        {
            jump();
            return;
        }
    }

    if (curState == DOWN)
    {
        if (canClimbDown(position))
        {
            climbDown();
            return;
        }
        else 
        {
            // if we counldnt climb at this position reset the state
            curState = horizontalState;
        }
    }
    
    // if we got here we just move the player horizontaly
    playerMovement.move( DIRECTIONS[horizontalState], gravity);
}

void Player::jump()
{
    Point movePosition;

    Point above = playerMovement.getPosition().oneAbove();
    // if were on the ground and there isnt floor above us OR were mid jump and havent reached jump height
    if ((playerMovement.checkOnGround() && !gameBoard->isObstacleAtPos(above))
        || (midJump && (heightTraveled < JUMP_HEIGHT)))
    {
        // horizontal state
        heightTraveled += 1;
        midJump = true;
                           //up, dowm or stay          add up direction
        movePosition = DIRECTIONS[horizontalState].oneAbove();
    }
    else
    {
        heightTraveled = 0;
        midJump = false;
        curState = horizontalState;

        movePosition = DIRECTIONS[horizontalState];
    }

    playerMovement.move(movePosition, !midJump);
}

void Player::climbUp()
{
    if(midClimb)
    {
        playerMovement.move(DIRECTIONS[UP] , false, true);
        
        //if we reached ground were no longer climbing
        if(playerMovement.checkOnGround())
        {
            midClimb = false;
            //stay after climbing up, feels more intuitive 
            curState = horizontalState = STAY;
        }
    }
    else
    {
        playerMovement.move(DIRECTIONS[UP], false, true);
        midClimb = true;
    }   
}

void Player::climbDown()
{
    if (midClimb)
    {
        playerMovement.move(DIRECTIONS[DOWN], false, false);
        
        //if we reached ground were no longer climbing
        if (playerMovement.checkOnGround())
        {
            midClimb = false;
            curState = horizontalState = STAY;
        }
    }
    else
    {
        playerMovement.move(DIRECTIONS[DOWN], false, true);
        midClimb = true;
    }
}