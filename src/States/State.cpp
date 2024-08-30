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
	static bool btn_pushed = false ; 
    static bool btn_released = false ; 
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		btn_pushed = true ; 
		return ; 
	}
	if(btn_pushed && not(btn_released)){
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) btn_released = true ; 
		return ; 
	}
	if(btn_pushed && btn_released){
		this->quit=true; // exits game
		btn_pushed=false ; // reset for next state in stack
		btn_released=false ; // reset for next state in stack
	}
}
