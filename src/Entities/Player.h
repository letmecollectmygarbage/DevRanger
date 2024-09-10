#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Player class is a specialization of Entity class
class Player : public Entity {
private:
    bool alive ; // Determines if hero is alive or dead (to implement)
    bool fireballBurning = false ; // 
    float time_to_live_fireball ; // in seconds
    std::vector<std::string> fireballs_colors ; // pink,red,blue
    int N_fireballs ; // number of sprites for each fireball color
    std::string dirFireball ; // direction of the fireball "up", "down", "left" or "right"
    sf::Texture heart_texture ; // original img of a 2D heart 
    std::vector<sf::Sprite> health_hearts ; 
    sf::Texture hurt_texture ; //texture to use when Player is hurt
    sf::Sprite hurt ; // sprite to use when Player is hurt

    sf::Sprite fireball ; // only fireball displayed
    std::string lastMovement; // last movement of the player ("UP","DOWN","LEFT","RIGHT","IDLE")
    std::string lastMovingMovement ; // same set as lastMovement excluding "IDLE" (used for fireball direction)

    /* dictionnary of fireball color (pink,red,blue) vs sprite
    * ex : { "pink" : {s1,s2,...,s6} , "red" : {s1,s2,...,s6} , "blue" : {s1,s2,...,s6} }
      with s1,...,s6 being sprites                                                        */
    std::map<std::string,std::vector<sf::Sprite>> fireball_color_sprites ; 

    /* dictionnary of fireball color (pink,red,blue) vs texture
    * ex : { "pink" : {t1,t2,...,t6} , "red" : {t1,t2,...,t6} , "blue" : {t1,t2,...,t6} }
      with s1,...,s6 being textures                                                       */
    std::map<std::string,std::vector<sf::Texture>> fireball_color_textures ; 

    // For each orientation of the fireball, we have a corresponding map(color,sprite)
    // ex : {"LEFT":color_sprite_left,"RIGHT":color_sprite_right,...}
    std::map < std::string, std::map<std::string,std::vector<sf::Sprite>> > orientation_map ; 

    
    

public:
    Player();
    ~Player();
    
    int initSprites(); // First method called 
    void initSpritesFireballs(); // subroutine of initSprites
    void init_life_display(); // Second method called

    // Called every frame //

    void render(sf::RenderTarget* target); 
    void update(const float &deltaTime);
    void move(const float& deltaTime, const float dir_x,const float dir_y); 

    // Called potentially every frame //

    void nextSprite(float dir_x, float dir_y); 
    void nextSpriteIDLE(); 
    
    
    void manage_life_display(); // called when attacked
    void attack(); // called when attack
    void manageFireballLifetime(float seconds_to_live); // manages lifetime of fireball
    void manageFireballTrajectory(float deltaTime); 

    // getters/setters


    
};

#endif