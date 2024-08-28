#include "Player.h"

// Constructor. Initializes player attributes and sprites. 
Player::Player() 
{
    movements = {"IDLE","UP","DOWN","LEFT","RIGHT"}; 
    imagesPerMovement = 6 ; // according to what I have in Images/Player/Moves
    movementSpeed = 300.f ; 
    health = 100 ; 
    numberOfDifferentMovements = 5 ; // idle, left,right,up,down
    width = 50.f ; 
    height = 50.f ; 
    size = {width,height}; 
    shape.setSize(size); 
    initialX = 400.f ;
    initialY = 400.f ;  
    initialPos = {initialX,initialY} ; 
    lastMovement = "IDLE" ; 
    entityImagesFolder = "Player/Moves/" ; // 40x64 px
    initSprites(); // to call last, after all attributes are set
    init_life_display();

}

Player::~Player() 
{
    // Destructor for Player, if needed
}

void Player::render(sf::RenderTarget* target){
    target->draw(this->sprite);
    for(sf::Sprite heart : this->health_hearts){
        target->draw(heart);
    }
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
    float k = 0 ; 
    if(dir_x == 0.f && dir_y == 0.f) nextSpriteIDLE();
    else nextSprite(dir_x, dir_y);

    sprite.move(dir_x*movementSpeed*deltaTime,dir_y*movementSpeed*deltaTime);
    pos = sprite.getPosition(); // update current position of player
    // update positions of hearts 
    float width_heart = health_hearts[0].getGlobalBounds().getSize().x ; 
    // dispose 3 hearts horizontally 
    for(int i = 0 ; i < 3 ; i++){
        float x = pos.x+(width_heart*k) + 100.f ; 
        health_hearts[i].setPosition(x,pos.y-100);
        k++;
    }
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


void Player::init_life_display(){
    // Initialize the life display of the hero
    std::string path_to_heart_img = "./"+imagesFolder+"Player/heart.png";
    sf::Sprite heart_sprite ;
    sf::Vector2f pos_player = sprite.getPosition();
    if(!heart_texture.loadFromFile(path_to_heart_img)){
        std::cout << "Player constructor failed loading img from : " << path_to_heart_img << "\n";
        return ;
    }
    else{std::cout << "Player() : heart texture loaded from : "<<"./"+imagesFolder+"Player/heart.png \n";}
    heart_texture.setSmooth(true); // blurs edges
    heart_sprite.setTexture(heart_texture); 
    float width_heart = heart_sprite.getGlobalBounds().getSize().x ; 
    // dispose 3 hearts horizontally 
    for(float i = 0 ; i < 3 ; i++){
        heart_sprite.setPosition(pos_player.x+(width_heart*i),pos_player.y-100);
        health_hearts.push_back(heart_sprite);
    }
}