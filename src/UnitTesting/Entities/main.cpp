#include "../../Entities/Entity.h"

// compile me with : 
// g++ -o src/UnitTesting/Entities/EntityUnitTest src/UnitTesting/Entities/main.cpp src/Entities/Entity.cpp -IC:\SFML\include\ -LC:\SFML\lib\ -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window
// execute me with : 
// .\src\UnitTesting\Entities\EntityUnitTest.exe

bool testSufferingLongEnough(Entity entity);
bool testSufferingNotLongEnough(Entity entity);

int main(void){
    std::cout << "Hello World ! " << "\n";
    Entity entity = Entity();
    std::cout << "Entity created !\n";
    sf::Sprite entitySprite = entity.getSprite();
    std::cout << "Sprite obtained ! \n" ;
    //static_assert()

    if(testSufferingLongEnough(entity) == true) std::cout << "Test #1 SUCCEDED !\n";
    else{std::cout << "Test #1 FAILED ! \n";}
    if(testSufferingNotLongEnough(entity)) std::cout << "Test #2 SUCCEDED !\n";
    else{std::cout << "Test #2 FAILED ! \n";}



    return 0 ; 

}

// Verify that manageSuffering disables suffering after 0.5s
bool testSufferingLongEnough(Entity entity){
    sf::Clock clock ;
    sf::Time time ; 
    entity.setSuffering(true); 
    clock.restart(); // local clock starts before internal clock of manageSuffering()
    while(entity.getSuffering()){
        time = clock.getElapsedTime();
        entity.manageSuffering();
    }
    std::cout << "time(s)="<< time.asSeconds() << "\n"; // should be greater than 0.5s
    if(time.asSeconds() >= 0.5) return true ; 
    return false ;
}

bool testSufferingNotLongEnough(Entity entity){
    // Verify that manageSuffering does not disable suffering before 0.5s
    sf::Clock clock ;
    sf::Time time ; 
    entity.setSuffering(true);

    clock.restart();
    while(time.asSeconds() < 0.3f){
        time = clock.getElapsedTime();
        entity.manageSuffering();
    }
     
    if(entity.getSuffering()){
        // Entity should still suffer at this point because 0.5s not over
        return true ;
    }
    
    return false ;

}