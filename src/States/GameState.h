#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : 
    public State
    {

        private:
            // Player used for this state. Useful if you want to control another player during the game. (cf. GTA5).
            Player statePlayer ; 
            Monster stateMonster ;
            sf::Clock clock; // // starts the clock
            sf::Time time1,time2 ; // 
        public:
            GameState(sf::RenderWindow* window, sf::View view);
            virtual ~GameState();

            void endState();
            void updateInput(const float& deltaTime);
            void updateMonsterMoveDirection(const float& deltaTime);
            void update(const float& deltaTime);
            void render(sf::RenderTarget* target = nullptr);
    };

#endif
