#include "GameTile.h"

/*
* @brief Creates a GameTile instance. 
*
* The resulting object is essentially a sprite with attributes to say if it's free (walkable) or 
* an exit (to give access to another area of the map for example). 
* 
* @param textureFilename (std::string): name of the texture I want to apply on my sprite
* @param scaleFactor (float): Original dimensions will be multiplied by this factor. 
* @param resize (bool): If enabled, the sprite will be resized.
* @return True if texture is found, False otherwise.
*/
GameTile::GameTile(std::string textureName,int numSprites, sf::Vector2f pos, bool isFree){

    this->numSprites = numSprites ; 
    this->pos = pos ; 
    this->isFree = isFree ; 

    if(!setUpSprite(textureName)){
        // image file not found
        return ; 
    }
    // after this point, the sprite vector is created with appropriate texture
    for(int i = 0 ; i < numSprites ; i++){
        sprites[i].setPosition(pos); // stack them all on the same pos first
    }
}

/*
* @brief Associates a sf::sprite to a sf::texture. 
*
* Applies the texture attribute to the sprite attribute. If resize 
* is enabled, the texture is first resized. 
* 
* @param textureFilename (std::string): filename (filepath) of the texture 
* @return True if texture is found, False otherwise.
*/
bool GameTile::setUpSprite(std::string textureFilename){

    sf::Sprite sprite ; 
    if(!texture.loadFromFile(textureFilename)) return false; // loading image failed
    texture.setSmooth(true); // blurs edges
    for(int i = 0 ; i < numSprites ; i++){
        sprite.setTexture(texture);
        sprites.push_back(sprite);
    }
    return true;
}