#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <cstdlib> // for random enemy positions
#include <ctime> // for random enemy positions
#include <chrono> // for FPS measurement
#include <stack>
#include <vector>
#include <map>
#include <array>


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



class Entity
{
    private : 



    protected : 

    sf::RectangleShape shape ; 
    float movementSpeed ; 
    int imagesPerMovement ; // according to what I have in Images/<entity>/Moves
    int numberOfDifferentMovements; // also according to what I have in Images/<entity>/Moves

    // Map to link sprite arrays to their movement directions
    std::map<std::string, std::vector<sf::Sprite>> spriteMap;
    
    // Map to link texture arrays to their movement directions
    std::map<std::string, std::vector<sf::Texture>> textureMap;

    float width; // width of entity
    float height; // height of entity
    sf::Vector2f size ; // size (width,height) of the player

    float initialX; // Initial X position
    float initialY;  // Initial Y position
    sf::Vector2f initialPos; // Initial position (initialX,initialY)
    
    sf::Sprite sprite ; // current sprite of the entity
    
    std::string lastMovement; // last movement of the entity ("UP","DOWN","IDLE",...)




    public:
        sf::Vector2f pos = initialPos; // current position of the entity
        Entity();
        virtual ~Entity(); // Declare the destructor as virtual for proper polymorphism

        // Functions 
        virtual void update(const float& dt) ;
        virtual void render(sf::RenderTarget* target) ;
        virtual void move(const float& dt, const float x, const float y);
};

#endif