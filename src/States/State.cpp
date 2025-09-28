#include "State.h"

// Constructor
State::State(sf::RenderWindow* window, sf::View view)
    : window{window}
    , view{view}
	, quit{false}
{
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
void State::checkForQuit()
{
	static sf::Keyboard::Key escape_key = sf::Keyboard::Escape ;
	if(sf::Keyboard::isKeyPressed(escape_key))
	{
		while(sf::Keyboard::isKeyPressed(escape_key)){}
		this->quit=true; // exits state 
	}
}


/*
* 	Goal : Perform an action when a key is pressed and released. 
* 	This method will likely be called multiple times per action because the key will be pressed longer than one frame cycle.
*	Example : Player presses space > a flag is enabled and must stay so for next call (static)
	While the space key is not released only this flag is enabled, and False is returned
	Player then releases the space key : the static flag is reset and True is returned
*/
bool State::acquireInput(sf::Keyboard::Key key)
{
	//static bool key_already_pressed = true ;
	
	// key is still pressed, waiting for release...
    if(sf::Keyboard::isKeyPressed(key))
	{
		return false ;
	}
	// key has been released
	else
	{
		//key_already_pressed = false ; 
		return true ; 
	}
	
}
