#include "GameWorld.h"



GameWorld::GameWorld()
    : dImg{"./ressources/Images/"}
    , dMap{"Map/"}
{
    setUpTiles();
}

// define static member 
GameWorld GameWorld::instance;

GameWorld& GameWorld::getInstance(){
    return instance ;
}



void GameWorld::setUpTiles()
{
    tiles.clear();
    std::string walls = "walls_32x32/" ;  
    std::string ext = ".png" ;


    std::string wall1 = dImg+walls+"1"+ext ;
    std::string wall2 = dImg+walls+"2"+ext ;
    std::string wall3 = dImg+walls+"3"+ext ;
    bool isFree = false ; // walls are obstacles
    
    sf::Vector2f pos = {0.f,0.f};
    int num_walls_h = 10 ; // number of sprites for the horizontal walls
    // horizontal walls
    GameTile* top_wall_1 = new GameTile(wall1,num_walls_h,pos,isFree);
    GameTile* top_wall_2 = new GameTile(wall2,num_walls_h,pos,isFree);
    GameTile* top_wall_3 = new GameTile(wall3,num_walls_h,pos,isFree);
    GameTile* btm_wall_1 = new GameTile(wall1,num_walls_h,pos,isFree); 
    GameTile* btm_wall_2 = new GameTile(wall2,num_walls_h,pos,isFree); 
    GameTile* btm_wall_3 = new GameTile(wall3,num_walls_h,pos,isFree); 

    // vertical walls 
    int num_walls_v = 2 ; // number of sprites for the vertical walls
    GameTile* left_wall_1 = new GameTile(wall1,num_walls_h,pos,isFree);
    GameTile* left_wall_2 = new GameTile(wall2,num_walls_h,pos,isFree);
    GameTile* left_wall_3 = new GameTile(wall3,num_walls_h,pos,isFree);
    GameTile* right_wall_1 = new GameTile(wall1,num_walls_h,pos,isFree);
    GameTile* right_wall_2 = new GameTile(wall2,num_walls_h,pos,isFree);
    GameTile* right_wall_3 = new GameTile(wall3,num_walls_h,pos,isFree);
    float width = top_wall_1->sprites[0].getTextureRect().width ; // sprite width
    float height = top_wall_1->sprites[0].getTextureRect().height ; // sprite height

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
    // FLOOR 
    setUpFloorTiles();

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


// Sets up sprites for the floor (background)
void GameWorld::setUpFloorTiles(){
    std::string fName = "floor.png" ; // filename of floor texture
    std::string path = dImg + dMap + fName ;
    int num_blocks_x,num_blocks_y ;
    sf::Vector2i res = {1920,1080} ; // TODO: check what happens if user's res is lower 
    res *= 2 ; // temporary fix so floor is visible in every pos of 1st room
    sf::Vector2f pos_init_player = {400.f,400.f}; // TODO : find a way to get it from Player class
    sf::Texture txtr = loadTexture(path);
    sf::Vector2f s_txtr = {static_cast<float>(txtr.getSize().x),static_cast<float>(txtr.getSize().y)}; // size of texture (in pixels)
    num_blocks_x = res.x/s_txtr.x ; // number of sprites needed to cover res.x pixels with a texture of this width
    num_blocks_y = res.y/s_txtr.y ; // number of sprites needed to cover res.y pixels with a texture of this height
    GameTile* floor = new GameTile(path,num_blocks_x*num_blocks_y,{0.f,0.f},true);
    const sf::Vector2f original_pos = {-932.f,-512.f}; // never modify this one
    sf::Vector2f pos = original_pos ; 
    floor->sprites[0].setPosition(pos); // case i = 0 to put outside loop bc of 0% = 0 
    pos.x += s_txtr.x ; 
    for(int i=1 ; i < num_blocks_x * num_blocks_y ; i++){
        if(i % num_blocks_x  == 0){
            pos.x = original_pos.x ; // reset x coordinate to draw new line
            pos.y += s_txtr.y ; // adjust y coordinate to draw new line
        }
        floor->sprites[i].setPosition(pos);
        pos.x += s_txtr.x ;
    }
    tiles.push_back(floor);
}


sf::Texture GameWorld::loadTexture(std::string txtrName){
    sf::Texture txtr ; 
    if(!txtr.loadFromFile(txtrName)){
        std::cerr << "[GameWorld::loadTexture] Impossible to load texture from "<<txtrName<<"\n";
    }
    return txtr ; 
}