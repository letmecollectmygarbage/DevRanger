#include <iostream>
#include <cstdlib> // for random enemy positions
#include <ctime> // for random enemy positions
#include <chrono> // for FPS measurement
#include <stack>
#include <vector>
#include <map>
#include <array>
#include <filesystem> // for path handling


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    private : 


    protected : 
    sf::RectangleShape shape ; 
    float movementSpeed ; 




    public:
        Entity();
        virtual ~Entity(); // Declare the destructor as virtual for proper polymorphism

        // Functions 
        virtual void update(const float& dt) ;
        virtual void render(sf::RenderTarget* target) ;
        virtual void move(const float& dt, const float x, const float y);
};

#endif