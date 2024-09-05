#include "Player.h"
#include <iterator> 

// Constructor. Initializes player attributes and sprites. 
Player::Player() 
{
    movements = {"IDLE","UP","DOWN","LEFT","RIGHT"}; 
    imagesPerMovement = 6 ; // according to what I have in Images/Player/Moves
    movementSpeed = 300.f ;
    maxHealth = 100 ; 
    health = maxHealth ; 
    numberOfDifferentMovements = 5 ; // idle, left,right,up,down
    width = 50.f ; 
    height = 50.f ; 
    size = {width,height}; 
    shape.setSize(size); 
    initialX = 400.f ;
    initialY = 400.f ;  
    initialPos = {initialX,initialY} ; 
    lastMovement = "IDLE" ; 
    entityImagesFolder = "Player/Moves/" ; // 40x64 px
    suffering = false ; 
    initSprites(); // to call last, after all attributes are set
    init_life_display();

}

Player::~Player() 
{
    // Destructor for Player, if needed
}

void Player::render(sf::RenderTarget* target){
    if(suffering) target->draw(hurt);
    target->draw(this->sprite);
    for(sf::Sprite heart : this->health_hearts){
        target->draw(heart);
    }
    
}





/*
*   This is the function that makes the hero move. 
*   Arguments : dir_x and dir_y values are keyboard inputs
*   For correct behaviour only use this functions with   
*   dir_x belonging to [-1;1]
*   dir_y belonging to [-1;1]
*   Note: you only enter this function when Z,Q,S or D is pressed.
*/
void Player::move(const float& deltaTime, const float dir_x, const float dir_y){
    float k = 0 ; 
    if(dir_x == 0.f && dir_y == 0.f) nextSpriteIDLE();
    else nextSprite(dir_x, dir_y);

    sprite.move(dir_x*movementSpeed*deltaTime,dir_y*movementSpeed*deltaTime);
    pos = sprite.getPosition(); // update current position of player
    // update positions of hearts if hero still has some lives
    if (health_hearts.size() == 0){
        return ; 
    }
    float width_heart = health_hearts[0].getGlobalBounds().getSize().x ; 
    // dispose 3 hearts horizontally 
    for(sf::Sprite heart : health_hearts){
        float x = pos.x+(width_heart*k) + 40.f ; 
        health_hearts[k].setPosition(x,pos.y-100);
        k++;
    }
    hurt.setPosition(pos);
}

void Player::nextSprite(float dir_x, float dir_y){
    static int cyclePos = 0 ; // position in the current movement cycle (0->5)
    static int i = 0 ; 
    int repeat = 4 ; // number of times each sprite is repeated, used to slow down the 6 frame movement cycle
    std::string movement ; // most up to date Movement request from user

    // HANDLE FRAME CYCLES //

    // Determine movement direction based on dir_x and dir_y (user input)
    if(dir_x == 0.f && dir_y == -1.f){movement = "UP";}
    else if(dir_x == -1.f && dir_y == 0.f){movement = "LEFT";}
    else if(dir_x == 1.f && dir_y == 0.f){movement = "RIGHT";}
    else if(dir_x == 0.f && dir_y == 1.f){movement = "DOWN";}
    else{
        std::cerr << "[Player::nextSprite] Unhandled dirx,dir_y combination \n";
    }

    // hero walks in the same direction as last input
    if(lastMovement == movement){ 
        if(i < repeat) i++ ; // do nothing to slow down display a little
        else{ // take next sprite of same direction
            i = 0 ; 
            sprite = spriteMap[movement][cyclePos] ;
            sprite.setPosition(pos);
            cyclePos++;
            if(cyclePos >= 6) cyclePos = 0 ; // reset counter to not go outside the bounds of sprtUP
        }
    }
    // hero changes direction
    else{
        cyclePos = 0 ; // reset counter 
        sprite = spriteMap[movement][cyclePos] ;
        sprite.setPosition(pos);
        cyclePos++;
        lastMovement = movement;
    }
    return;
}


void Player::nextSpriteIDLE()
{
    std::string movement = "IDLE";
    // if already IDLE, do nothing
    if(lastMovement == movement){return;}
    else{
        if(lastMovement =="UP") sprite = spriteMap[movement][3];
        else if(lastMovement =="DOWN") sprite = spriteMap[movement][0];
        else if(lastMovement == "LEFT") sprite = spriteMap[movement][1];
        else if(lastMovement == "RIGHT") sprite = spriteMap[movement][2];
        else{std::cout << "[Player::nextSpriteIDLE] lastMovement unknown \n";}
        sprite.setPosition(pos);
    }
    return ;
}


