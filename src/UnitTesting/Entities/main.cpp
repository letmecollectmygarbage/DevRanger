#include "../../Entities/Entity.h"

// compile me with : 
// g++ -o src/UnitTesting/Entities/EntityUnitTest src/UnitTesting/Entities/main.cpp src/Entities/Entity.cpp -IC:\SFML\include\ -LC:\SFML\lib\ -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window
// execute me with : 
// .\src\UnitTesting\Entities\EntityUnitTest.exe

bool testSufferingLongEnough(Entity entity);
bool testSufferingNotLongEnough(Entity entity);
bool isEntitySufferingAfterTime(Entity entity, float time_to_suffer);
void test_output(int test_num, bool actual_result, bool expected_result);


int main(void){
    std::cout << "Hello World ! " << "\n";
    Entity entity = Entity();
    std::cout << "Entity created !\n";
    sf::Sprite entitySprite = entity.getSprite();
    std::cout << "Sprite obtained ! \n" ;
    //static_assert()

    // TESTS I EXCPECT TO RETURN FALSE 
    bool actual_result ;
    actual_result = isEntitySufferingAfterTime(entity,2.f);
    test_output(1,actual_result,false);
    actual_result = isEntitySufferingAfterTime(entity,0.6f);
    test_output(1,actual_result,false);
    actual_result = isEntitySufferingAfterTime(entity,1.f);
    test_output(1,actual_result,false);

    // TESTS I EXPECT TO RETURN TRUE
    actual_result = isEntitySufferingAfterTime(entity,0.4f);
    test_output(2,actual_result,true);
    actual_result = isEntitySufferingAfterTime(entity,0.3f);
    test_output(2,actual_result,true);
    actual_result = isEntitySufferingAfterTime(entity,0.3f);
    test_output(2,actual_result,true);


    return 0 ; 

}

// Verify that manageSuffering manages suffering correctly 
// Entity should suffer for 0.5s not more not
// Returns suffering attribute of entity
// time_to_suffer (seconds)
bool isEntitySufferingAfterTime(Entity entity, float time_to_suffer){
    sf::Clock clock ;
    sf::Time time ; 
    entity.manageSuffering(true); // reset internal clock to do like when Player is attacked twice during the 0.5s delay
    entity.setSuffering(true);
    clock.restart();
    while(time.asSeconds() < time_to_suffer){
        time = clock.getElapsedTime();
        entity.manageSuffering(false);
    }
    return entity.getSuffering() ;    
}

void test_output(int test_num, bool actual_result, bool expected_result){
    if(actual_result == expected_result){
        std::cout <<"TEST #" << test_num << " : SUCCESS :-) \n" ;
    }
    else{
        std::cout <<"TEST #" << test_num << " : FAIL :-( \n" ;
    }
}