#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    sf::Texture heart_texture ; // original img of a 2D heart 
    std::vector<sf::Sprite> health_hearts ; 
    sf::Texture hurt_texture ; //texture to use when Player is hurt
    sf::Sprite hurt ; // sprite to use when Player is hurt
    
    std::map<std::string,std::vector<sf::Sprite>> fireball_color_sprites ; // dictionnary of fireball name (pink,red,blue) vs sprite
    std::map<std::string,std::vector<sf::Texture>> fireball_color_textures ; // dictionnary of fireball name (pink,red,blue) vs texture

    
    

public:
    Player();
    ~Player();
    
    void move(const float& deltaTime, const float dir_x,const float dir_y);
    int initSprites();
    void nextSprite(float dir_x, float dir_y);
    void nextSpriteIDLE();
    void render(sf::RenderTarget* target);
    void init_life_display();
    void manage_life_display();
    
};

#endif