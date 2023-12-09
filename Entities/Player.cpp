#include "Player.h"

Player::Player() 
{
    this->shape.setSize(sf::Vector2f(50.f,50.f));
    this->movementSpeed = 300.f ;
    initPlayerSprites();
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
                            4 full left step 
                            5 half left step
                            6 full right step
                            7 half right step
                        // going right //
                            8 full left step
                            9 half left step
                            10 full right step
                            11 half right step
                        // going up //
                            12 right step
                            13 left step
                        // going down //
                            14 right step
                            15 left step
                    
    *   @return : -1 if at least one image file was not found
    *              0 if all good 
    *
    */
    int nbMovements = 16 ; // 16 sprites necessary to display every moving positions (going down, up, steps, ...)
    std::string filename,folder;
    folder = "../Images/" ; // TODO : find a more sustainable way to manage paths
    for(int i = 0 ; i < nbMovements ; i++)
    {
        
        filename = "hero" + std::to_string(i) + ".png"; // be careful to name the pictures in the Images folder as defined below
        if(!this->mvmtTextures[i].loadFromFile(filename))
        {
            std::cerr << "The image " + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }
    for(int i = 0 ; i < nbMovements ; i++)
    {
        this->mvmtSprites[i].setTexture(this->mvmtTextures[i]);
    }
    return 0 ;


}

// Implement any additional member functions for the Player class if needed
