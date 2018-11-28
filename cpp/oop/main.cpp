#include <iostream>
#include <string>
#include <vector>

class Player {
    //attributes
    std::string name;
    int health;
    int xp;
   
    // methods
    void talk(std::string);
    bool is_dead();
};

int main() {

    // stack memomry 
    Player frank;
    Player hero;


    Player players[] {frank, hero};

    // created on the heap
    Player *enemy {nullptr};
    enemy = new Player;


    delete enemy;


    return 0;
}