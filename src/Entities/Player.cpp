#include "Player.h"

// Constructor. Initializes player attributes and sprites. 
Player::Player() 
{
    imagesPerMovement = 6 ; // according to what I have in Images/Player/Moves
    movementSpeed = 300.f ; 
    numberOfDifferentMovements = 5 ; // idle, left,right,up,down
    width = 50.f ; 
    height = 50.f ; 
    size = {width,height}; 
    shape.setSize(size); 
    initialX = 0.f ;
    initialY = 0.f ;  
    initialPos = {initialX,initialY} ; 
    lastMovement = "IDLE" ; 
    initSprites();
    
}

Player::~Player() 
{
    // Destructor for Player, if needed
}





void Player::render(sf::RenderTarget* target){
    target->draw(this->sprite);
}

/*
*   This is the function that makes the hero move. 
*   Arguments : dir_x and dir_y values are keyboard inputs
*   For correct behaviour only use this functions with   
*   dir_x belonging to [-1;1]
*   dir_y belonging to [-1;1]
*   Note: you only enter this function when Z,Q,S or D is pressed.
*/
void Player::move(const float& deltaTime, const float dir_x, const float dir_y){

    if(dir_x == 0.f && dir_y == 0.f) nextSpriteIDLE();
    else nextSprite(dir_x, dir_y);
    

    sprite.move(dir_x*movementSpeed*deltaTime,dir_y*movementSpeed*deltaTime);
    pos = sprite.getPosition(); // update current position of player
}

void Player::nextSprite(float dir_x, float dir_y){
    static int cyclePos = 0 ; // position in the current movement cycle (0->5)
    static int i = 0 ; 
    int repeat = 4 ; // number of times each sprite is repeated, used to slow down the 6 frame movement cycle
    std::string movement ; // most up to date Movement request from user

    // HANDLE FRAME CYCLES //

    // Determine movement direction based on dir_x and dir_y (user input)
    if(dir_x == 0.f && dir_y == -1.f){movement = "UP";}
    else if(dir_x == -1.f && dir_y == 0.f){movement = "LEFT";}
    else if(dir_x == 1.f && dir_y == 0.f){movement = "RIGHT";}
    else if(dir_x == 0.f && dir_y == 1.f){movement = "DOWN";}
    else{
        std::cerr << "[Player::nextSprite] Unhandled dirx,dir_y combination \n";
    }

    // hero walks in the same direction as last input
    if(lastMovement == movement){ 
        if(i < repeat) i++ ; // do nothing to slow down display a little
        else{ // take next sprite of same direction
            i = 0 ; 
            sprite = spriteMap[movement][cyclePos] ;
            sprite.setPosition(pos);
            cyclePos++;
            if(cyclePos >= 6) cyclePos = 0 ; // reset counter to not go outside the bounds of sprtUP
        }
    }
    // hero changes direction
    else{
        cyclePos = 0 ; // reset counter 
        sprite = spriteMap[movement][cyclePos] ;
        sprite.setPosition(pos);
        cyclePos++;
        lastMovement = movement;
    }
    return;
}


void Player::nextSpriteIDLE()
{
    std::string movement = "IDLE";
    // if already IDLE, do nothing
    if(lastMovement == movement){return;}
    else{
        if(lastMovement =="UP") sprite = spriteMap[movement][3];
        else if(lastMovement =="DOWN") sprite = spriteMap[movement][0];
        else if(lastMovement == "LEFT") sprite = spriteMap[movement][1];
        else if(lastMovement == "RIGHT") sprite = spriteMap[movement][2];
        else{std::cout << "[Player::nextSpriteIDLE] lastMovement unknown \n";}
        sprite.setPosition(pos);
    }
    return ;
}


