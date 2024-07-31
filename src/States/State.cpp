#include "State.h"

State::State(sf::RenderWindow* window)
{
	this->window = window;
	this->quit = false ; 
}

State::~State()
{
	
}

const bool &State::getQuit() const
{
	// check if state wants to quit
	return this->quit;
}

void State::checkForQuit()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit=true; // exits game 
	}
}
