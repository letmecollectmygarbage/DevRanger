#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : 
    public State
    {

        private:
            //Entity whiteRectangle ; // to replace by actual hero
            Player player ; // hey it's my player !!!




        public:
            GameState(sf::RenderWindow* window);
            virtual ~GameState();

            // Functions
            
            void endState();

            void updateKeybinds(const float& dt);
            void update(const float& dt);
            void render(sf::RenderTarget* target = nullptr);
    };

#endif
