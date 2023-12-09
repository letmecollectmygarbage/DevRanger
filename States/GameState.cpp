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
    this->updateKeybinds(dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        std::cout << "A" << "\n" ; // test 
    }

    this->player.update(dt);
         
}

void GameState::render(sf::RenderTarget* target)
{
    this->player.render(target);

}

void GameState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
}