#include "GameTile.h"

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
    private : 
        sf::Vector2i exitPos ; 
        void setUpTiles();



    public : 
        std::vector<GameTile*> tiles ; 
        sf::Vector2i gridSize ; // x = width , y = length 
        GameWorld();

};

#endif