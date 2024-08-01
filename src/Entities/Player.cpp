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

    int nbMvtIDLE = 4 ; // number of movements for hero being IDLE
    int nbMvtUP = 6 ; // number of movements for hero going UP
    int nbMvtDOWN = 6 ; // number of movements for hero going DOWN
    int nbMvtLEFT = 6 ; // number of movements for hero going LEFT
    int nbMvtRIGHT = 6 ; // number of movements for hero going RIGHT

    std::string filename,imagesFolder,imagesPlayerFolder;
    std::string currentPath = "./" ;
    imagesFolder = "ressources/Images/" ;
    imagesPlayerFolder = "Player/Moves/" ; 
    std::string folderPath = currentPath+imagesFolder+imagesPlayerFolder; 

    // LOAD EVERY TEXTURE NECESSARY FOR HERO MOVEMENT //
    // IDLE:
    for(int i = 0 ; i < nbMvtIDLE ; i++){
        filename = "IDLE_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrIDLE[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image IDLE_" + std::to_string(i) + " was not found \n" ;
            //std::filesystem::path currentPath = std::filesystem::current_path();
            //std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }
    // UP:
    for(int i = 0 ; i < nbMvtUP ; i++){
        filename = "UP_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrUP[i].loadFromFile((folderPath+filename))){
            std::cerr << "The image UP_" + std::to_string(i) + " was not found \n" ;
            //std::filesystem::path currentPath = std::filesystem::current_path();
            //std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }
    // LEFT:
    for(int i = 0 ; i < nbMvtLEFT ; i++){
        filename = "LEFT_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrLEFT[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image LEFT_" + std::to_string(i) + " was not found \n" ;
            //std::filesystem::path currentPath = std::filesystem::current_path();
            //std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }
    // RIGHT:
    for(int i = 0 ; i < nbMvtRIGHT ; i++){
        filename = "RIGHT_" + std::to_string(i+1) + ".png"; // be careful to name the pictures in the Images/Moves folder as defined below
        if(!this->txtrRIGHT[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image RIGHT_" + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }
    // DOWN:
    for(int i = 0 ; i < nbMvtDOWN ; i++){
        filename = "DOWN_" + std::to_string(i+1) + ".png"; // be careful to name the pictures in the Images/Moves folder as defined below
        if(!this->txtrDOWN[i].loadFromFile(folderPath+filename)){
            std::cerr << "The image DOWN_" + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }

    // ASSOCIATE A SPRITE WITH EACH TEXTURE TO DISPLAY LATER //

    for(int i = 0 ; i < nbMvtIDLE ; i++){
        this->sprtIDLE[i].setTexture(this->txtrIDLE[i]);
    }
    for(int i = 0 ; i < nbMvtDOWN ; i++){
        this->sprtDOWN[i].setTexture(this->txtrDOWN[i]);
    }
    for(int i = 0 ; i < nbMvtUP ; i++){
        this->sprtUP[i].setTexture(this->txtrUP[i]);
    }
    for(int i = 0 ; i < nbMvtLEFT ; i++){
        this->sprtLEFT[i].setTexture(this->txtrLEFT[i]);
    }
    for(int i = 0 ; i < nbMvtRIGHT ; i++){
        this->sprtRIGHT[i].setTexture(this->txtrRIGHT[i]);
    }

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
    static char lastMvmt = 'I' ; // initiated as IDLE down
    static int cyclePos = 0 ; // position in the current movement cycle (0->5)
    static int i = 0 ; 
    int repeat = 4 ; // number of times each sprite is repeated, used to slow down the 6 frame movement cycle

    // HANDLE FRAME CYCLES //

     // player going UP:
    if(dir_x == 0.f && dir_y == -1.f){
        // if already walking UP:
        if(lastMvmt == 'U'){ 
            if(i < repeat) i++ ;
            else{
                i = 0 ; 
                sprtUP[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtUP[cyclePos];
                cyclePos++;
                if(cyclePos >= 6) cyclePos = 0 ; // reset counter to not go outside the bounds of sprtUP
            }
        }
        // was not walking UP before:
        else{
            cyclePos = 0 ; // reset counter 
            sprtUP[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtUP[cyclePos];
            cyclePos++;
            lastMvmt = 'U';
        }
    }
    // player going LEFT:
    else if(dir_x == -1.f && dir_y == 0.f){
        // if already walking LEFT:
        if(lastMvmt == 'L'){ 
            if(i < repeat) i++ ;
            else{
                i = 0 ; 
                sprtLEFT[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtLEFT[cyclePos];
                cyclePos++;
                if(cyclePos >= 6) cyclePos = 0 ; 
            }
        }
        // was not walking UP before:
        else{
            cyclePos = 0 ; // reset counter 
            sprtLEFT[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtLEFT[cyclePos];
            cyclePos++;
            lastMvmt = 'L';
        }
    }
    // player going RIGHT:
    else if(dir_x == 1.f && dir_y == 0.f){
        // if already walking RIGHT:
        if(lastMvmt == 'R'){ 
            if(i < repeat) i++ ;
            else{
                i = 0 ; 
                sprtRIGHT[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtRIGHT[cyclePos];
                cyclePos++;
                if(cyclePos >= 6) cyclePos = 0 ;
            }
        }
        // was not walking RIGHT before:
        else{
            cyclePos = 0 ; // reset counter 
            sprtRIGHT[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtRIGHT[cyclePos];
            cyclePos++;
            lastMvmt = 'R';
        }
    }
    // player going DOWN:
    else if(dir_x == 0.f && dir_y == 1.f){
        // if already walking DOWN:
        if(lastMvmt == 'D'){ 
            if(i < repeat) i++ ;
            else{
                i = 0 ; 
                sprtDOWN[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtDOWN[cyclePos];
                cyclePos++;
                if(cyclePos >= 6) cyclePos = 0 ;
            }
        }
        // was not walking DOWN before:
        else{
            cyclePos = 0 ; // reset counter 
            sprtDOWN[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtDOWN[cyclePos];
            cyclePos++;
            lastMvmt = 'D';
        }
   }
   // player going IDLE:
   else if(dir_x == 0.f && dir_y == 0.f){
        // was walking DOWN:
        if(lastMvmt == 'D'){ 
            sprtIDLE[0].setPosition(this->pos);
            this->playerSprite= sprtIDLE[0];
        }
        // was walking LEFT:
        else if(lastMvmt == 'L'){
            sprtIDLE[1].setPosition(this->pos);
            this->playerSprite= sprtIDLE[1];         
        }
        // was walking RIGHT:
        else if(lastMvmt == 'R'){
            sprtIDLE[2].setPosition(this->pos);
            this->playerSprite= sprtIDLE[2];           
        }
        // was walking UP:
        else{
            sprtIDLE[3].setPosition(this->pos);
            this->playerSprite= sprtIDLE[3];
        }
   }

    // ACTUALLY MOVE THE PLAYER'S SPRITE //

    this->playerSprite.move(dir_x*this->movementSpeed*dt,dir_y*this->movementSpeed*dt);
    this->pos = playerSprite.getPosition(); // update current position of player
}

