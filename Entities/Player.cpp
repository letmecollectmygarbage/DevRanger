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
    /*
    *   @brief :    Loads all the sprites necessary for displaying a moving player
                        // IDLE //
                            0 IDLE up
                            1 IDLE right
                            2 IDLE down
                            3 IDLE left
                        // going left //
                            4 half left step
                            5 full left step
                            6 half right step
                            7 full right step
                        // going right //
                            8 half left step
                            9 full left step
                            10 half right step
                            11 full right step
                        // going up //
                            12 half right step
                            13 full right step
                            14 half left step
                            15 full left step
                        // going down //
                            16 right step
                            17 left step              
    *   @return : -1 if at least one image file was not found
    *              0 if all good 
    */
    int nbMvtIDLE = 4 ; // 28 sprites necessary to display every moving positions (going down, up, steps, ...)
    int nbMvtUP = 6 ;
    int nbMvtDOWN = 6 ;
    int nbMvtLEFT = 6 ;
    int nbMvtRIGHT = 6 ;

    std::string filename,imagesFolder,imagesPlayerFolder;
    std::filesystem::path currentPath = std::filesystem::current_path();
    imagesFolder = "Images" ;
    imagesPlayerFolder = "Player/Moves" ; 
    std::filesystem::path folderPath = currentPath/imagesFolder/imagesPlayerFolder; 

    // LOAD EVERY NECESSARY TEXTURE FOR HERO MOVEMENT //
    for(int i = 0 ; i < nbMvtIDLE ; i++) // IDLE
    {
        filename = "IDLE_" + std::to_string(i+1) + ".png"; 
        if(!this->txtrIDLE[i].loadFromFile(folderPath/filename))
        {
            std::cerr << "The image " + std::to_string(i) + " was not found \n" ;
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
            std::cerr << "The image " + std::to_string(i) + " was not found \n" ;
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
            std::cerr << "The image " + std::to_string(i) + " was not found \n" ;
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
            std::cerr << "The image " + std::to_string(i) + " was not found \n" ;
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
            std::cerr << "The image " + std::to_string(i) + " was not found \n" ;
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
    playerSprite = sprtIDLE[0] ;
    std::cout << "Reached end of initPlayerSprites()" << "\n" ; 
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
    *       -1 <= dir_x <= 1
    *       -1 <= dir_y <= 1
    */
   static char lastMvmt = 'I' ; // initially IDLE
   static int cyclePos = 0 ; // position in the current movement cycle (0->5)
   static int repeat = 4 ; // number of times each sprite is repeated, used to slow down the display
   static int i = 0 ; 
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
        else// was not walking UP before
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
   if(dir_x==0 || dir_y==0) // ensure hero cannot move in diagonal
   {
        this->playerSprite.move(dir_x*this->movementSpeed*dt,dir_y*this->movementSpeed*dt);
        this->pos = playerSprite.getPosition(); // update current position of player
   }
}

