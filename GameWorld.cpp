#include "GameWorld.h"

void GameWorld::setUpInitialState()
{
    exitPos = sf::Vector2i(8,0);
    playerPos = sf::Vector2i(gridSize.x-1,gridSize.y-1);
    //setUpEnemyPositions(); // no enemies yet 
    setUpTiles();
}

void GameWorld::setUpEnemyPositions()
{
    enemyPositions.clear();
    enemyPositions.push_back(sf::Vector2i(0,2));
    enemyPositions.push_back(sf::Vector2i(6,0));
    enemyPositions.push_back(sf::Vector2i(2,7));

}

void GameWorld::setUpTiles()
{
    tiles.clear();
    std::string folder = "Images/" ;
    std::string wall = "wall.png" ; 
    std::string door = "door.png" ;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path wallPath = currentPath/folder/wall ;
    std::filesystem::path doorPath = currentPath/folder/door ;
    float scaleFactor = 2.f ; 
    bool resize = true ;
    bool isFree = false ; 
    bool isExit = false ; 
    std::vector<GameTile *> firstRow ; // row != column
    for(int i = 0 ; i < 16 ; i++)
    {
        // create top wall 
        
        firstRow.push_back(new GameTile((wallPath),{i*50.f,0},isFree,isExit,scaleFactor,resize)); // bc each tile is a 50x50px square
    }

    firstRow[8]->setUpSprite(doorPath,scaleFactor,resize) ;  // TODO : find a way to set isExit attribute to true for this one
    tiles.push_back(firstRow); 
}

GameWorld::GameWorld()
{
    gridSize = {16,12}; // to multiply by 50 to get resolution in px (cf : GameTile::setUpSprite(std::string textureName))
    setUpInitialState() ; 
}

