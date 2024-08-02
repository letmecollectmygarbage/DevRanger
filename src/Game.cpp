#include "Game.h"
#include "Map/GameWorld.h"


// Initalizes window of the game
void Game::initWindow()
{
	this->videoMode = sf::VideoMode::getDesktopMode();
	resX = videoMode.width ;
	resY = videoMode.height ; 
	std::cout << "[INFO] resX = " << resX <<", resY = "<<resY <<"\n";
	this->framerate_limit = 60 ; 
	bool isVSyncEnabled = true;
	this->VSync = true ;
	this->window = new sf::RenderWindow(this->videoMode, this->title, sf::Style::Fullscreen);
	this->window->setFramerateLimit(this->framerate_limit);
	this->window->setVerticalSyncEnabled(VSync);
	// create a view with the rectangular area of the 2D world to show
	float rectLeft = 0.f;
    float rectTop = 0.f;
    float rectWidth = resX / 4 ;
    float rectHeight = resY / 4 ; 
    gameView = sf::View(sf::FloatRect(rectLeft, rectTop, rectWidth, rectHeight));
	window->setView(gameView);
}

// Initializes states of the game.
void Game::initStates(){
	GameState* newState = new GameState(this->window,this->gameView);
	this->states.push(newState);
}

//Constructor.
Game::Game(){
	this->initWindow();
	this->initStates();
	this->gameWorld = GameWorld();
}

// Destructor for exiting the game.
// Frees the memory of every state of the game.
Game::~Game(){
	std::cout << "Ending Application!" << "\n";
	delete this->window;
	while(this->states.empty())	{
		delete this->states.top(); // removes data holded by pointer
		this->states.pop(); // removes the pointer
	}
}


/*Updates dt variable with time taken to update & render 1 frame.*/
void Game::updateDt(){
	this->dt = this->dtClock.restart().asSeconds();
}

// Closes game window if sf::Event::Closed is in the event queue
void Game::updateSFMLEvents(){
	while (this->window->pollEvent(this->sfEvent)){
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}


void Game::update(){
	this->updateSFMLEvents();
	// if there is at least one state in the stack:
	if(!this->states.empty()){
		// updates current state with state's specialized update method:
		this->states.top()->update(this->dt) ; 
		// leave current state:
		if(this->states.top()->getQuit()){
			this->states.top()->endState(); // put endState on top of stack and execute it
			delete this->states.top(); // delete endState's data
			this->states.pop(); // remove pointer to endState
		}
	}
	// Application End (stack of states is empty)
	else{Game::~Game();}
		
}

// clear window, draw, display
void Game::render(){
	this->window->clear();
	for(int i = 0 ; i < gameWorld.gridSize.x ; i++){
		this->window->draw(gameWorld.tiles[0][i]->sprite); // draws firstRow
		this->window->draw(gameWorld.tiles[1][i]->sprite); // draws bottomRow
	}

	//Render items
	if(!this->states.empty()){
		this->states.top()->render(this->window);
	}
	this->window->display();
}

void Game::run(){
	while (this->window->isOpen()){
		this->updateDt();
		this->update();
		this->render();
	}
}