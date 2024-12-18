#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (std::tolower(key) == KEYS[i]) {
            MoveState state = (MoveState)i;
            
            //set the current state acordingly if were not mid jump 
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

    // if the state is up we can either climb or jump 
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
    Point movePosition = DIRECTIONS[horizontalState];

    // position above player
    Point above = playerMovement.getPosition().oneAbove();

    // if we're on the ground and there isnt floor above us OR we're mid jump and havent reached jump height
    if ((playerMovement.checkOnGround() && !gameBoard->isObstacleAtPos(above))
        || (midJump && (heightTraveled < JUMP_HEIGHT)))
    {
        // increment height traveled
        heightTraveled += 1;
        midJump = true;

        //add up direction
        movePosition = DIRECTIONS[horizontalState].oneAbove();
    }
    else // we "landed"
    {
        // reset height traveled
        heightTraveled = 0;
        // reset midjump
        midJump = false;
        // set the state to horizontal state so the player continues horizontal movement =
        curState = horizontalState;
    }

    // move accordingly 
    playerMovement.move(movePosition, !midJump);
}

void Player::climbUp()
{
    // midClimb tells us whether to continue climb or not
    if(midClimb)
    {                             //dont use gravity on ladder and allow passing through floor
        playerMovement.move(DIRECTIONS[UP] , false, true);
        
        //if we reached ground we`re no longer climbing
        if(playerMovement.checkOnGround())
        {
            midClimb = false;
            //stay after climbing up, feels more intuitive 
            curState = horizontalState = STAY;
        }
    }
    else
    {
        //start climbing
        playerMovement.move(DIRECTIONS[UP], false, true);
        midClimb = true;
    }   
}

void Player::climbDown()
{
    // midClimb tells us whether to continue climb or not
    if (midClimb)
    { 
                                                    
        playerMovement.move(DIRECTIONS[DOWN], false, false);
        
        //if we reached ground we're no longer climbing
        if (playerMovement.checkOnGround())
        {
            midClimb = false;
            curState = horizontalState = STAY;
        }
    }
    else
    {
        // start climbing
        playerMovement.move(DIRECTIONS[DOWN], false, true);
        midClimb = true;
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