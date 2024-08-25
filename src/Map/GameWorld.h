#include "GameTile.h"
#include "StaticGameTile.h"

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
    private : 
        sf::Vector2i exitPos ; 
        void setUpTiles();



    public : 
        std::vector<StaticGameTile*> tiles ; 
        sf::Vector2i gridSize ; // x = width , y = length 
        GameWorld();

};

#endif