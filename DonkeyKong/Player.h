#pragma once

#include "Point.h"
#include "MovingObject.h"
#include "GameOptions.h"
#include "EventQueue.h"

class Player : public MovingObject
{
    enum MoveState { UP, LEFT, DOWN, RIGHT, STAY };
    static constexpr Point DIRECTIONS[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
    static constexpr char KEYS[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t NUM_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);
    
    static constexpr char HAMMER_KEY = 'p';
    enum HammerAnimation {hLEFT = 0, ARM, hRIGHT};
    static constexpr char HAMMER_ANIM_CHARS[]  = { 'q', '~', 'p'};

    static constexpr int MAX_LIVES = 3;
    static constexpr int JUMP_HEIGHT = 2;
    static constexpr int MAX_FALL_HEIGHT = 5;
    static constexpr int DEATH_ANIMATION_FRAMES = 5;

    Board* gameBoard = nullptr;

    MoveState curState = STAY;
    //the player keeps the recent horizontal state regardless of the current state
    MoveState horizontalState = STAY;

    MoveState hammerDir = RIGHT;

    int lives = MAX_LIVES;

    // tells if player has hammer
    bool hasHammer = false;

    // tells if player is currently using hammer (pressing 'p')
    bool usingHammer = false;

    //  mid jump not falling
    bool midJump = false;

    // height traveled during a jump 
    int heightTraveled = 0;

    // tells us if were climbing a ladder right now 
    bool midClimb = false;

    // the function is responsible for the first stage of the jump (until max jump height is reached) 
    // then mario just falls. (handled in movemnet by gravity function)  
    void jump();

    //checks if were trying to move sideways or pressed stay on ladder
    bool horizontalMovesOnLadder()
    {
        return (curState == STAY || curState == RIGHT || curState == LEFT) && midClimb;
    }

    bool isFalling() const
    {
        return getFallHeight() != 0;
    }

    bool canClimbUp(Point position) const;

    bool canClimbDown(Point position) const;

    void climbUp();

    void climbDown();
    
    // checks if the player picked up hammer
    void checkHammerPickup();
    void hammerAnimation(Point destroyPos) const;

    // change state by valid keyboard input (in KEYS[])
    void stateByKey(char key);

    void movePlayer();

public:
    Player(Board* _gameBoard, char _spriteChar, Point _startPos) :
        MovingObject(_gameBoard, _spriteChar, _startPos), gameBoard(_gameBoard) {}

    void update() override
    {
        movePlayer();
        usingHammer = false; // the reset is needed every update to ensure we are in usingHammer = true for only one frame
        checkHammerPickup();
    }

    void handleKeyboardInput(char key);

    bool checkFallDamage() const
    {
        //return true if we just fell more than MAX_FALL_HEIGHT tiles
        return (checkOnGround() && (getFallHeight() >= MAX_FALL_HEIGHT));
    }

    // checks collision with hazard objects 
    bool checkCollision() const
    {
        return gameBoard->isHazardAtPos(getPosition());
    }

    // actions when loses life
    void takeDamage();
    
    bool isHoldingHammer() const
    {
        return hasHammer;
    }

    // if the player uses the hammer right now and found something that he can destroy, 
    // this returns the Point position of whatever needs to be destroyed, if Mario hit something
    Point handleHammer();
};
