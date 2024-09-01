#include "Menu.h"

Menu::Menu(sf::RenderWindow* window, sf::View view)
    : State(window,view)
{
    this->view = view ;  
    std::cout << "Entering Menu constructor \n";
    int resX = 1920 ; 
    int resY = 1080 ; 
    std::string arrowTextureFilename = "./ressources/Images/arrow_GUI.png" ;
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
    sf::Vector2f pos_text = {resX/2.f-100.f, resY/2.f-100.f};
    int policeSize = 30 ;
    for(std::string choice : choices){
        choice_text = sf::Text(choice,font,policeSize);
        choice_text.setFillColor(sf::Color::Black);
        choice_text.setPosition(pos_text);
        pos_text.y = pos_text.y + 50.f ; 
        choices_text.push_back(choice_text);
    }
    if(!selectionArrowTexture.loadFromFile(arrowTextureFilename)){ // loading image failed
        std::cout << "[Menu] Failed loading sprite \n";
        return ;
    }
    selectionArrow.setTexture(selectionArrowTexture);
    moveSelectionArrow();
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
    target->draw(selectionArrow);
}

void Menu::updateInput(const float& deltaTime){
    static bool btn_pushed = false ; 
    static bool btn_released = false ; 
    static int i = 0 ; 
    this->checkForQuit();
    if(acquireInput(sf::Keyboard::Down) || acquireInput(sf::Keyboard::S)){
        num_choice++;
    }
    if(acquireInput(sf::Keyboard::Up) || acquireInput(sf::Keyboard::Z)){
        num_choice--;
    }
    moveSelectionArrow();
}

void Menu::moveSelectionArrow(){
    // Places the arrow next to choice #choice
    if(num_choice < 0) num_choice = choices.size()-1 ; 
    else if(num_choice > choices.size()-1) num_choice = 0 ; 
    sf::Vector2f posArrow = choices_text[num_choice].getPosition();
    posArrow.x -= 50.f ;
    selectionArrow.setPosition(posArrow);
}

/**
 * @brief Handles single key press detection for a specified key, ensuring that each key press
 *        is registered only once per full press-release cycle.
 *
 * This function tracks the state of a key press, ensuring that the key is considered "pressed" 
 * only once per physical press and release action. It avoids multiple detections if the key is 
 * held down continuously.
 *
 * @param key The specific key to monitor
 * @return Returns `true` when a full press-release cycle of the specified key is detected.
 *         Returns `false` if the cycle is incomplete or ongoing.
 */
bool Menu::acquireInput(sf::Keyboard::Key key){
	static bool btn_pushed = false ; 
    static bool btn_released = false ; 
    static sf::Keyboard::Key last_key = sf::Keyboard::Unknown ; 
	if(sf::Keyboard::isKeyPressed(key)){
		btn_pushed = true ; 
        last_key = key ;
		return false ; 
	}
	if(btn_pushed && not(btn_released)){
		if(!sf::Keyboard::isKeyPressed(last_key)) btn_released = true ; 
		return false; 
	}
	if(btn_pushed && btn_released){
		btn_pushed=false ; // reset for next call
		btn_released=false ; // reset for next call 
        return true ; 
	}
    return false ; 
}

