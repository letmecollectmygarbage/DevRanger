#include "GameState.h"
#include "../Map/GameWorld.h"

GameState::GameState(sf::RenderWindow* window, sf::View view)
    : State(window,view) 
    , movement_keys{sf::Keyboard::Key::Z, sf::Keyboard::Key::Q, sf::Keyboard::Key::S, sf::Keyboard::Key::D}
    , attack_keys{sf::Keyboard::Key::Space}

{
    gameWorld = GameWorld(); // Initialize the class member
    receiveMap(gameWorld.tiles);
    key_dir[sf::Keyboard::Key::Z] = {0.f,-1.f} ;
    key_dir[sf::Keyboard::Key::Q] = {-1.f,0.f} ;
    key_dir[sf::Keyboard::Key::S] = {0.f,1.f} ;
    key_dir[sf::Keyboard::Key::D] = {1.f,0.f} ;
    
}

// Destructor (but does nothing yet)
GameState::~GameState(){
}


//State before quitting where you can save hero's progression for example
void GameState::endState(){
}

// Checks for user input and does something else
void GameState::update(const float &deltaTime){
    this->updateInput(deltaTime);  
    this->updateMonsterMoveDirection(deltaTime);
    this->statePlayer.update(deltaTime);
    this->manageCollisions(deltaTime);
    //std::cout << "gamestate updating" << std::endl ; 
}

void GameState::render(sf::RenderTarget* target){
    // BACKGROUND
    int numVectors = this->gameWorld.tiles.size(); 
	int numSprites ;
	for(int i = 0 ; i < numVectors ; i++)
    {
		numSprites = gameWorld.tiles[i]->sprites.size();
		for(int j = 0 ; j < numSprites ; j++ )
        {
		    this->window->draw(gameWorld.tiles[i]->sprites[j]);
		}
	}
    // FOREGROUND
    this->statePlayer.render(target);
    this->stateMonster.render(target);
    
}

// Update player's input
/*
*   2 modes can be enabled independatly : movement mode and attack mode
*   To enable movement mode : press Z, Q, S or D
*   To enable attack mode : press Space bar
*   To leave each mode : release key
*   If no mode is enabled, method will check if any key is pressed and return
*   Else, method will check if it can exit the given mode. 
*
*/
void GameState::updateInput(const float& deltaTime)
{
    static sf::Keyboard::Key space_key = sf::Keyboard::Space ;
    this->checkForQuit();
    static bool attack_mode = false ; 
    static bool movement_mode = false ; 
    static sf::Keyboard::Key mvmt_key_pressed ;
    
    // Check if movement mode needs to be enabled
    if(!movement_mode)
    {
        for(auto key : movement_keys)
        {
            if(sf::Keyboard::isKeyPressed(key))
            {
                movement_mode = true ; 
                mvmt_key_pressed = key ; 
                break ; // player can move only one direction at the time for now
            }
        }
    }
    // check if movement mode can be disabled 
    else
    {
        if(!sf::Keyboard::isKeyPressed(mvmt_key_pressed))
        {
            movement_mode = false ; 
        }
        else
        {
            sf::Vector2f dir = key_dir[mvmt_key_pressed] ;
            this->statePlayer.move(deltaTime, dir.x, dir.y);
        }
    }

    // ATTACK:
    if(sf::Keyboard::isKeyPressed(space_key))
    {
        acquireInput(space_key);
        this->statePlayer.attack();
    }
    // no key pressed, IDLE
    else
    {
        this->statePlayer.move(deltaTime, 0.f, 0.f);  // todo : investigate relevancy...
    }
    if(isPlayerTouchingMonster()){
        MonsterAttacksPlayer();
        if(statePlayer.getSuffering()) statePlayer.manageSuffering(true); // make sure he suffers for an additional 0.5s
    } 
    statePlayer.manageSuffering(false);
    view.setCenter(this->statePlayer.pos);
    window->setView(this->view);
}

void GameState::manageCollisions(const float& deltaTime)
{
    if(!isPlayerTouchingWall()){
        return ;
    } 
    std::string relative_pos_of_obstacle = "";

    relative_pos_of_obstacle = whereIsObstacleComparedToPlayer();
    statePlayer.latest_obstacles.clear();
    std::cout << relative_pos_of_obstacle << std::endl ;
}


    // // LEFT:
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    // {
    //     this->statePlayer.move(deltaTime,-1.f,0.f);
    //     if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,1.f,0.f);
    // }
    // // UP:
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    // {
    //     this->statePlayer.move(deltaTime,0.f,-1.f);
    //     if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,0.f,1.f);
    // }
    // // RIGHT:
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    // {
    //     this->statePlayer.move(deltaTime,1.f,0.f);
    //     if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,-1.f,0.f);
    // } 
    // // DOWN:
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    // {
    //     this->statePlayer.move(deltaTime,0.f,1.f);
    //     if(isPlayerTouchingWall()) this->statePlayer.move(deltaTime,0.f,-1.f);
    // }

