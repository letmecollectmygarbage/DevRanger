#include "State.h"

// Constructor
State::State(sf::RenderWindow* window, sf::View view){
	this->window = window;
	this->view = view ;
	this->quit = false ; 
	// Goal : switch view between each state
	// sf::Vector2f viewSize = view.getSize();
	// stateView = sf::View(sf::FloatRect({0.f,0.f},viewSize));
}

// Destructor
State::~State(){	
}

const bool &State::getQuit() const{
	// check if state wants to quit
	return this->quit;
}


/*
*	Switches game to next state in the stack if the Escape 
*	key is pressed.
*
*/
void State::checkForQuit(){
	static sf::Keyboard::Key escapeKey = sf::Keyboard::Escape ;
	if(sf::Keyboard::isKeyPressed(escapeKey)){
		while(sf::Keyboard::isKeyPressed(escapeKey)){}
		this->quit=true; // exits state 
	}
}

void State::acquireInput(sf::Keyboard::Key key){
    while(sf::Keyboard::isKeyPressed(key)==true){
        // stay in loop while key is pressed
    }
    // exit when key is released
}
