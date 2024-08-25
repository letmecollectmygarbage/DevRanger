#include "../Entities/Entity.h"

#ifndef GAMETILE_H
#define GAMETILE_H


class GameTile
{
    public : 
        sf::Vector2f pos ; // probably to remove
        int numSprites ; // number of sprites in the vector
        bool isFree ; 
        std::vector<sf::Sprite> sprites ; // vector of sprites sharing the same texture
        sf::Texture texture ; 
        /// Methods ///
        // constructor 

        GameTile(std::string textureName,int numSprites, sf::Vector2f pos, bool isFree);
        bool setUpSprite(std::string textureFilename); // set up sprites and resize texture if needed
};

#endif