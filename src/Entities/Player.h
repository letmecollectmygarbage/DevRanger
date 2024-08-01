#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    
    

    



public:
    Player();
    ~Player();
    int initPlayerSprites();
    void render(sf::RenderTarget* target);
    void move(const float& dt, const float dir_x,const float dir_y);
    void nextSprite(float dir_x, float dir_y);
};

#endif

