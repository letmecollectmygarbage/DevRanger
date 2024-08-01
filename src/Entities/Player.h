#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:

    // Map to link sprite arrays to their movement directions
    std::map<std::string, std::array<sf::Sprite, 6>> spriteMap;

    // Map to link texture arrays to their movement directions
    std::map<std::string, std::array<sf::Texture, 6>> textureMap;


    
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
};

#endif

