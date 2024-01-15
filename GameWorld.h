#include "GameTile.h"

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
    sf::Vector2i exitPos ; 
    void setUpInitialState();
    void setUpTiles();



    public : 
        std::vector<std::vector<GameTile*>> tiles ; 
        sf::Vector2i gridSize ; // x = width , y = length 
        GameWorld();

};

#endif