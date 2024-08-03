


#include "Player.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

// Does NOTHING !
void Entity::update(const float &deltaTime)
{

}

void Entity::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}

void Entity::move(const float& deltaTime, const float dir_x, const float dir_y)
{
    /*
    *       -1 <= dir_x <= 1
    *       -1 <= dir_y <= 1
    */
    this->shape.move(dir_x*this->movementSpeed*deltaTime,dir_y*this->movementSpeed*deltaTime);
}

// Initializes sprites of the hero
int Entity::initSprites(){
    // Number of movements for each walk cycle and IDLE. Must all be equal to use a map
    std::string mvmtID ; 



    std::string filename,imagesFolder,imagesPlayerFolder;
    std::string currentPath = "./" ;
    imagesFolder = "ressources/Images/" ;
    imagesPlayerFolder = "Player/Moves/" ; 
    std::string folderPath = currentPath+imagesFolder+imagesPlayerFolder; 
    lastMovement = "IDLE" ; // initiated as IDLE down
    // LOAD EVERY TEXTURE NECESSARY FOR HERO MOVEMENT //
    // IDLE:
    
    // For every different movement
    for(int j = 0 ; j < numberOfDifferentMovements ; j++){
        // define mvmtID of image
        if(j==0){mvmtID = "IDLE";}
        else if(j==1){mvmtID = "UP";}
        else if(j==2){mvmtID = "DOWN";}
        else if(j==3){mvmtID = "LEFT";}
        else if(j==4){mvmtID = "RIGHT";}
        // Initialize the vectors in the maps
        textureMap[mvmtID] = std::vector<sf::Texture>(imagesPerMovement);
        spriteMap[mvmtID] = std::vector<sf::Sprite>(imagesPerMovement);
        // For the number of sprites each movement has
        for(int i = 0 ; i < imagesPerMovement ; i++){
            filename = mvmtID + +"_"+std::to_string(i+1) + ".png" ; 
            if(!textureMap[mvmtID][i].loadFromFile(folderPath+filename)){
                std::cerr << "The image"+mvmtID+"_"+ std::to_string(i) + " was not found \n" ;
                return -1 ; 
            }
            spriteMap[mvmtID][i].setTexture(textureMap[mvmtID][i]);
        }
    }

    // make hero start IDLE facing the user
    sprite = spriteMap["IDLE"][0] ; // IDLE facing down
    std::cerr << "[INFO] Player::initSprites() achieved" << "\n" ; 
    return 0 ;
}