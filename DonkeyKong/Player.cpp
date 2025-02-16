#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (key == KEYS[i]) {
            MoveState state = static_cast<MoveState>(i);
            
            //set the current state acordingly if were not mid jump 
            if(!midJump)
            {
                curState = state;
            }
            //update the horizontal state and hammerDir if needed
            if ((state != DOWN) && (state != UP))
            {
                horizontalState = state;

                if (state != STAY)
                    hammerDir = state;
            }
            
            return;
        }
    }
}

void Player::handleKeyboardInput(char key)
{
    char lowerKey = static_cast<char>(std::tolower(key));

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
    Point currPosition = getPosition();

    bool gravity = true;

    if (horizontalMovesOnLadder())
    {
        // stop the player and dont apply gravity
        gravity = false;
        move(DIRECTIONS[STAY], gravity);
        gameBoard->setPlayerPos(getPosition());
        return;
    }

    // if the state is up we can either climb or jump 
    if (curState == UP)
    {   
        if (canClimbUp(currPosition))
        {
            climbUp();
            gameBoard->setPlayerPos(getPosition());
            return;
        }
        else
        {
            jump();
            gameBoard->setPlayerPos(getPosition());
            return;
        }
    }
     
    if (curState == DOWN)
    {
        if (canClimbDown(currPosition))
        {
            climbDown();
            gameBoard->setPlayerPos(getPosition());
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
    gameBoard->setPlayerPos(getPosition());
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

void Player::takeDamage()
{
    //little animation 
    for (size_t i = 0; i < DEATH_ANIMATION_FRAMES; i++)
    {
        erase();
        Sleep(GameOptions::getRefreshRate() * 2);
        draw();
        Sleep(GameOptions::getRefreshRate() * 2);
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
    // prints either p or q in the direction Mario is facing,
    // based on hammerDir
    const char hammerChar = (hammerDir == LEFT) ? HAMMER_ANIM_CHARS[HammerAnimation::hLEFT] : HAMMER_ANIM_CHARS[HammerAnimation::hRIGHT];
    const char armChar = HAMMER_ANIM_CHARS[HammerAnimation::ARM];
    Point destroyPosPlus = destroyPos + DIRECTIONS[hammerDir];
    
    // looks like @~p or q~@
    DK_utils::drawSymbolOnScreen(armChar, destroyPos);
    DK_utils::drawSymbolOnScreen(hammerChar, destroyPosPlus);

    Sleep(GameOptions::getRefreshRate());
   
    // erases both hammer and "arm"
    DK_utils::drawSymbolOnScreen(gameBoard->getCharAtPos(destroyPos), destroyPos);
    DK_utils::drawSymbolOnScreen(gameBoard->getCharAtPos(destroyPosPlus), destroyPosPlus);

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
        
        // if we didnt hit an enemy that can be destroyed by hammer, return position not set
        return GameOptions::POS_NOT_SET;
    }

    return GameOptions::POS_NOT_SET;
}