void Player::init_life_display(){
    // Initialize the life display of the hero
    std::string path_to_heart_img = "./"+imagesFolder+"Player/heart.png";
    sf::Sprite heart_sprite ;
    sf::Vector2f pos_player = sprite.getPosition();
    if(!heart_texture.loadFromFile(path_to_heart_img)){
        std::cout << "Player constructor failed loading img from : " << path_to_heart_img << "\n";
        return ;
    }
    else{std::cout << "Player() : heart texture loaded from : "<<"./"+imagesFolder+"Player/heart.png \n";}
    heart_texture.setSmooth(true); // blurs edges
    heart_sprite.setTexture(heart_texture); 
    float width_heart = heart_sprite.getGlobalBounds().getSize().x ; 
    // dispose 3 hearts horizontally 
    for(float i = 0 ; i < 3 ; i++){
        heart_sprite.setPosition(pos_player.x+(width_heart*i),pos_player.y-100);
        health_hearts.push_back(heart_sprite);
    }
}

void Player::manage_life_display(){
    // Handles how many hearts you see depending on remaining health
    float life_ratio = static_cast<float>(health)/static_cast<float>(maxHealth) ; 
    int num_hearts ; // number of hearts that should be displayed
    if(life_ratio > 0.66f) num_hearts = 3 ; 
    else if(life_ratio > 0.33f && life_ratio <0.66f) num_hearts = 2 ; 
    else if(life_ratio < 0.33f && life_ratio >0.f) num_hearts=1 ; 
    else{num_hearts = 0 ; }

    // Verify that num_hearts hearts are visible as they should be
    if(health_hearts.size()==num_hearts) return ; 
    else{
        health_hearts.clear();
        sf::Sprite heart_sprite ;
        heart_sprite.setTexture(heart_texture);
        float width_heart = heart_sprite.getGlobalBounds().getSize().x ;
        for(float i=0 ; i < num_hearts ; i++){
            heart_sprite.setPosition(pos.x+(width_heart*i),pos.y-100);
            health_hearts.push_back(heart_sprite);
        }
    }
}

// Initializes sprites of the hero or monster
int Player::initSprites(){
    // Number of movements for each walk cycle and IDLE. Must all be equal to use a map
    std::string mvmtID ; 
    std::vector<std::string> fireballs_colors = {"pink/","red/","blue/"} ; 
    int N_fireballs = 6 ; // number of sprites for each fireball 


    std::string filename;
    std::string currentPath = "./" ;
    std::string imgPath = currentPath+imagesFolder+entityImagesFolder; 
    std::string fireballPath = "./" + imagesFolder+"Player/fireball/" ;
    std::cout<< "[INFO] [Entity::initSprites()] imgPath = " << imgPath << "\n";
    
    // LOAD EVERY TEXTURE OF THE ENTITY //

    for(auto move : movements){
        mvmtID = move ;
        // Initialize sf::Sprite & sf::Texture vectors
        textureMap[mvmtID] = std::vector<sf::Texture>(imagesPerMovement); 
        spriteMap[mvmtID] = std::vector<sf::Sprite>(imagesPerMovement); 
        // For the number of sprites each movement has
        for(int i = 0 ; i < imagesPerMovement ; i++){
            filename = mvmtID + +"_"+std::to_string(i+1) + ".png" ; 
            if(!textureMap[mvmtID][i].loadFromFile(imgPath+filename)){
                std::cerr << "The image"+mvmtID+"_"+ std::to_string(i) + " was not found \n" ;
                return -1 ; 
            }
            spriteMap[mvmtID][i].setTexture(textureMap[mvmtID][i]);
        }
    }
    // Load hurt sprite
    std::string blood_path = currentPath+imagesFolder+"Player/blood.png" ;
    if(!hurt_texture.loadFromFile(blood_path)){
        std::cerr << "Failed loading hurt_texture from : "<< blood_path << "\n" ; 
        return -1 ; 
    }
    hurt.setTexture(hurt_texture);

    // loading fireballs textures and sprites
    for(std::vector<std::string>::iterator color = fireballs_colors.begin() ; color != fireballs_colors.end() ; color++){
        std::vector<sf::Texture> texture_vector ;
        std::vector<sf::Sprite> sprite_vector ; 
        for(int i = 0 ; i < N_fireballs ; i++){
            sf::Texture fireballTexture ;
            sf::Sprite fireballSprite ;
            std::string path = fireballPath+*color+"/"+std::to_string(i+1)+".png" ;
            if(!fireballTexture.loadFromFile(path)){
                std::cerr << "Failed loading texture for fireball #"<<i<<" from: "<<path<< "\n" ;
            }
            fireballSprite.setTexture(fireballTexture) ;
            texture_vector.push_back(fireballTexture) ;
            sprite_vector.push_back(fireballSprite);
        }
        this->fireball_color_sprites[*color] = sprite_vector ;
    }
    

    // make entity start IDLE facing the user
    sprite = spriteMap["IDLE"][0] ; // IDLE facing down
    std::cerr << "[INFO] Entity::initSprites() achieved" << "\n" ; 
    sprite.setPosition(initialPos);
    return 0 ;
}