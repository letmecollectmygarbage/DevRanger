#include "State.h"

// Constructor
State::State(sf::RenderWindow* window, sf::View view)
{
	this->window = window;
	this->view = view ;
	this->quit = false ; 
}

// Destructor
State::~State(){	
}

const bool &State::getQuit() const{
	// check if state wants to quit
	return this->quit;
}

void State::checkForQuit(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		this->quit=true; // exits game 
	}
}
