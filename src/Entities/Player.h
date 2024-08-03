#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    
    

    



public:
    Player();
    ~Player();
    
    void render(sf::RenderTarget* target);
    void move(const float& deltaTime, const float dir_x,const float dir_y);
    void nextSprite(float dir_x, float dir_y);
    void nextSpriteIDLE();
};

#endif

