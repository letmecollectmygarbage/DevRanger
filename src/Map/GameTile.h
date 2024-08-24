#include "../Entities/Entity.h"

#ifndef GAMETILE_H
#define GAMETILE_H


class GameTile
{
    public : 
        bool isFree ; // we can pass through it or not
        sf::Vector2f pos ;
        sf::Texture texture ; // what we put on the rectangle 
        sf::Sprite sprite ; // A sprite is nothing more than a textured rectangle.
        GameTile(std::string textureName, sf::Vector2f pos, bool isFree, float scaleFactor, bool resize);
        bool setUpSprite(std::string, float scaleFactor, bool resize); // set up sprites and resize texture if needed
        sf::Texture resizeTexture(const sf::Texture& originalTexture, float scaleFactor) ;

};

#endif