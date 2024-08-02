


#include "Player.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

// Does NOTHING !
void Entity::update(const float &deltaTime)
{

}

void Entity::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}

void Entity::move(const float& deltaTime, const float dir_x, const float dir_y)
{
    /*
    *       -1 <= dir_x <= 1
    *       -1 <= dir_y <= 1
    */
    this->shape.move(dir_x*this->movementSpeed*deltaTime,dir_y*this->movementSpeed*deltaTime);
}

