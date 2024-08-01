#include "Player.h"

Player::Player() 
{
    this->shape.setSize(sf::Vector2f(50.f,50.f));
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
    int nbMvt = 6 ; 


    std::string filename,imagesFolder,imagesPlayerFolder;
    std::string currentPath = "./" ;
    imagesFolder = "ressources/Images/" ;
    imagesPlayerFolder = "Player/Moves/" ; 
    std::string folderPath = currentPath+imagesFolder+imagesPlayerFolder; 
    this->lastMvmt = "IDLE" ; // initiated as IDLE down
    // LOAD EVERY TEXTURE NECESSARY FOR HERO MOVEMENT //
    // IDLE:
    for(int i = 0 ; i < nbMvt ; i++){
        filename = "IDLE_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrIDLE[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image IDLE_" + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }
    // UP:
    for(int i = 0 ; i < nbMvt ; i++){
        filename = "UP_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrUP[i].loadFromFile((folderPath+filename))){
            std::cerr << "The image UP_" + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }
    // LEFT:
    for(int i = 0 ; i < nbMvt ; i++){
        filename = "LEFT_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrLEFT[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image LEFT_" + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }
    // RIGHT:
    for(int i = 0 ; i < nbMvt ; i++){
        filename = "RIGHT_" + std::to_string(i+1) + ".png"; // be careful to name the pictures in the Images/Moves folder as defined below
        if(!this->txtrRIGHT[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image RIGHT_" + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }
    // DOWN:
    for(int i = 0 ; i < nbMvt ; i++){
        filename = "DOWN_" + std::to_string(i+1) + ".png"; // be careful to name the pictures in the Images/Moves folder as defined below
        if(!this->txtrDOWN[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image DOWN_" + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }

    // ASSOCIATE A SPRITE WITH EACH TEXTURE TO DISPLAY LATER //

    for(int i = 0 ; i < nbMvt ; i++){
        this->sprtIDLE[i].setTexture(this->txtrIDLE[i]);
    }
    for(int i = 0 ; i < nbMvt ; i++){
        this->sprtDOWN[i].setTexture(this->txtrDOWN[i]);
    }
    for(int i = 0 ; i < nbMvt ; i++){
        this->sprtUP[i].setTexture(this->txtrUP[i]);
    }
    for(int i = 0 ; i < nbMvt ; i++){
        this->sprtLEFT[i].setTexture(this->txtrLEFT[i]);
    }
    for(int i = 0 ; i < nbMvt ; i++){
        this->sprtRIGHT[i].setTexture(this->txtrRIGHT[i]);
    }
    // Add sprite arrays to the map
    this->spriteMap["IDLE"] = sprtIDLE;
    this->spriteMap["UP"] = sprtUP;
    this->spriteMap["DOWN"] = sprtDOWN;
    this->spriteMap["LEFT"] = sprtLEFT;
    this->spriteMap["RIGHT"] = sprtRIGHT;

    // DEFINE DEFAULT POSITION FOR HERO:
    playerSprite = sprtIDLE[0] ; // IDLE facing down
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