#include "GameWorld.h"





void GameWorld::setUpTiles()
{
    // window = 800*600 px

    tiles.clear();
    std::string folder = "ressources/Images/" ;
    std::string wall = "wall.png" ;  // 16*16px --> 32*32px bc of scaleFactor
    std::string door = "door.png" ;
    std::string currentPath = "./" ;
    std::string wallPath = currentPath+folder+wall ;
    std::string doorPath = currentPath+folder+door ;
    float scaleFactor = 2.f ; 
    sf::Vector2f posFirstRow = {0.f,0.f};
    sf::Vector2f posBottomRow = {0.f,568.f}; // objective height = 600px here
    //std::vector<StaticGameTile *> firstRow ; // row != column
    //std::vector<StaticGameTile *> bottomRow ; 
    int numSprites = 10 ; 
    StaticGameTile* topWall = new StaticGameTile(wallPath,numSprites,posFirstRow);
    StaticGameTile* bottomWall = new StaticGameTile(wallPath,numSprites,posBottomRow);
    for(int i = 0 ; i < numSprites ; i++){
        topWall->sprites[i].setPosition(posFirstRow);
        bottomWall->sprites[i].setPosition(posBottomRow);

        posFirstRow.x += 32.f ; // increment by width of tile
        posBottomRow.x = posFirstRow.x ; // symetrical with top wall
    }
    
    //firstRow[8]->setUpSprite(doorPath) ; 
    tiles.push_back(topWall); 
    tiles.push_back(bottomWall);
    
}

GameWorld::GameWorld()
{
    gridSize = {25,12}; // to multiply by 50 to get resolution in px (cf : GameTile::setUpSprite(std::string textureName))
    setUpTiles();
}

