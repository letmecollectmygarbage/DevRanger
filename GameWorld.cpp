#include "GameWorld.h"

void GameWorld::setUpInitialState()
{
    //exitPos = sf::Vector2i(8,0);
    setUpTiles();
}



void GameWorld::setUpTiles()
{
    // window = 800*600 px

    tiles.clear();
    std::string folder = "Images/" ;
    std::string wall = "wall.png" ;  // 16*16px --> 32*32px bc of scaleFactor
    std::string door = "door.png" ;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path wallPath = currentPath/folder/wall ;
    std::filesystem::path doorPath = currentPath/folder/door ;
    float scaleFactor = 2.f ; 
    bool resize = true ;
    bool isFree = false ; 
    bool isExit = false ; 
    sf::Vector2f posFirstRow = {0.f,0.f};
    sf::Vector2f posBottomRow = {0.f,568.f};
    std::vector<GameTile *> firstRow ; // row != column
    std::vector<GameTile *> bottomRow ; 
    for(int i = 0 ; i < gridSize.x ; i++)
    {
        // create top wall 
        firstRow.push_back(new GameTile(wallPath,posFirstRow,isFree,isExit,scaleFactor,resize)); // bc each tile is a 32x32px
        bottomRow.push_back(new GameTile(wallPath,posBottomRow,isFree,isExit,scaleFactor,resize)); // 32 * gridSize.x = 800
        
        std::cerr << "[DEBUG] i = " << i << "\n";
        posFirstRow.x += 32.f ; 
        posBottomRow.x = posFirstRow.x ;
    }

    firstRow[8]->setUpSprite(doorPath,scaleFactor,resize) ;  // TODO : find a way to set isExit attribute to true for this one
    tiles.push_back(firstRow); 
    tiles.push_back(bottomRow);
}

GameWorld::GameWorld()
{
    gridSize = {25,12}; // to multiply by 50 to get resolution in px (cf : GameTile::setUpSprite(std::string textureName))
    setUpInitialState() ; 
}

