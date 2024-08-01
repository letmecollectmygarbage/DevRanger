#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    // Add any additional member variables specific to the Player class here
    // sprites for all directions
    std::array<sf::Sprite, 4> sprtIDLE ;  
    std::array<sf::Sprite, 6> sprtUP ; 
    std::array<sf::Sprite, 6> sprtDOWN ; 
    std::array<sf::Sprite, 6> sprtLEFT ; 
    std::array<sf::Sprite, 6> sprtRIGHT ; 

    // textures for all directions
    std::array<sf::Texture, 4> txtrIDLE ;  
    std::array<sf::Texture, 6> txtrUP ; 
    std::array<sf::Texture, 6> txtrDOWN ; 
    std::array<sf::Texture, 6> txtrLEFT ; 
    std::array<sf::Texture, 6> txtrRIGHT ; 
    
    sf::Sprite playerSprite ; // the player that the user can move
    sf::Vector2f pos; // position of the player 


public:
    Player();
    ~Player();
    int initPlayerSprites();
    void render(sf::RenderTarget* target);
    void move(const float& dt, const float dir_x,const float dir_y);
    // Add any additional member functions specific to the Player class here
};

#endif

