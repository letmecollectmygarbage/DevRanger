#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
    : State(window)
{

}

GameState::~GameState()
{


}

void GameState::endState()
/*
*   State before quitting where you can save hero's progression for example
*/
{
    std::cout << "endState is reached !" << "\n" ;
}

void GameState::update(const float &dt)
{
    this->updateInput(dt);

    // just a debug test //
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        std::cout << "A" << "\n" ; // test 
    }    
    // end of test 

    this->statePlayer.update(dt);      
}

void GameState::render(sf::RenderTarget* target)
{
    // if(!target)
    // {
    //     target = this->window;
    // }
    this->statePlayer.render(target);

}

void GameState::updateInput(const float& dt)
{
    this->checkForQuit();


    // Update player's input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // left 
    {
        this->statePlayer.move(dt,-1.f,0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) // up
    {
        this->statePlayer.move(dt,0.f,-1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
    {
        this->statePlayer.move(dt,1.f,0.f);
    } 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
    {
        this->statePlayer.move(dt,0.f,1.f);
    }
}