#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib> // for random enemy positions
#include <ctime> // for random enemy positions
#include <chrono> // for FPS measurement
#include <stack>
#include <vector>
#include <map>

class State
{
	private:
		sf::RenderWindow* window ;
		std::vector<sf::Texture> textures;

	public:
		State(sf::RenderWindow* window);
		virtual ~State();


		virtual void endState() = 0; // (virtual ... = 0) means you MUST create this function for children classes
		virtual void update(const float& dt) = 0; 
		virtual void render(sf::RenderTarget* target = nullptr) = 0;  // argument means you can draw at another window but default is principal window
	};

#endif