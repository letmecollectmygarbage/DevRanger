#ifndef GAME_H
#define GAME_H

#include "States/GameState.h"
#include "Map/GameWorld.h"

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	// i should probably put this in a state but idk where else to put it 
	GameWorld gameWorld ; // this line produces an error

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states ; // a stack containing every game state
	//Initialization

	void initWindow();
	void initStates();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif