#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : 
    public State
    {

        private:
            // Player used for this state. Useful if you want to control another player during the game. (cf. GTA5).
            Player statePlayer ; 

        public:
            GameState(sf::RenderWindow* window, sf::View view);
            virtual ~GameState();

            void endState();
            void updateInput(const float& dt);
            void update(const float& dt);
            void render(sf::RenderTarget* target = nullptr);
    };

#endif
