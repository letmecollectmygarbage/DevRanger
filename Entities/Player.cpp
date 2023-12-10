#include "Player.h"

Player::Player() 
{
    this->shape.setSize(sf::Vector2f(50.f,50.f));
    this->movementSpeed = 100.f ;
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
    folder = "Images/" ; // TODO : find a more sustainable way to manage paths
    for(int i = 0 ; i < nbMovements ; i++)
    {
        
        filename = "hero" + std::to_string(i) + ".png"; // be careful to name the pictures in the Images folder as defined below
        if(!this->mvmtTextures[i].loadFromFile(folder+filename))
        {
            std::cerr << "The image " + std::to_string(i) + " was not found \n" ;
            return -1 ; 
        }
    }
    for(int i = 0 ; i < nbMovements ; i++)
    {
        this->mvmtSprites[i].setTexture(this->mvmtTextures[i]);
    }
    playerSprite = mvmtSprites[2];
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
   static int lastMvmt ; // last movement sprite of player 
   
   if(dir_x == 0.f && dir_y == -1.f) // player going up
   {
        if(lastMvmt == 0)
        { // start walking up
            mvmtSprites[12].setPosition(this->pos);
            this->playerSprite= mvmtSprites[12];
            lastMvmt = 12;
        }
        else if(lastMvmt==12)
        { // alternating foot
            mvmtSprites[13].setPosition(this->pos);
            this->playerSprite= mvmtSprites[13];
            lastMvmt = 13;
        }
        else if(lastMvmt==13)
        { // alternating foot
            mvmtSprites[12].setPosition(this->pos);
            this->playerSprite= mvmtSprites[12]; 
            lastMvmt = 12;
        }
        else // player was not going up before
        {
            mvmtSprites[0].setPosition(this->pos);
            this->playerSprite= mvmtSprites[0]; // IDLE UP
            lastMvmt = 0;
        }
   }
    else if(dir_x == -1.f && dir_y == 0.f) // player going left 
   {
        if(lastMvmt == 3)
        { // start walking left
            mvmtSprites[4].setPosition(this->pos);
            this->playerSprite= mvmtSprites[4];
            lastMvmt = 4;
        }
        else if(lastMvmt==4)
        { // alternating foot
            mvmtSprites[5].setPosition(this->pos);
            this->playerSprite= mvmtSprites[5];
            lastMvmt = 5;
        }
        else if(lastMvmt==5)
        { // alternating foot
            mvmtSprites[6].setPosition(this->pos);
            this->playerSprite= mvmtSprites[6]; 
            lastMvmt = 6;
        }
        else if(lastMvmt==6)
        { // alternating foot
            mvmtSprites[7].setPosition(this->pos);
            this->playerSprite= mvmtSprites[7]; 
            lastMvmt = 7;
        }
        else // player was not facing left before
        {
            mvmtSprites[3].setPosition(this->pos);
            this->playerSprite= mvmtSprites[3]; // IDLE LEFT
            lastMvmt = 3;
        }
   }
    else if(dir_x == 1.f && dir_y == 0.f) // player going right 
        if(lastMvmt == 1)
        { // start walking right
            mvmtSprites[8].setPosition(this->pos);
            this->playerSprite= mvmtSprites[8];
            lastMvmt = 8;
        }
        else if(lastMvmt==8)
        { // alternating foot
            mvmtSprites[9].setPosition(this->pos);
            this->playerSprite= mvmtSprites[9];
            lastMvmt = 9;
        }
        else if(lastMvmt==9)
        { // alternating foot
            mvmtSprites[10].setPosition(this->pos);
            this->playerSprite= mvmtSprites[10]; 
            lastMvmt = 10;
        }
        else if(lastMvmt==10)
        { // alternating foot
            mvmtSprites[11].setPosition(this->pos);
            this->playerSprite= mvmtSprites[11]; 
            lastMvmt = 11;
        }
        else // player was not facing right before
        {
            mvmtSprites[1].setPosition(this->pos);
            this->playerSprite= mvmtSprites[1]; // IDLE RIGHT
            lastMvmt = 1;
        }
    else if(dir_x == 0.f && dir_y == 1.f) // player going down 
   {
        if(lastMvmt == 2)
        { // start walking down
            mvmtSprites[14].setPosition(this->pos);
            this->playerSprite= mvmtSprites[14];
            lastMvmt = 14;
        }
        else if(lastMvmt==14)
        { // alternating foot
            mvmtSprites[15].setPosition(this->pos);
            this->playerSprite= mvmtSprites[15];
            lastMvmt = 15;
        }
        else // player was not facing down before
        {
            mvmtSprites[2].setPosition(this->pos);
            this->playerSprite= mvmtSprites[2]; // IDLE RIGHT
            lastMvmt = 2;
        }
   }
    this->playerSprite.move(dir_x*this->movementSpeed*dt,dir_y*this->movementSpeed*dt);
    this->pos = playerSprite.getPosition(); // update current position of player
}

                        // // IDLE //
                        //     0 IDLE up
                        //     1 IDLE right
                        //     2 IDLE down
                        //     3 IDLE left
                        // // going left //
                        //     4 full left step 
                        //     5 half left step
                        //     6 full right step
                        //     7 half right step
                        // // going right //
                        //     8 full left step
                        //     9 half left step
                        //     10 full right step
                        //     11 half right step
                        // // going up //
                        //     12 right step
                        //     13 left step
                        // // going down //
                        //     14 right step
                        //     15 left step