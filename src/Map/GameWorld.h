#include "GameTile.h"

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
    private : 

        void setUpTiles();
        static GameWorld instance ; // Static instance for the singleton
        GameWorld(); // private constructor for the singleton pattern

        // Explicitly delete copy constructor and assignment operator to prevent copying
        GameWorld(const GameWorld&) = delete; 
        GameWorld& operator=(const GameWorld&) = delete;
        



    public : 
        std::vector<GameTile*> tiles ; 
        
        static GameWorld& getInstance(); // Accessor for the singleton instance

};

#endif