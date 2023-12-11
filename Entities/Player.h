#ifndef PLAYER_H
#define PLAYER_H
#define NB_TEXTURES_PLAYER 18 // 18 sprites necessary to display every moving positions (going down, up, ...) 
                                // TODO : remove this is C style and ugly and might cause runtime errors if we add sprites in cpp file wtihout adjusting size

#include "Entity.h"

class Player : public Entity {
private:
    // Add any additional member variables specific to the Player class here
    std::array<sf::Sprite, NB_TEXTURES_PLAYER> mvmtSprites ;  
    std::array<sf::Texture,NB_TEXTURES_PLAYER> mvmtTextures ;
    sf::Sprite playerSprite ; // the player that the user can move
    sf::Vector2f pos; // position of the player 


public:
    Player();
    ~Player();
    int initPlayerSprites();
    void render(sf::RenderTarget* target);
    void move(const float& dt, const float dir_x, const float dir_y);
    // Add any additional member functions specific to the Player class here
};

#endif

                        // // IDLE //
                        //     0 IDLE up
                        //     1 IDLE right
                        //     2 IDLE down
                        //     3 IDLE left
                        // // going left //
                        //     4 half left step
                        //     5 full left step
                        //     6 half right step
                        //     7 full right step
                        // // going right //
                        //     8 half left step
                        //     9 full left step
                        //     10 half right step
                        //     11 full right step
                        // // going up //
                        //     12 half right step
                        //     13 full right step
                        //     14 half left step
                        //     15 full left step
                        // // going down //
                        //     16 right step
                        //     17 left step  