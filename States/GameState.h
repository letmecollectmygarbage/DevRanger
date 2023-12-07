#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : 
    public State
    {
        public:
            GameState(sf::RenderWindow* window);
            virtual ~GameState();

            // Functions
            
            void endState();
            void update(const float& dt);
            void render(sf::RenderTarget* target = nullptr);
    };

#endif
