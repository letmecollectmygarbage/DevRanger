#include "Player.h"

Player::Player() 
{
    
    sf::Vector2f initialSize = sf::Vector2f(50.f,50.f);
    this->shape.setSize(initialSize); // 
    this->movementSpeed = 200.f ;
    initPlayerSprites();
    this->pos = {0.f,0.f};
}

Player::~Player() 
{
    // Destructor for Player, if needed
}

// Initializes sprites of the hero
int Player::initPlayerSprites(){
    // Number of movements for each walk cycle and IDLE. Must all be equal to use a map
    std::string mvmtID ; 



    std::string filename,imagesFolder,imagesPlayerFolder;
    std::string currentPath = "./" ;
    imagesFolder = "ressources/Images/" ;
    imagesPlayerFolder = "Player/Moves/" ; 
    std::string folderPath = currentPath+imagesFolder+imagesPlayerFolder; 
    this->lastMvmt = "IDLE" ; // initiated as IDLE down
    // LOAD EVERY TEXTURE NECESSARY FOR HERO MOVEMENT //
    // IDLE:
    
    // For every different movement
    for(int j = 0 ; j < numberOfDifferentMovements ; j++){
        // define mvmtID of image
        if(j==0){mvmtID = "IDLE";}
        else if(j==1){mvmtID = "UP";}
        else if(j==2){mvmtID = "DOWN";}
        else if(j==3){mvmtID = "LEFT";}
        else if(j==4){mvmtID = "RIGHT";}
        // For the number of sprites each movement has
        for(int i = 0 ; i < imagesPerMovement ; i++){
            filename = mvmtID + +"_"+std::to_string(i+1) + ".png" ; 
            if(!this->textureMap[mvmtID][i].loadFromFile(folderPath+filename)){
                std::cerr << "The image"+mvmtID+"_"+ std::to_string(i) + " was not found \n" ;
                return -1 ; 
            }
            this->spriteMap[mvmtID][i].setTexture(this->textureMap[mvmtID][i]);
        }
    }




    // make hero start IDLE facing the user
    playerSprite = this->spriteMap["IDLE"][0] ; // IDLE facing down
    std::cerr << "[INFO] Player::initPlayerSprites() achieved" << "\n" ; 
    return 0 ;
}

// Implement any additional member functions for the Player class if needed

void Player::render(sf::RenderTarget* target){
    target->draw(this->playerSprite);
}

/*
*   This is the function that makes the hero move. 
*   Arguments : dir_x and dir_y values are keyboard inputs
*   For correct behaviour only use this functions with   
*   dir_x belonging to [-1;1]
*   dir_y belonging to [-1;1]
*   Note: you only enter this function when Z,Q,S or D is pressed.
*/
void Player::move(const float& dt, const float dir_x, const float dir_y){

    nextSprite(dir_x, dir_y);

    this->playerSprite.move(dir_x*this->movementSpeed*dt,dir_y*this->movementSpeed*dt);
    this->pos = playerSprite.getPosition(); // update current position of player
}

void Player::nextSprite(float dir_x, float dir_y){
    static int cyclePos = 0 ; // position in the current movement cycle (0->5)
    static int i = 0 ; 
    int repeat = 4 ; // number of times each sprite is repeated, used to slow down the 6 frame movement cycle
    std::string Mvmt ; // most up to date Movement request from user

    // HANDLE FRAME CYCLES //

    // Determine Mvmt direction based on dir_x and dir_y (user input)
    if(dir_x == 0.f && dir_y == -1.f){Mvmt = "UP";}
    else if(dir_x == -1.f && dir_y == 0.f){Mvmt = "LEFT";}
    else if(dir_x == 1.f && dir_y == 0.f){Mvmt = "RIGHT";}
    else if(dir_x == 0.f && dir_y == 1.f){Mvmt = "DOWN";}



    // hero walks in the same direction as last input
    if(this->lastMvmt == Mvmt){ 
        if(i < repeat) i++ ; // do nothing to slow down display a little
        else{ // take next sprite of same direction
            i = 0 ; 
            this->playerSprite = spriteMap[Mvmt][cyclePos] ;
            this->playerSprite.setPosition(this->pos);
            cyclePos++;
            if(cyclePos >= 6) cyclePos = 0 ; // reset counter to not go outside the bounds of sprtUP
        }
    }
    // hero changes direction
    else{
        cyclePos = 0 ; // reset counter 
        this->playerSprite = spriteMap[Mvmt][cyclePos] ;
        this->playerSprite.setPosition(this->pos);
        cyclePos++;
        this->lastMvmt = Mvmt;
    }
    return;
}

