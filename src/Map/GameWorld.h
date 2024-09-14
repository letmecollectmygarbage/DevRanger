#include "GameTile.h"

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld
{
    private : 

        void setUpTiles();
        void setUpFloorTiles();
        
        std::string dImg ; // root img directory
        std::string dMap ; // map textures directory
        static GameWorld instance ; // Static instance for the singleton
        GameWorld(); // private constructor for the singleton pattern

        // Explicitly delete copy constructor and assignment operator to prevent copying
        GameWorld(const GameWorld&) = delete; 
        GameWorld& operator=(const GameWorld&) = delete;
        



    public : 
        std::vector<GameTile*> tiles ;
        sf::Texture loadTexture(std::string txtrName); 
        
        static GameWorld& getInstance(); // Accessor for the singleton instance

};

#endif