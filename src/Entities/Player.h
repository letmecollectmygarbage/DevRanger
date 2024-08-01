#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    
    // Map to link sprite arrays to their movement directions
    int imagesPerMovement = 6 ; // according to what I have in Images/player/Moves
    int numberOfDifferentMovements = 5 ; // also according to what I have in Images/player/Moves
    std::size_t imagesPerMovementSize = 6 ;
    std::map<std::string, std::vector<sf::Sprite>> spriteMap;
    

    // Map to link texture arrays to their movement directions
    std::map<std::string, std::vector<sf::Texture>> textureMap;

    float playerWidth = 50.f ; // player width
    float playerHeight = 50.f ; // player height
    sf::Vector2f size = sf::Vector2f(this->playerWidth,this->playerHeight); // size of the player

    float initialX = 0.f ; // Initial X position
    float initialY = 0.f ;  // Initial Y position
    sf::Vector2f initialPos = {this->initialX,this->initialY} ; // Initial position 
    
    sf::Sprite sprite ; // the player that the user can move
    sf::Vector2f pos = initialPos; // position of the player 
    std::string lastMovement;
    



public:
    Player();
    ~Player();
    int initPlayerSprites();
    void render(sf::RenderTarget* target);
    void move(const float& dt, const float dir_x,const float dir_y);
    void nextSprite(float dir_x, float dir_y);
};

#endif

