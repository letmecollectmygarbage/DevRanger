#ifndef PLAYER_H
#define PLAYER_H
#define NB_TEXTURES_PLAYER 16 // 16 sprites necessary to display every moving positions (going down, up, ...) 
                                // TODO : remove this is C style and ugly

#include "Entity.h"

class Player : public Entity {
private:
    // Add any additional member variables specific to the Player class here
    std::array<sf::Sprite, NB_TEXTURES_PLAYER> mvmtSprites ;  
    std::array<sf::Texture,NB_TEXTURES_PLAYER> mvmtTextures ;


public:
    Player();
    ~Player();
    int initPlayerSprites();

    // Add any additional member functions specific to the Player class here
};

#endif
