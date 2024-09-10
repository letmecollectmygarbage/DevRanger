


#include "Entity.h"

Entity::Entity(){
    imagesPerMovement=0;
    initSprites();
}

Entity::~Entity(){}

// Does NOTHING !
void Entity::update(const float &deltaTime){}

void Entity::render(sf::RenderTarget* target){
    target->draw(this->sprite);
}

void Entity::move(const float& deltaTime, const float dir_x, const float dir_y){
    /*
    *       -1 <= dir_x <= 1
    *       -1 <= dir_y <= 1
    */
    this->sprite.move(dir_x*this->movementSpeed*deltaTime,dir_y*this->movementSpeed*deltaTime);
}

// Initializes sprites of the hero or monster
int Entity::initSprites(){
    // Number of movements for each walk cycle and IDLE. Must all be equal to use a map
    std::string mvmtID ; 
    std::string filename;
    std::string currentPath = "./" ;
    std::string imgPath = currentPath+imagesFolder+entityImagesFolder; 
    
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
    // make entity start IDLE facing the user
    if(spriteMap.size()>0){
        sprite = spriteMap["IDLE"][0] ; // IDLE facing down
        sprite.setPosition(initialPos);
    }
    return 0 ;
}


sf::Sprite Entity::getSprite(){
    return sprite ;
}

bool Entity::getSuffering(){
    return suffering;
}

void Entity::setSuffering(bool suffering){
    this->suffering = suffering ; 
}

// Makes entity suffer for a certain period of time, no more
// Call reset in case Player is attacked twice in a 0.5s delay to
// make sure that he will stay suffering for an additional 0.5s
void Entity::manageSuffering(bool reset){
    // Unhandled case : (example):
    // Player attacked at T=0
    // suffering=true
    // Player attacked at T=0.4s
    // suffering=false at T=0.5s

    static sf::Clock clock ;
    static bool counting = false ; 
    sf::Time time ;
    if(!suffering){ 
        // Entity is not suffering, nothing to do here
        clock.restart(); // restart in preparation of call when suffering==true
        return ;
    }
    else{
        if(reset) clock.restart(); 
        if(!counting){
            clock.restart();
            counting = true ;
        }
        time = clock.getElapsedTime();
        if(time.asSeconds() > 0.5f){
            setSuffering(false);
            clock.restart(); // important in case Player is constantly attacked 
            counting = false ; 
        }
    }  

}

int Entity::getHealth(){return health ;}
void Entity::setHealth(int health){
            if(health >= 0) this->health = health ;
            else{this->health = 0;}
        }