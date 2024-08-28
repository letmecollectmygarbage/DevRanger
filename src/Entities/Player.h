#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    sf::Texture heart_texture ; // original img of a 2D heart 
    std::vector<sf::Sprite> health_hearts ; 
    

public:
    Player();
    ~Player();
    
    void move(const float& deltaTime, const float dir_x,const float dir_y);
    void nextSprite(float dir_x, float dir_y);
    void nextSpriteIDLE();
    void render(sf::RenderTarget* target);
    void init_life_display();
};

#endif

