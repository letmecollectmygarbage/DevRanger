#ifndef ENTITY_H
#define ENTITY_H


#include "Player.h"




#endif

Entity::Entity()
{
    this->shape.setSize(sf::Vector2f(50.f,50.f));
    this->movementSpeed = 300.f ;
}

Entity::~Entity()
{
}

void Entity::update(const float &dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // left 
    {
        this->move(dt,-1.f,0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) // up
    {
        this->move(dt,0.f,-1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
    {
        this->move(dt,1.f,0.f);
    } 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
    {
        this->move(dt,0.f,1.f);
    }
}

void Entity::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
    /*
    *       -1 <= dir_x <= 1
    *       -1 <= dir_y <= 1
    */
    this->shape.move(dir_x*this->movementSpeed*dt,dir_y*this->movementSpeed*dt);
}
