#include "GameTile.h"

GameTile::GameTile(std::string textureName, sf::Vector2f pos, bool isFree, bool isExit, float scaleFactor, bool resize)
{
    if(!setUpSprite(textureName,scaleFactor,resize))
    {
        // if we don't find the image file 
        return ; 
    }
    // after this point, the sprite is created with appropriate texture
    this->sprite.setPosition(pos);
    this->isFree = isFree;
    this->isExit = isExit ;
}

bool GameTile::setUpSprite(std::string textureName,float scaleFactor, bool resize)
{
    /*
    *   This function aims to associate a sprite to a texture generated from an image file on the hard drive 
    *   std::string textureName : name of the texture I want to associate to many sprites
    *   float scaleFactor : how much should I increase the size of my texture
    *   bool resize : true <=> I want to resize my texture 
    *
    */
    if(!this->texture.loadFromFile(textureName))
    {
        return false; // loading image failed
    }
    if(resize == true)
    {
        this->texture = resizeTexture(this->texture,scaleFactor);
    }
    this->texture.setSmooth(true); // blurs the edges of the texture
    this->sprite.setTexture(this->texture);
    sf::Vector2u textureSize = this->texture.getSize(); 
    
    //this->sprite.setTextureRect(sf::IntRect(0,0,textureSize.x,textureSize.y)); // defines the "hitbox"
    return true;
}

sf::Texture GameTile::resizeTexture(const sf::Texture& originalTexture, float scaleFactor) 
{
    /*
    *   Useful to avoid "manually" resizing an image file too little compared to game's window
    *
    *
    */

    // Get the original texture size
    sf::Vector2u originalSize = originalTexture.getSize();

    // Create a black image with desired size
    sf::Image resizedImage;
    resizedImage.create(static_cast<unsigned int>(originalSize.x * scaleFactor), 
                        static_cast<unsigned int>(originalSize.y * scaleFactor));

    // Copy pixels from the original texture to the resized image 
    for (unsigned int y = 0; y < originalSize.y; y++) 
    {
        for (unsigned int x = 0; x < originalSize.x; x++) 
        {
            sf::Color pixelColor = originalTexture.copyToImage().getPixel(x, y);
            for (float dy = 0; dy < scaleFactor; dy++) 
            {
                for (float dx = 0; dx < scaleFactor; dx++) 
                {
                    resizedImage.setPixel(static_cast<unsigned int>(x * scaleFactor + dx),
                                          static_cast<unsigned int>(y * scaleFactor + dy),pixelColor);
                }
            }
        }
    }
    // Create a new texture from the resized image
    sf::Texture resizedTexture;
    resizedTexture.loadFromImage(resizedImage);
    return resizedTexture;
}