// Calculates monster to hero direction 
// move monster in this direction to attack hero
// AB' = (xB - xA, yB - yA)  
void GameState::updateMonsterMoveDirection(const float& deltaTime){
    this->checkForQuit();
    sf::Vector2f moveToHero = statePlayer.pos - stateMonster.getSprite().getPosition() ; 
    sf::Vector2f nullVector = {0.f,0.f};
    if(moveToHero == nullVector) return ; // so div never equals 0

    float dir_x, dir_y =0.f ; 
    float div ; // what I divide dir_x & dir_y with to 1-norm them
    div = std::max(std::abs(moveToHero.x),std::abs(moveToHero.y)); // strictly positive
    dir_x = moveToHero.x/std::abs(div) ;
    dir_y = moveToHero.y/std::abs(div) ; 
    stateMonster.move(deltaTime,dir_x,dir_y); 

    // DEBUG PRINT STATEMENTS
    // time1 = clock.getElapsedTime();
    // if(time1.asSeconds() > 5)
    // { 
    //     std::cerr << "[GameState::updateMonsterMoveDirection] " ;
    //     std::cerr << "statePlayer.pos : " << statePlayer.pos.x << ","  ;
    //     std::cerr << statePlayer.pos.y << " | stateMonster.pos :" ;
    //     std::cerr << stateMonster.pos.x << "," << stateMonster.pos.y ;
    //     std::cerr << " | moveToHero : " << moveToHero.x << ","  ;
    //     std::cerr  << moveToHero.y << "\n" ;
    //     std::cerr << "dir_x , dir_y : " << dir_x << " , " << dir_y <<"\n" ; 
    //     clock.restart();
    // }
}

void GameState::receiveMap(std::vector<GameTile*> tiles){
    this->tiles = tiles ;
}

bool GameState::isPlayerTouchingWall(){
    /////////////////////////////
    sf::FloatRect player_feet_rect = statePlayer.getSprite().getGlobalBounds();
    player_feet_rect.top += player_feet_rect.height * 0.9f ; // we make the top point go down by 90% of the player's height
    player_feet_rect.height /= 5 ; // we divide by 5 the height of the player to get the feet's height
    //////////////////////////////

    bool intersection = false ; 



    
    for(GameTile* tile : this->tiles){  // todo : check only the tiles within a reasonable distance
        if(!tile->isFree)
        {
            for(sf::Sprite sprite : tile->sprites)
            {
                sf::FloatRect wallRect = sprite.getGlobalBounds();
                if(player_feet_rect.intersects(wallRect))
                {
                    statePlayer.latest_obstacles.push_back(sprite) ; // typically the player can intersect with 1 or 2 sprites maximum
                    intersection = true ;
                    
                } 
            }
        }
    }
    if(intersection)
    {
        std::cout << "player_feet_rect.height = " << player_feet_rect.height << std::endl ; 
        std::cout << "player_feet_rect.width = " << player_feet_rect.width << std::endl ;  
    } 
    else statePlayer.latest_obstacles.clear();
    return intersection ; 
}

bool compare_x(sf::Sprite a, sf::Sprite b) {
    float x_a = a.getGlobalBounds().left ;
    float x_b = b.getGlobalBounds().left ;
    return x_a < x_b;
}

bool compare_y(sf::Sprite a, sf::Sprite b) {
    float y_a = a.getGlobalBounds().left ;
    float y_b = b.getGlobalBounds().left ;
    return y_a < y_b;
}

