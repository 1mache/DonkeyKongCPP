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
    lives--;
    //little animation     MAGIC NUMBER
    for (size_t i = 0; i < 5; i++)
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

    // STAY IS VALID !!!!!!!!!!!!!!!!!
    if (isInvalidLadderMove())
    {
        playerMovement.move(DIRECTIONS[STAY], false);
        return;
    }

    if (curState == UP)
    {   
                                    // not mid jump and not mid fall
        if (canClimbUp(position) && !midJump && playerMovement.getFallHeight() == 0)
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
    }
    
    // if we got here we
    playerMovement.move( DIRECTIONS[horizontalState], true);

    //if we fell more than X lines we get hurt
    if (playerMovement.checkOnGround() && (playerMovement.getFallHeight() >= MAX_FALL_HEIGHT))
    {
        takeDamage();
    }
    //                                     MAGIC CHAR +=================================================
    if(gameBoard->getCharAtPos(position) == 'O')
    {
        takeDamage();
    }

}

void Player::jump()
{
    Point movePosition;

    // if were on the ground and the move state is up OR were mid jump and havent reached jump height
    if (playerMovement.checkOnGround() || (midJump && (heightTraveled < jumpHeight)))
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
            //stay after climbing up ==================================================
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