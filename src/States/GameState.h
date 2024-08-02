#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : 
    public State
    {

        private:
            Player statePlayer ; // is this my player from Player class? 




        public:
            GameState(sf::RenderWindow* window, sf::View view);
            virtual ~GameState();

            // Functions
            
            void endState();

            void updateInput(const float& dt);
            void update(const float& dt);
            void render(sf::RenderTarget* target = nullptr);
    };

#endif
