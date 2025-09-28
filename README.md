# DevRanger
A RPG where you progress by coding

The goal is to unlock access to the whole map by helping the goodies and defeating the baddies... with code(C,C++)


This is the command to compile and generate the executable game file : 

~~~~Linux~~~~
g++ -o DevRanger src/main.cpp src/Game.cpp src/States/GameState.cpp src/States/Menu.cpp src/Entities/Entity.cpp src/Entities/Player.cpp src/Entities/Monster.cpp src/Map/GameWorld.cpp src/Map/GameTile.cpp  src/States/State.cpp  -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

VSCode Build shortcuts: 
Build and start debugging: Press 'F5'
Build in release mode: Press 'CTRL+b' (to customize)

Compiler : g++.exe (MinGW-W64 x86_64-msvcrt-posix-seh, built by Brecht Sanders) 13.1.0
 
Credits : 
    SFML tutorial about game states : https://www.youtube.com/watch?v=WFJW9M852Ko (author : Suraj Sharma)
    SFML tutorial about maps : https://www.youtube.com/watch?v=_RLFI1D99Ow (author : Zenva)
    Sprites of the hero (opengameart.org) (author : Fry) (link : https://opengameart.org/users/fry)  
    Sprites of the menu arrow (opengameart.org) (author : INFECTiON656) (link : https://opengameart.org/users/infection656)     
    Sprites of menu background, walls (opengameart.org) (author : Ivan Voirol) (link : https://opengameart.org/users/ivan-voirol)
    Sprites for hero's fireball : Game Developer Studio (www.gamedeveloperstudio.com) (author : Robert Brooks)
