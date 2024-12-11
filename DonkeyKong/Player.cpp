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

    //     LEFT - (-1) || STAY = 0 || RIGHT = 1
    int moveX = DIRECTIONS[horizontalState].getX();
    int moveY = 0;

    //if were on a ladder in one of the current states
    if (curState == STAY || curState == RIGHT || curState == LEFT)
    {
        if (gameBoard->isLadderAtPos(position)
            && !onGround && !midJump && (playerMovement.getFallHeight() == 0))
        {
            //dont move and dont apply gravity
            playerMovement.move(DIRECTIONS[STAY], false);
            return;
        }
    }

    if (curState == UP)
    {
        if (canClimbUp(position) && !midJump)
        {
            climbUp();
            return;
        }
        else
        {
            jump();
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

    if (midJump)
    {
        moveY = -1;
    }
    
    //no gravity if were mid jump
    playerMovement.move( Point(moveX, moveY) , !midJump);

    //if we fell more than X lines we get hurt
    // NOTE: BUG in this if statement, it is triggered by repeated jumping=====================
    if (playerMovement.checkOnGround() && (playerMovement.getFallHeight() >= MAX_FALL_HEIGHT))
    {
        takeDamage();
    }
}

//returns if were mid jump right now
void Player::jump()
{
    // if were on the ground and the move state is up OR were mid jump and havent reached jump height
    if (playerMovement.checkOnGround() || (midJump && (heightTraveled < jumpHeight)))
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
    if(midClimb)
    {
        playerMovement.move(DIRECTIONS[UP] , false, true);
        
        //if we reached ground were no longer climbing
        if(playerMovement.checkOnGround())
        {
            midClimb = false;
            curState = horizontalState;
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
            curState = horizontalState;
        }
    }
    else
    {
        playerMovement.move(DIRECTIONS[DOWN], false, true);
        midClimb = true;
    }
}