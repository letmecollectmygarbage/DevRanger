#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <chrono> // for FPS measurement
#include <stack>
#include <vector>
#include <map>

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
    int health ; // number of health points the entity has
    int maxHealth ; // number of health points the entity starts with 
    int imagesPerMovement ; // according to what I have in Images/<entity>/Moves
    int numberOfDifferentMovements; // also according to what I have in Images/<entity>/Moves

    // Map to link sprite arrays to their movement directions
    std::map<std::string, std::vector<sf::Sprite>> spriteMap;
    
    // Map to link texture arrays to their movement directions
    std::map<std::string, std::vector<sf::Texture>> textureMap;

    float width; // width of entity
    float height; // height of entity
    sf::Vector2f size ; // size (width,height) of the entity

    float initialX; // Initial X position
    float initialY;  // Initial Y position
    sf::Vector2f initialPos; // Initial position (initialX,initialY)
    
    sf::Sprite sprite ; // current sprite of the entity
    
    
    
    std::string imagesFolder = "ressources/Images/" ; // root image folder
    std::string entityImagesFolder ; // entity related images
    std::vector<std::string> movements ; // all movements the entity can do (depends on the sprites we will find)
    





    public:
        sf::Vector2f pos ; // current position of the entity
        Entity();
        virtual ~Entity(); // Declare the destructor as virtual for proper polymorphism

        // Functions 
        virtual void update(const float& deltaTime) ;
        virtual void render(sf::RenderTarget* target) ;
        void move(const float& deltaTime, const float x, const float y);
        int initSprites();
        sf::Clock clock; // // starts the clock
        
        sf::Time time1,time2 ; // 
        bool suffering ; // determines wether the Entity is suffering from an attack or not

        // getters / setters 
        sf::Sprite getSprite();
        bool getSuffering();
        void setSuffering(bool suffering);
        void manageSuffering(bool reset);
        int getHealth();
        void setHealth(int health);
};

#endif