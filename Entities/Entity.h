

#include <iostream>
#include <cstdlib> // for random enemy positions
#include <ctime> // for random enemy positions
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




    public:
        Entity();
        virtual ~Entity(); // Declare the destructor as virtual for proper polymorphism

        // Functions 
        virtual void update(const float& dt) ;
        virtual void render(sf::RenderTarget* target) ;
        virtual void move(const float& dt, const float x, const float y);
};