#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (key == KEYS[i]) {
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

                if (state != STAY)
                {
                    hammerDir = state;
                }
            }
            
            return;
        }
    }
}

void Player::handleKeyboardInput(char key)
{
    char lowerKey = std::tolower(key);

    if (lowerKey == HAMMER_KEY)
    {
        usingHammer = true;
    }
    else
    {
        stateByKey(lowerKey);
    }
}

void Player::movePlayer()
{
    Point position = getPosition();

    bool gravity = true;

    if (horizontalMovesOnLadder())
    {
        // stop the player and dont apply gravity
        gravity = false;
        move(DIRECTIONS[STAY], gravity);
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
    move(DIRECTIONS[horizontalState], gravity);
}

void Player::jump()
{
    Point movePosition = DIRECTIONS[horizontalState];

    // position above player
    Point above = getPosition().oneAbove();

    // if we're on the ground and there isnt floor above us OR we're mid jump and havent reached jump height
    if ((checkOnGround() && !gameBoard->isObstacleAtPos(above))
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
    move(movePosition, !midJump);
}

bool Player::canClimbUp(Point position) const
{
    // while climbing up we need to be on the ladder or one tile above the ladder
    // which looks like were "in the ground"
    bool positionAllowsClimbing = gameBoard->isLadderAtPos(position) ||
        (gameBoard->isLadderAtPos(position.oneBelow()) && gameBoard->isObstacleAtPos(position));

    return positionAllowsClimbing && !midJump && !isFalling();
}

bool Player::canClimbDown(Point position) const
{
    // while climbing down, we need to be on the ladder that is above ground
    // or on the floor above the ladder 
    Point twoBelow = position.oneBelow().oneBelow();
    bool positionAllowsClimbing = (gameBoard->isLadderAtPos(position) && !checkOnGround()) ||
        gameBoard->isLadderAtPos(twoBelow);

    return positionAllowsClimbing && !midJump && !isFalling();
}

void Player::climbUp()
{
    // midClimb tells us whether to continue climb or not
    if(midClimb)
    {                             //dont use gravity on ladder and allow passing through floor
        move(DIRECTIONS[UP] , false, true);
        
        //if we reached ground we`re no longer climbing
        if(checkOnGround())
        {
            midClimb = false;
            //stay after climbing up, feels more intuitive 
            curState = horizontalState = STAY;
        }
    }
    else
    {
        //start climbing
        move(DIRECTIONS[UP], false, true);
        midClimb = true;
    }   
}

void Player::climbDown()
{
    // midClimb tells us whether to continue climb or not
    if (midClimb)
    { 
                                                    
        move(DIRECTIONS[DOWN], false, false);
        
        //if we reached ground we're no longer climbing
        if (checkOnGround())
        {
            midClimb = false;
            curState = horizontalState = STAY;
        }
    }
    else
    {
        // start climbing
        move(DIRECTIONS[DOWN], false, true);
        midClimb = true;
    }
}

void Player::takeDamage() const
{
    //little animation 
    for (size_t i = 0; i < DEATH_ANIMATION_FRAMES; i++)
    {
        erase();
        Sleep(Constants::GAME_REFRESH_RATE * 2);
        draw();
        Sleep(Constants::GAME_REFRESH_RATE * 2);
    }
}

void Player::checkHammerPickup()
{
    Point position = getPosition();
    if (gameBoard->isHammerAtPos(position))
    {
        hasHammer = true;
        gameBoard->resetCharAtPos(position);
    }
}

void Player::hammerAnimation(Point destroyPos) const
{
    if (gameBoard->isPosInBounds(destroyPos))
    {
        gotoScreenPos(destroyPos);
        std::cout << '~';
    }
    if (gameBoard->isPosInBounds(destroyPos + DIRECTIONS[hammerDir]))
    {
        gotoScreenPos(destroyPos + DIRECTIONS[hammerDir]);
        std::cout << '~';
    }

    Sleep(Constants::GAME_REFRESH_RATE);

    if (gameBoard->isPosInBounds(destroyPos))
    {
        gotoScreenPos(destroyPos);
        std::cout << gameBoard->getCharAtPos(destroyPos);
    }
    if (gameBoard->isPosInBounds(destroyPos + DIRECTIONS[hammerDir]))
    {
        gotoScreenPos(destroyPos + DIRECTIONS[hammerDir]);
        std::cout << gameBoard->getCharAtPos(destroyPos + DIRECTIONS[hammerDir]);
    }
}

Point Player::handleHammer()
{
    if (hasHammer && usingHammer)
    {
        usingHammer = false;
        Point destroyPos = getPosition() + DIRECTIONS[hammerDir];
        
        hammerAnimation(destroyPos);

        // check for an enemy in one of 2 chars infront of player direction
        if (gameBoard->isHammerEnemyAtPos(destroyPos))
        {
            return destroyPos;
        }
        else if (gameBoard->isHammerEnemyAtPos(destroyPos + DIRECTIONS[hammerDir]))
        {
            return destroyPos + DIRECTIONS[hammerDir];
        }
        
        return Constants::POS_NOT_SET;
    }

    return Constants::POS_NOT_SET;
}
