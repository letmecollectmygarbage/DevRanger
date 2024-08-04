#include "Monster.h"

// Constructor. Initializes player attributes and sprites. 
Monster::Monster() 
{
    movements = {"IDLE"} ;
    imagesPerMovement = 1 ; // according to what I have in entityImagesFolder
    movementSpeed = 50.f ; 
    numberOfDifferentMovements = 1 ; // idle
    width = 50.f ; 
    height = 50.f ; 
    size = {width,height}; 
    shape.setSize(size); 
    initialX = 0.f ;
    initialY = 0.f ;  
    initialPos = {initialX,initialY} ; 
    pos = initialPos ;
    lastMovement = "IDLE" ; 
    entityImagesFolder = "Monster/" ; // 68x71 px
    this->initSprites(); // to call last, after all attributes are set
    
}