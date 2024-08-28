#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, sf::View view)
    : State(window,view)
{

}

// Destructor (but does nothing yet)
GameState::~GameState(){
}


//State before quitting where you can save hero's progression for example
void GameState::endState(){
    std::cout << "endState is reached !" << "\n" ;
}

// Checks for user input and does something else
void GameState::update(const float &deltaTime){
    this->updateInput(deltaTime);  
    this->updateMonsterMoveDirection(deltaTime);
}

void GameState::render(sf::RenderTarget* target){
    this->statePlayer.render(target);
    this->stateMonster.render(target);
}

// Update player's input
void GameState::updateInput(const float& deltaTime){
    this->checkForQuit();
    
    // Update player's input //
    
    // LEFT:
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        this->statePlayer.move(deltaTime,-1.f,0.f);
        if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,1.f,0.f);
    }
    // UP:
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        this->statePlayer.move(deltaTime,0.f,-1.f);
        if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,0.f,1.f);
    }
    // RIGHT:
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->statePlayer.move(deltaTime,1.f,0.f);
        if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,-1.f,0.f);
    } 
    // DOWN:
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->statePlayer.move(deltaTime,0.f,1.f);
        if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,0.f,-1.f);
    }
    // no key pressed, IDLE
    else{
        this->statePlayer.move(deltaTime,0.f,0.f);
    }
    if(isPlayerTouchingMonster()) MonsterAttacksPlayer();
    view.setCenter(this->statePlayer.pos);
    window->setView(this->view);
}

// Calculates monster to hero direction 
// move monster in this direction to attack hero
// AB' = (xB - xA, yB - yA)  
void GameState::updateMonsterMoveDirection(const float& deltaTime){
    this->checkForQuit();
    sf::Vector2f moveToHero = statePlayer.pos - stateMonster.getSprite().getPosition() ; 
    sf::Vector2f nullVector = {0.f,0.f};
    if(moveToHero == nullVector) return ; // so div never equals 0

    float dir_x, dir_y =0.f ; 
    float div ; // what I divide dir_x & dir_y with to 1-norm them
    div = std::max(std::abs(moveToHero.x),std::abs(moveToHero.y)); // strictly positive
    dir_x = moveToHero.x/std::abs(div) ;
    dir_y = moveToHero.y/std::abs(div) ; 
    stateMonster.move(deltaTime,dir_x,dir_y); 

    // DEBUG PRINT STATEMENTS
    // time1 = clock.getElapsedTime();
    // if(time1.asSeconds() > 5)
    // { 
    //     std::cerr << "[GameState::updateMonsterMoveDirection] " ;
    //     std::cerr << "statePlayer.pos : " << statePlayer.pos.x << ","  ;
    //     std::cerr << statePlayer.pos.y << " | stateMonster.pos :" ;
    //     std::cerr << stateMonster.pos.x << "," << stateMonster.pos.y ;
    //     std::cerr << " | moveToHero : " << moveToHero.x << ","  ;
    //     std::cerr  << moveToHero.y << "\n" ;
    //     std::cerr << "dir_x , dir_y : " << dir_x << " , " << dir_y <<"\n" ; 
    //     clock.restart();
    // }
}

void GameState::receiveMap(std::vector<GameTile*> tiles){
    this->tiles = tiles ;


}

bool GameState::isPlayerTouchingWall(){
    sf::FloatRect playerRect = statePlayer.getSprite().getGlobalBounds();
    for(GameTile* tile : tiles){
        for(sf::Sprite sprite : tile->sprites){
            sf::FloatRect wallRect = sprite.getGlobalBounds();
            if(playerRect.intersects(wallRect)) return true ;
        }
    }
    return false ; 
}

bool GameState::isPlayerTouchingMonster(){
    sf::FloatRect playerRect = statePlayer.getSprite().getGlobalBounds();
    sf::FloatRect monsterRect = stateMonster.getSprite().getGlobalBounds();
    if(playerRect.intersects(monsterRect)) return true ;
    return false ; 
}

void GameState::MonsterAttacksPlayer(){
    static bool firstAttack = true ;
    if(firstAttack){
        int hp = statePlayer.getHealth() -10 ; 
        statePlayer.setHealth(hp) ;
        firstAttack = false ;
    }
    
    else{
        time1 = clock.getElapsedTime();
        if(time1.asSeconds() > 5){
            int hp = statePlayer.getHealth() -10 ; 
            statePlayer.setHealth(hp) ;
            clock.restart();
        }
        else{return;}
    }

}