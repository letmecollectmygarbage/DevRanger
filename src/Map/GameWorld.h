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
        bool construction_finished = false ;
        
    public : 
        GameWorld(); 
        std::vector<GameTile*> tiles ;
        sf::Texture loadTexture(std::string txtrName); 
        

};

#endif