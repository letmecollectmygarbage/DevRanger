#include "Menu.h"

Menu::Menu(sf::RenderWindow* window, sf::View view)
    : State(window,view)
{
    std::cout << "Entering Menu constructor \n";
    choices.push_back("Retry");
    choices.push_back("Exit DevRanger");
    if (!font.loadFromFile("./ressources/Fonts/arial.ttf")){
        std::cout << "Menu() failed loading font \n";
        return ;
    }
        // set the character size
    sf::Text choice_text ;
    choice_text.setCharacterSize(24); // in pixels, not points!
    choice_text.setFillColor(sf::Color::Red);
    choice_text.setStyle(sf::Text::Bold);
    sf::Vector2f pos_text = {200.f,200.f};
    for(std::string choice : choices){
        choice_text.setString(choice);
        choice_text.setPosition(pos_text);
        pos_text.y = pos_text.y - 50.f ; 
        choices_text.push_back(choice_text);
    }
    
}



// Destructor 
Menu::~Menu(){
}

void Menu::endState(){
    std::cout << "[Menu] endState is reached !" << "\n" ;
}

void Menu::update(const float &deltaTime){
    this->updateInput(deltaTime);  
}


void Menu::render(sf::RenderTarget* target){
    //this->statePlayer.render(target);
    for(auto choice : choices_text){
        target->draw(choice);
    }
}



void Menu::updateInput(const float& deltaTime){
    static bool btn_pushed = false ; 
    static bool btn_released = false ; 
    static int i = 0 ; 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){ // wait until key is released
            btn_pushed = true ; 
        }
        btn_released = true ; 
        i++;
        if(i > choices.size()-1) i=0;
        choice = choices[i];
        std::cout << choice << "\n";
    }
}

