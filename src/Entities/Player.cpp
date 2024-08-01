#include "Player.h"

Player::Player() 
{
    shape.setSize(size); 
    movementSpeed = 200.f ;
    initPlayerSprites();
    
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
    lastMovement = "IDLE" ; // initiated as IDLE down
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
        // Initialize the vectors in the maps
        textureMap[mvmtID] = std::vector<sf::Texture>(imagesPerMovement);
        spriteMap[mvmtID] = std::vector<sf::Sprite>(imagesPerMovement);
        // For the number of sprites each movement has
        for(int i = 0 ; i < imagesPerMovement ; i++){
            filename = mvmtID + +"_"+std::to_string(i+1) + ".png" ; 
            if(!textureMap[mvmtID][i].loadFromFile(folderPath+filename)){
                std::cerr << "The image"+mvmtID+"_"+ std::to_string(i) + " was not found \n" ;
                return -1 ; 
            }
            spriteMap[mvmtID][i].setTexture(textureMap[mvmtID][i]);
        }
    }

    // make hero start IDLE facing the user
    sprite = spriteMap["IDLE"][0] ; // IDLE facing down
    std::cerr << "[INFO] Player::initPlayerSprites() achieved" << "\n" ; 
    return 0 ;
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
void Player::move(const float& dt, const float dir_x, const float dir_y){

    nextSprite(dir_x, dir_y);

    sprite.move(dir_x*movementSpeed*dt,dir_y*movementSpeed*dt);
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


