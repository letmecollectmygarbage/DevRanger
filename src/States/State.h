#ifndef STATE_H
#define STATE_H

#include "../Entities/Player.h"

#include "../Entities/Monster.h"
#include "../Map/GameWorld.h"

class State
{
	private:
		
		
		std::vector<sf::Texture> textures;
		bool quit;

	public:
		sf::View view;
		sf::RenderWindow* window ;
		
		State(sf::RenderWindow* window, sf::View view);
		virtual ~State();


		const bool& getQuit() const;

		virtual void updateInput(const float& dt)=0; 
		virtual void endState() = 0;
		virtual void checkForQuit(); 
		virtual void update(const float& dt) = 0; // (virtual ... = 0) means you MUST create this function for children classes
		// argument means you can draw at another 
		// window but default is principal window 
		virtual void render(sf::RenderTarget* target = nullptr) = 0;
		bool acquireInput(sf::Keyboard::Key key); 
	};

#endif