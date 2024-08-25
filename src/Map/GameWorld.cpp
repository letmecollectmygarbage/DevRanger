#include "GameWorld.h"





void GameWorld::setUpTiles()
{
    tiles.clear();
    std::string repo_img = "./ressources/Images/" ;
    std::string walls = "walls_32x32/" ;  // 30*30px 
    std::string ext = ".png" ;


    std::string wall1 = repo_img+walls+"1"+ext ;
    std::string wall2 = repo_img+walls+"2"+ext ;
    std::string wall3 = repo_img+walls+"3"+ext ;

    
    sf::Vector2f pos = {0.f,0.f};
    int num_walls_h = 10 ; // number of sprites for the horizontal walls
    // horizontal walls
    GameTile* top_wall_1 = new GameTile(wall1,num_walls_h,pos);
    GameTile* top_wall_2 = new GameTile(wall2,num_walls_h,pos);
    GameTile* top_wall_3 = new GameTile(wall3,num_walls_h,pos);
    GameTile* btm_wall_1 = new GameTile(wall1,num_walls_h,pos); 
    GameTile* btm_wall_2 = new GameTile(wall2,num_walls_h,pos); 
    GameTile* btm_wall_3 = new GameTile(wall3,num_walls_h,pos); 

    // vertical walls 
    int num_walls_v = 2 ; // number of sprites for the vertical walls
    GameTile* left_wall_1 = new GameTile(wall1,num_walls_h,pos);
    GameTile* left_wall_2 = new GameTile(wall2,num_walls_h,pos);
    GameTile* left_wall_3 = new GameTile(wall3,num_walls_h,pos);
    GameTile* right_wall_1 = new GameTile(wall1,num_walls_h,pos);
    GameTile* right_wall_2 = new GameTile(wall2,num_walls_h,pos);
    GameTile* right_wall_3 = new GameTile(wall3,num_walls_h,pos);
    float width = top_wall_1->sprites[0].getTextureRect().width ;
    float height = top_wall_1->sprites[0].getTextureRect().height ;

    // position every tile of top wall correctly with following pattern: wall1, wall2, wall3 and repeat
    
    for(int i = 0 ; i < num_walls_h ; i++){
        top_wall_1->sprites[i].setPosition(pos);
        pos.x += width;
        top_wall_2->sprites[i].setPosition(pos);
        pos.x += width;
        top_wall_3->sprites[i].setPosition(pos);
        pos.x += width;
    }

    // position every tile of bottom wall correctly with following pattern: wall1, wall2, wall3 and repeat
    float y = 3 * height * num_walls_h - height ; 
    pos = {0.f,y}; // y is determined to match the end of vertical walls
    for(int i = 0 ; i < num_walls_h ; i++){
        btm_wall_1->sprites[i].setPosition(pos);
        pos.x += width ;
        btm_wall_2->sprites[i].setPosition(pos);
        pos.x += width ; 
        btm_wall_3->sprites[i].setPosition(pos);
        pos.x += width ;
    }

    // position every tile of left wall correctly with following pattern: wall1, wall2, wall3 and repeat
    pos = {0.f,0.f}; 
    for(int i = 0 ; i < num_walls_h ; i++){
        left_wall_1->sprites[i].setPosition(pos);
        pos.y += height ;
        left_wall_2->sprites[i].setPosition(pos);
        pos.y += height ; 
        left_wall_3->sprites[i].setPosition(pos);
        pos.y += height ;
    }

    // position every tile of right wall correctly with following pattern: wall1, wall2, wall3 and repeat
    float x_max_wall = num_walls_h * width * 3 ; // determine end of horizontal wall to place right wall
    pos = {x_max_wall,0.f}; 
    for(int i = 0 ; i < num_walls_h ; i++){
        right_wall_1->sprites[i].setPosition(pos);
        pos.y += height ;
        right_wall_2->sprites[i].setPosition(pos);
        pos.y += height ; 
        right_wall_3->sprites[i].setPosition(pos);
        pos.y += height ;
    }


    
    // add tiles pointers to the tiles vector which is the only one rendered 
    tiles.push_back(top_wall_1); 
    tiles.push_back(top_wall_2);
    tiles.push_back(top_wall_3);  
    tiles.push_back(btm_wall_1); 
    tiles.push_back(btm_wall_2);
    tiles.push_back(btm_wall_3); 
    tiles.push_back(left_wall_1); 
    tiles.push_back(left_wall_2);
    tiles.push_back(left_wall_3);
    tiles.push_back(right_wall_1); 
    tiles.push_back(right_wall_2);
    tiles.push_back(right_wall_3);

    
}

GameWorld::GameWorld()
{
    gridSize = {25,12}; // to multiply by 50 to get resolution in px (cf : GameTile::setUpSprite(std::string textureName))
    setUpTiles();
}

