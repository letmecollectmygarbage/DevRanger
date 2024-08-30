#include "Menu.h"

Menu::Menu(sf::RenderWindow* window, sf::View view)
    : State(window,view)
{
    this->view = view ;  
    std::cout << "Entering Menu constructor \n";
    int resX = 1920 ; 
    int resY = 1080 ; 
    

    sf::Vector2f pos = {0.f,0.f} ;  
    std::string textureFilename = "./ressources/Images/background_96x96.png" ;
    sf::Sprite sprite ; 
    if(!background_texture.loadFromFile(textureFilename)){ // loading image failed
        std::cout << "Failed loading sprite \n";
        return ;
    } 
    sf::Vector2u sizeTexture = background_texture.getSize() ;
    int lines = resY/sizeTexture.y + 1 ; // min number of lines to fill resX px with texture
    if(resY%sizeTexture.y==0) lines = resY/sizeTexture.y ; // lucky case
    int cols = resX/sizeTexture.x + 1 ; // min number of cols to fill resY px with texture
    if(resX%sizeTexture.x==0) cols = resX/sizeTexture.x ; // lucky case
    background_texture.setSmooth(true); // blurs edges
    for(int i = 0 ; i < lines ; i++){
        pos.x = 0.f ; // reset
        for(int j = 0 ; j < cols ; j++){
            // 
            sprite.setTexture(background_texture);
            sprite.setPosition(pos);
            background_sprites.push_back(sprite);
            pos.x += sprite.getGlobalBounds().getSize().x ;
        }
        pos.y += sprite.getGlobalBounds().getSize().y ; 
    }
    choices.push_back("Retry");
    choices.push_back("Exit DevRanger");
    if (!font.loadFromFile("./ressources/Fonts/arial.ttf")){
        std::cout << "Menu() failed loading font \n";
        return ;
    }
        // set the character size
    sf::Text choice_text ;
    sf::Vector2f pos_text = {0.f,0.f};
    int policeSize = 30 ;
    for(std::string choice : choices){
        choice_text = sf::Text(choice,font,policeSize);
        choice_text.setFillColor(sf::Color::Green);
        choice_text.setPosition(pos_text);
        pos_text.y = pos_text.y + 50.f ; 
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


    // BACKGROUND DRAWING
    for(sf::Sprite sprite : background_sprites){
        target->draw(sprite);
    }

    // FOREGROUND DRAWING
    for(sf::Text choice : choices_text){
        target->draw(choice);
    }
    target->draw(test_text);


}



void Menu::updateInput(const float& deltaTime){
    static bool btn_pushed = false ; 
    static bool btn_released = false ; 
    static int i = 0 ; 
    this->checkForQuit();
}

