#include "GameTile.h"

GameTile::GameTile(std::string textureName, sf::Vector2f pos, bool isFree, bool isExit)
{
    if(!setUpSprite(textureName))
    {
        return ; 
    }
    this->sprite.setPosition(pos);
    this->isFree = isFree;
    this->isExit = isExit ;
}

bool GameTile::setUpSprite(std::string textureName)
{
    if(!this->texture.loadFromFile(textureName))
    {
        return false; // loading image failed
    }
    this->texture.setSmooth(true); // blurs the edges of the texture
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0,0,50,50));
    
    return true;
}


