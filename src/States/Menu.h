#ifndef MENU_H
#define MENU_H

#include "State.h"

class Menu : 
    public State
    {

        private:
            std::string choice ;
            std::vector<std::string> choices ; 
            sf::Texture selectionArrowTexture ; // texture of the arrow used to indicate user's choice
            sf::Sprite selectionArrow ; // sprite of the arrow used to indicate user's choice
            sf::Font font;
            std::vector<sf::Text> choices_text ; 

            
        public:
            Menu(sf::RenderWindow* window, sf::View view);
            void update(const float &deltaTime);
            void render(sf::RenderTarget* target);
            void updateInput(const float& deltaTime);

    };



#endif