std::string GameState::whereIsObstacleComparedToPlayer()
// you should enter this method only if player is touching a wall
{
    /////////////////////////////
    sf::FloatRect player_feet_rect = statePlayer.getSprite().getGlobalBounds();
    player_feet_rect.top += player_feet_rect.height * 0.9f ; // we make the top point go down by 90% of the player's height
    player_feet_rect.height /= 5 ; // we divide by 5 the height of the player to get the feet's height
    //////////////////////////////
    sf::FloatRect player_bounds = statePlayer.getSprite().getGlobalBounds() ;
    std::vector<sf::Sprite> obstacles = statePlayer.latest_obstacles ;
    sf::FloatRect cumulated_obstacle  = sf::FloatRect();
    // if the obstacle contains more than sprite we must get the global dimensions of it
    std::cout << "entered GameState::whereIsObstacleComparedToPlayer()" << std::endl ; 
    if(obstacles.size() == 1)
    {
        std::cout << "GameState::whereIsObstacleComparedToPlayer() : case one obstacle" << std::endl ; 
        cumulated_obstacle = statePlayer.latest_obstacles.at(0).getGlobalBounds() ;
    }
    else if(obstacles.size() > 1)
    {
        std::cout << "GameState::whereIsObstacleComparedToPlayer() : case multiple obstacles : " << obstacles.size() << std::endl ; 
        // first case : the obstacles are aligned vertically
        if(obstacles.front().getGlobalBounds().left == obstacles.at(1).getGlobalBounds().left)
        {
            std::cout << "GameState::whereIsObstacleComparedToPlayer() : case vertical" << std::endl ; 
            cumulated_obstacle.left = obstacles.front().getGlobalBounds().left ; // whatever the sorting it's true
            cumulated_obstacle.width = obstacles.front().getGlobalBounds().width ; // the width will not change
            std::sort(obstacles.begin(), obstacles.end(), compare_y); // sort from the most top obstacle to most bottom 
            cumulated_obstacle.top = obstacles.front().getGlobalBounds().top ;
            
            for(sf::Sprite obstacle_sprite : obstacles)
            {
                cumulated_obstacle.height += obstacle_sprite.getGlobalBounds().height ;
            }
            
        }
        // second case : the obstacles are aligned horizontally
        else
        {
            cumulated_obstacle.top = obstacles.front().getGlobalBounds().top ; // whatever the sorting it's true
            cumulated_obstacle.height = obstacles.front().getGlobalBounds().height ; // the height will not change
            std::sort(obstacles.begin(), obstacles.end(), compare_x); // sort from the most left obstacle to most right 
            cumulated_obstacle.left = obstacles.front().getGlobalBounds().left ;
            
            for(sf::Sprite obstacle_sprite : obstacles)
            {
                cumulated_obstacle.width += obstacle_sprite.getGlobalBounds().width ;
            }
            std::cout << "GameState::whereIsObstacleComparedToPlayer() : case horizontal" << std::endl ; 
        }
    }
    else
    {
        std::cout << "Error : you should not enter this method if obstacles is empty" << std::endl ; 
    }

    std::cout << "cumulated_obstacle.top = " << cumulated_obstacle.top << std::endl ; 
    std::cout << "cumulated_obstacle.left = " << cumulated_obstacle.left << std::endl ; 
    std::cout << "cumulated_obstacle.height = " << cumulated_obstacle.height << std::endl ; 
    std::cout << "cumulated_obstacle.width = " << cumulated_obstacle.width << std::endl ; 
    std::cout << std::endl ;
    std::cout << "obstacles.first().top = " << obstacles.front().getGlobalBounds().top << std::endl ; 
    std::cout << "obstacles.first().left = " << obstacles.front().getGlobalBounds().left << std::endl ; 
    std::cout << "obstacles.first().height = " << obstacles.front().getGlobalBounds().height << std::endl ; 
    std::cout << "obstacles.first().width = " << obstacles.front().getGlobalBounds().width << std::endl ; 

    // We see which points are inside the cumulutad obstacle
    sf::Vector2f top_left_pt = {player_feet_rect.left, player_feet_rect.top};
    sf::Vector2f bottom_left_pt = {player_feet_rect.left , player_feet_rect.top + player_feet_rect.height};
    sf::Vector2f top_right_pt = {player_feet_rect.left + player_feet_rect.width , player_feet_rect.top};
    sf::Vector2f bottom_right_pt = {player_feet_rect.left + player_feet_rect.width, player_feet_rect.top + player_feet_rect.height};

    if(cumulated_obstacle.contains(top_left_pt) && cumulated_obstacle.contains(bottom_left_pt)) return "LEFT" ;
    if(cumulated_obstacle.contains(top_right_pt) && cumulated_obstacle.contains(bottom_right_pt)) return "RIGHT" ;
    if(cumulated_obstacle.contains(bottom_left_pt) && cumulated_obstacle.contains(bottom_right_pt)) return "UNDER" ;
    if(cumulated_obstacle.contains(top_left_pt) && cumulated_obstacle.contains(top_right_pt)) return "ABOVE" ;
    return "ERROR" ;
}

bool GameState::isPlayerTouchingMonster(){
    sf::FloatRect playerRect = statePlayer.getSprite().getGlobalBounds();
    sf::FloatRect monsterRect = stateMonster.getSprite().getGlobalBounds();
    if(playerRect.intersects(monsterRect)) return true ;
    return false ; 
}

void GameState::MonsterAttacksPlayer(){
    // Consequences of an attack from the monster on the player
    int attackTimeout = 1 ; 
    static bool firstAttack = true ;
    if(firstAttack){
        int hp = statePlayer.getHealth() -10 ; 
        statePlayer.setHealth(hp) ;
        firstAttack = false ;
    }
    else{
        time1 = clock.getElapsedTime();
        if(time1.asSeconds() > attackTimeout){
            int hp = statePlayer.getHealth() -10 ; 
            statePlayer.setHealth(hp) ;
            statePlayer.setSuffering(true);
            clock.restart();
            statePlayer.manage_life_display();
        }
        else{return;} // no attack
    }
    


}