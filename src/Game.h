#ifndef GAME_H
#define GAME_H

#include "States/GameState.h"
#include "States/Menu.h"
#include "Map/GameWorld.h"

#include "wtypes.h" // to get screen resolution

class Game
{
private:
	static Game gameInstance ; // unique game instance (singleton)
	Game(const Game&) = delete; // Delete copy constructor
    Game& operator=(const Game&) = delete; // Delete copy assignment
	/// Window parameters ///
	sf::RenderWindow *window;
	sf::VideoMode videoMode ; 
	int resX ; // X resolution of the game's window
	int resY  ; // Y resolution of the game's window
	int viewScaleFactor ;
	float rectWidth ; 
	float rectHeight ;
	sf::Vector2f sizeViewRect ;
	sf::Vector2f originViewRect ; 
	bool VSync ; // True = enabled
	
	std::string title = "DevRanger"; // game's name
	int framerate_limit ;
	
	
	sf::Event sfEvent; 
	sf::Clock deltaTimeClock;
	float deltaTime;
	std::stack<State*> states ; // a stack containing every game state
	//Initialization

	void initWindow();

public:
	// attributes 
	sf::View gameView ;
	sf::View menuView ; 
	static Game& getInstance(); // Return reference instead of object

	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions
	void setWindowView(sf::View view);

	//Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif