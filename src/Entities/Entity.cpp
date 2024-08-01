


#include "Player.h"

Entity::Entity()
{
    //this->shape.setSize(sf::Vector2f(50.f,50.f));
    //this->movementSpeed = 300.f ;
}

Entity::~Entity()
{
}

// Does NOTHING !
void Entity::update(const float &dt)
{

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

