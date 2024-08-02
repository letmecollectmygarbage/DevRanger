#ifndef GAME_H
#define GAME_H

#include "States/GameState.h"
#include "Map/GameWorld.h"
#include "wtypes.h" // to get screen resolution

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::VideoMode videoMode ; 
	int resX ; // X resolution of the game's window
	int resY  ; // Y resolution of the game's window
	std::string title = "DevRanger"; // game's name
	int framerate_limit ;
	bool VSync ; // True = enabled
	sf::Event sfEvent; 
	GameWorld gameWorld ; 

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states ; // a stack containing every game state
	//Initialization

	void initWindow();
	void initStates();

public:
	// attributes 
	sf::View view;

	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

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