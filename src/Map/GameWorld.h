#include "GameTile.h"

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
    private : 

        void setUpTiles();



    public : 
        std::vector<GameTile*> tiles ; 
        GameWorld();

};

#endif