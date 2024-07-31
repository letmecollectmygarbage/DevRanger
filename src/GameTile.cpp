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
GameTile::GameTile(std::string textureName, sf::Vector2f pos, bool isFree, bool isExit, float scaleFactor, bool resize)
{

    if(!setUpSprite(textureName,scaleFactor,resize))
    {
        // image file not found
        return ; 
    }
    // after this point, the sprite is created with appropriate texture
    this->sprite.setPosition(pos);
    this->isFree = isFree;
    this->isExit = isExit ;
}

/*
* @brief Associates a sf::sprite to a sf::texture. 
*
* Applies the texture attribute to the sprite attribute. If resize 
* is enabled, the texture is first resized. 
* 
* @param textureFilename (std::string): filename (filepath) of the texture 
* @param scaleFactor (float): original dimensions will be multiplied by this factor. 
* @param resize (bool): if enabled, the sprite will be resized.
* @return True if texture is found, False otherwise.
*/
bool GameTile::setUpSprite(std::string textureFilename,float scaleFactor, bool resize){
    if(!this->texture.loadFromFile(textureFilename)) return false; // loading image failed
    if(resize) this->texture = resizeTexture(this->texture,scaleFactor);
    
    this->texture.setSmooth(true); // blurs edges
    this->sprite.setTexture(this->texture);
    sf::Vector2u textureSize = this->texture.getSize(); 
    return true;
}

sf::Texture GameTile::resizeTexture(const sf::Texture& originalTexture, float scaleFactor){
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


