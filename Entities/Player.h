#ifndef PLAYER_H
#define PLAYER_H
#define NB_TEXTURES_PLAYER 28 // 28 sprites necessary to display every moving positions (going down, up, ...) 
                                // TODO : remove this is C style and ugly and might cause runtime errors if we add sprites in cpp file without adjusting size

#include "Entity.h"

class Player : public Entity {
private:
    // Add any additional member variables specific to the Player class here
    std::array<sf::Sprite, 4> sprtIDLE ;  
    std::array<sf::Sprite, 6> sprtUP ; 
    std::array<sf::Sprite, 6> sprtDOWN ; 
    std::array<sf::Sprite, 6> sprtLEFT ; 
    std::array<sf::Sprite, 6> sprtRIGHT ; 

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
    void move(const float& dt, const float dir_x, const float dir_y);
    // Add any additional member functions specific to the Player class here
};

#endif

