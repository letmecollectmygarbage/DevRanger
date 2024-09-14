#include "GameTile.h"

/*
* @brief Creates a GameTile instance.
* The resulting object is essentially a vector of sprites with attribute to say if it's free (walkable) or not. 
* @param pathImg (std::string): path to the image which defines my texture
* @return True if texture is found, False otherwise.
*/
GameTile::GameTile(std::string pathImg, int numSprites, sf::Vector2f pos, bool isFree)
    : numSprites{numSprites}
    , pos{pos}
    , isFree{isFree}
{
    // image file not found
    if(!setUpSprite(pathImg)) return ;
    for(int i = 0 ; i < numSprites ; i++){
        sprites[i].setPosition(pos); // TODO: remove this
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