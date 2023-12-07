#include "Game.h"

//Static functions

//Initializer functions
void Game::initWindow()
{
	/*Creates a SFML window using options from a window.ini file.*/
	std::string title = "DevRanger";
	sf::VideoMode window_bounds(800, 600);
	unsigned int framerate_limit = 120;
	bool isVSyncEnabled = true;

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(isVSyncEnabled);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

//Constructors/Destructors
Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	/*
	* Destructor for exiting the game : 
	* 	frees the memory of every state which composes the game
	*/
	delete this->window;
	while(this->states.empty())
	{
		delete this->states.top(); // removes data holded by pointer
		this->states.pop(); // removes the pointer
	}
		
}

//Functions
void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame.*/

	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();
	if(!this->states.empty())
		this->states.top()->update(this->dt);
}

void Game::render()
{
	this->window->clear();

	//Render items
	if(!this->states.empty())
	{
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

