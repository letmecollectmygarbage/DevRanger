#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    // Add any additional member variables specific to the Player class here
    // sprites for all directions

    std::array<sf::Sprite, 6> sprtIDLE ; // made it the same size bc I need to put them in a map  
    std::array<sf::Sprite, 6> sprtUP ; 
    std::array<sf::Sprite, 6> sprtDOWN ; 
    std::array<sf::Sprite, 6> sprtLEFT ; 
    std::array<sf::Sprite, 6> sprtRIGHT ; 
    // Map to link sprite arrays to their movement directions
    std::map<std::string, std::array<sf::Sprite, 6>> spriteMap;

    // textures for all directions
    std::array<sf::Texture, 4> txtrIDLE ;  
    std::array<sf::Texture, 6> txtrUP ; 
    std::array<sf::Texture, 6> txtrDOWN ; 
    std::array<sf::Texture, 6> txtrLEFT ; 
    std::array<sf::Texture, 6> txtrRIGHT ; 
    
    sf::Sprite playerSprite ; // the player that the user can move
    sf::Vector2f pos; // position of the player 
    std::string lastMvmt;


public:
    Player();
    ~Player();
    int initPlayerSprites();
    void render(sf::RenderTarget* target);
    void move(const float& dt, const float dir_x,const float dir_y);
    void nextSprite(float dir_x, float dir_y);
    //void Player::setPlayerSprite();
    // Add any additional member functions specific to the Player class here
};

#endif

