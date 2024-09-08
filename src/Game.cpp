#include "Game.h"



// Initalizes window of the game
void Game::initWindow()
{
	this->videoMode = sf::VideoMode::getDesktopMode();
	resX = videoMode.width;
	resY = videoMode.height; 
	std::cout << "[INFO] resX = " << resX <<", resY = "<<resY <<"\n";
	this->framerate_limit = 60 ; 
	bool isVSyncEnabled = true;
	this->VSync = true ;
	this->window = new sf::RenderWindow(this->videoMode, this->title, sf::Style::Fullscreen);
	this->window->setFramerateLimit(this->framerate_limit);
	this->window->setVerticalSyncEnabled(VSync);
	// create a view with the rectangular area of the 2D world to show
	viewScaleFactor = 1 ;
	originViewRect = {0.f,0.f};
    rectWidth = resX / viewScaleFactor ;
    rectHeight = resY / viewScaleFactor ; 
	sizeViewRect = {rectWidth,rectHeight};
    gameView = sf::View(sf::FloatRect(originViewRect,sizeViewRect));
	menuView = sf::View(sf::FloatRect(originViewRect,{800.f,600.f})); // this has no impact
	window->setView(gameView);
}



//Constructor.
Game::Game(){
	this->initWindow();
	Menu* menuState = new Menu(this->window,this->menuView);
	this->states.push(menuState);
	GameState* gameState = new GameState(this->window,this->gameView);
	this->states.push(gameState);

}

// Implement singleton pattern //

// Define the static member
Game Game::gameInstance;

Game& Game::getInstance(){
	return gameInstance;
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


/*Updates deltaTime variable with time taken to update & render 1 frame.*/
void Game::updateDeltaTime(){
	this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}

// Closes game window if sf::Event::Closed is in the event queue
void Game::updateSFMLEvents(){
	while (this->window->pollEvent(this->sfEvent)){
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

/*
*	Call update methods of current state.
*	Switches current state if state quits
*/
void Game::update(){
	this->updateSFMLEvents();
	// if there is at least one state in the stack:
	if(!this->states.empty()){
		// updates current state with state's specialized update method:
		this->states.top()->update(this->deltaTime) ; 
		// leave current state:
		if(this->states.top()->getQuit()){
			this->states.top()->endState(); // save progression 
			delete this->states.top(); 
			
			setWindowView(gameView); // this only recenters view, does not impact res like I want
			this->states.pop(); // remove current state from stack
		}
	}
	// Application End (stack of states is empty)
	else{Game::~Game();}
		
}

// clear window, draw, display
void Game::render(){
	this->window->clear();


	//Render items
	if(!this->states.empty()){
		this->states.top()->render(this->window);
	}
	this->window->display();
}

void Game::run(){
	while (this->window->isOpen()){
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}

void Game::setWindowView(sf::View view){
	this->window->setView(view);
}