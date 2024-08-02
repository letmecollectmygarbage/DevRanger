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
void GameState::update(const float &dt){
    this->updateInput(dt);  
}

void GameState::render(sf::RenderTarget* target){
    this->statePlayer.render(target);
}

void GameState::updateInput(const float& dt){
    this->checkForQuit();

    // Update player's input //
    
    // LEFT:
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        this->statePlayer.move(dt,-1.f,0.f);
    }
    // UP:
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        this->statePlayer.move(dt,0.f,-1.f);
    }
    // RIGHT:
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->statePlayer.move(dt,1.f,0.f);
    } 
    // DOWN:
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->statePlayer.move(dt,0.f,1.f);
    }
    // no key pressed, IDLE
    else{
        this->statePlayer.move(dt,0.f,0.f);
    }
    view.setCenter(this->statePlayer.pos);
    window->setView(this->view);
}