#ifndef MENU_H
#define MENU_H

#include "State.h"

class Menu : 
    public State
    {

        private:
            std::string choice ;
            bool quit ; 
            std::vector<std::string> choices ; // vector of choices
            int num_choice ; // choice index in the choices vector
            sf::Texture selectionArrowTexture ; // texture of the arrow used to indicate user's choice
            sf::Sprite selectionArrow ; // sprite of the arrow used to indicate user's choice
            sf::Font font;
            std::vector<sf::Text> choices_text ; 
            sf::Text test_text ; 
            sf::Texture background_texture ; // texture used for all background sprites
            std::vector<sf::Sprite> background_sprites ; // background sprites

            
        public:
            Menu(sf::RenderWindow* window, sf::View view);
            ~Menu();
            void update(const float &deltaTime);
            void render(sf::RenderTarget* target);
            void updateInput(const float& deltaTime);
            void endState();
            void moveSelectionArrow();
            int getNum_choice();
            
            

    };



#endif