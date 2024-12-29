#include "Monster.h"

// Constructor. Initializes player attributes and sprites. 
Monster::Monster() 
{
    movements = {"IDLE"} ;
    images_per_movement = 1 ; // according to what I have in entity_images_folder
    movement_speed = 50.f ; 
    health = 1 ; 
    number_of_different_movements = 1 ; // idle 
    initial_x = 0.f ;
    initial_y = 0.f ;  
    initial_pos = {initial_x,initial_y} ; 
    pos = initial_pos ;
    lastMovement = "IDLE" ; 
    entity_images_folder = "Monster/" ; // 68x71 px
    this->init_sprites(); // to call last, after all attributes are set
    
}

void Monster::move(const float& deltaTime, const float dir_x, const float dir_y)
{
    /*
    *       -1 <= dir_x <= 1
    *       -1 <= dir_y <= 1
    */
    sprite.move(dir_x*this->movement_speed*deltaTime,dir_y*this->movement_speed*deltaTime);
}