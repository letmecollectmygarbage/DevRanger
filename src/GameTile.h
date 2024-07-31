#include "Entities/Entity.h"

#ifndef GAMETILE_H
#define GAMETILE_H


class GameTile
{
    public : 
        bool isFree ; // we can pass through it
        bool isExit ; 
        sf::Vector2f pos ;
        sf::Texture texture ; 
        sf::Sprite sprite ;
        GameTile(std::string textureName, sf::Vector2f pos,bool isFree, bool isExit,float scaleFactor, bool resize);
        bool setUpSprite(std::string, float scaleFactor, bool resize); // set up sprites and resize texture if needed
        sf::Texture resizeTexture(const sf::Texture& originalTexture, float scaleFactor) ;

};

#endif