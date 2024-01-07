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

int Player::initPlayerSprites()
{

    int nbMvtIDLE = 4 ; // "number of sprites necessary to represent the hero" IDLE in every direction
    int nbMvtUP = 6 ; // "..." moving up
    int nbMvtDOWN = 6 ; // "..." moving down
    int nbMvtLEFT = 6 ; // "..." moving left
    int nbMvtRIGHT = 6 ; // "..." moving right

    std::string filename,imagesFolder,imagesPlayerFolder;
    std::filesystem::path currentPath = std::filesystem::current_path();
    imagesFolder = "Images" ;
    imagesPlayerFolder = "Player/Moves" ; 
    std::filesystem::path folderPath = currentPath/imagesFolder/imagesPlayerFolder; 

    // LOAD EVERY TEXTURE NECESSARY FOR HERO MOVEMENT //

    for(int i = 0 ; i < nbMvtIDLE ; i++) // IDLE
    {
        filename = "IDLE_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrIDLE[i].loadFromFile(folderPath/filename))
        {
            std::cerr << "The image IDLE_" + std::to_string(i) + " was not found \n" ;
            std::filesystem::path currentPath = std::filesystem::current_path();
            std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }
    for(int i = 0 ; i < nbMvtUP ; i++) // UP
    {
        filename = "UP_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrUP[i].loadFromFile(folderPath/filename))
        {
            std::cerr << "The image UP_" + std::to_string(i) + " was not found \n" ;
            std::filesystem::path currentPath = std::filesystem::current_path();
            std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }

    for(int i = 0 ; i < nbMvtLEFT ; i++) // LEFT
    {
        filename = "LEFT_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrLEFT[i].loadFromFile(folderPath/filename))
        {
            std::cerr << "The image LEFT_" + std::to_string(i) + " was not found \n" ;
            std::filesystem::path currentPath = std::filesystem::current_path();
            std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }

    for(int i = 0 ; i < nbMvtRIGHT ; i++) // RIGHT
    {
        filename = "RIGHT_" + std::to_string(i+1) + ".png"; // be careful to name the pictures in the Images/Moves folder as defined below
        if(!this->txtrRIGHT[i].loadFromFile(folderPath/filename))
        {
            std::cerr << "The image RIGHT_" + std::to_string(i) + " was not found \n" ;
            std::filesystem::path currentPath = std::filesystem::current_path();
            std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }

    for(int i = 0 ; i < nbMvtDOWN ; i++) // DOWN
    {
        filename = "DOWN_" + std::to_string(i+1) + ".png"; // be careful to name the pictures in the Images/Moves folder as defined below
        if(!this->txtrDOWN[i].loadFromFile(folderPath/filename))
        {
            std::cerr << "The image DOWN_" + std::to_string(i) + " was not found \n" ;
            std::filesystem::path currentPath = std::filesystem::current_path();
            std::cout << "Current working directory: " << currentPath.string() << std::endl;
            return -1 ; 
        }
    }

    // ASSOCIATE A SPRITE WITH EACH TEXTURE TO DISPLAY LATER //

    for(int i = 0 ; i < nbMvtIDLE ; i++)
    {
        this->sprtIDLE[i].setTexture(this->txtrIDLE[i]);
    }
    for(int i = 0 ; i < nbMvtDOWN ; i++)
    {
        this->sprtDOWN[i].setTexture(this->txtrDOWN[i]);
    }
    for(int i = 0 ; i < nbMvtUP ; i++)
    {
        this->sprtUP[i].setTexture(this->txtrUP[i]);
    }
    for(int i = 0 ; i < nbMvtLEFT ; i++)
    {
        this->sprtLEFT[i].setTexture(this->txtrLEFT[i]);
    }
    for(int i = 0 ; i < nbMvtRIGHT ; i++)
    {
        this->sprtRIGHT[i].setTexture(this->txtrRIGHT[i]);
    }

    // DEFINE DEFAULT POSITION FOR HERO
    playerSprite = sprtIDLE[0] ; // IDLE facing down
    std::cerr << "[INFO] initPlayerSprites() achieved" << "\n" ; 
    return 0 ;
}

// Implement any additional member functions for the Player class if needed

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->playerSprite);
}

void Player::move(const float& dt, const float dir_x, const float dir_y)
{
    /*
    *   This is the function that makes the hero move. 
    *   Arguments : dir_x and dir_y values are keyboard inputs
    *   For correct behaviour only use this functions with   
    *   dir_x belonging to [-1;1]
    *   dir_y belonging to [-1;1]
    */
    static char lastMvmt = 'I' ; // initiated as IDLE down
    static int cyclePos = 0 ; // position in the current movement cycle (0->5)
    static int i = 0 ; 
    int repeat = 16 ; // number of times each sprite is repeated, used to slow down the 6 frame movement cycle
    if(dir_x == 0.f && dir_y == -1.f) // player going UP
    {
        if(lastMvmt == 'U') // if already walking UP
        { 
            if(i < repeat)
            {
                i++ ;
            }
            else
            {
                i = 0 ; 
                sprtUP[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtUP[cyclePos];
                cyclePos++;
                if(cyclePos >= 6) cyclePos = 0 ; // reset counter to not go outside the bounds of sprtUP
            }
        }
        else // was not walking UP before
        {
            cyclePos = 0 ; // reset counter 
            sprtUP[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtUP[cyclePos];
            cyclePos++;
            lastMvmt = 'U';
        }
    }
    else if(dir_x == -1.f && dir_y == 0.f) // player going LEFT
    {
        if(lastMvmt == 'L') // if already walking LEFT
        { 
            if(i < repeat)
            {
                i++ ;
            }
            else
            {
                i = 0 ; 
                sprtLEFT[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtLEFT[cyclePos];
                cyclePos++;
            if(cyclePos >= 6) cyclePos = 0 ; 
            }
        }
        else// was not walking UP before
        {
            cyclePos = 0 ; // reset counter 
            sprtLEFT[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtLEFT[cyclePos];
            cyclePos++;
            lastMvmt = 'L';
        }
   }
    else if(dir_x == 1.f && dir_y == 0.f) // player going RIGHT
        if(lastMvmt == 'R') // if already walking RIGHT
        { 
            if(i < repeat)
            {
                i++ ;
            }
            else
            {
                i = 0 ; 
                sprtRIGHT[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtRIGHT[cyclePos];
                cyclePos++;
                if(cyclePos >= 6) cyclePos = 0 ;
            }
        }
        else// was not walking RIGHT before
        {
            cyclePos = 0 ; // reset counter 
            sprtRIGHT[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtRIGHT[cyclePos];
            cyclePos++;
            lastMvmt = 'R';
        }
    else if(dir_x == 0.f && dir_y == 1.f) // player going DOWN
   {
        if(lastMvmt == 'D') // if already walking DOWN
        { 
            if(i < repeat)
            {
                i++ ;
            }
            else
            {
                i = 0 ; 
                sprtDOWN[cyclePos].setPosition(this->pos);
                this->playerSprite= sprtDOWN[cyclePos];
                cyclePos++;
                if(cyclePos >= 6) cyclePos = 0 ;
            }
        }
        else// was not walking DOWN before
        {
            cyclePos = 0 ; // reset counter 
            sprtDOWN[cyclePos].setPosition(this->pos);
            this->playerSprite= sprtDOWN[cyclePos];
            cyclePos++;
            lastMvmt = 'D';
        }
   }
   else if(dir_x == 0.f && dir_y == 0.f) // player goes IDLE
   {
        if(lastMvmt == 'R') // was walking DOWN
        { 
            sprtIDLE[0].setPosition(this->pos);
            this->playerSprite= sprtIDLE[0];
        }
        else if(lastMvmt == 'L') // was walking LEFT
        {
            sprtIDLE[1].setPosition(this->pos);
            this->playerSprite= sprtIDLE[1];            
        }
        else if(lastMvmt == 'R') // was walking RIGHT
        {
            sprtIDLE[2].setPosition(this->pos);
            this->playerSprite= sprtIDLE[2];            
        }
        else
        {
            sprtIDLE[3].setPosition(this->pos);
            this->playerSprite= sprtIDLE[3];
        }
   }
//    else // player is trying to move diagonally : block him in IDLE down
//    {
//     sprtIDLE[0].setPosition(this->pos);
//     this->playerSprite= sprtIDLE[0];
//    }
   if ( (dir_x == 0.f) ^ (dir_y == 0.f) ) // ensure hero cannot move in diagonal (^ = XOR)
   {
        this->playerSprite.move(dir_x*this->movementSpeed*dt,dir_y*this->movementSpeed*dt);
        this->pos = playerSprite.getPosition(); // update current position of player
   }
}

