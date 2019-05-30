#include <iostream>

class Player {
private:
    std::string name;
    int health;
    int xp;
public:
    void set_name(std::string name_val) {
        name = name_val;
    }
    //Overloaded constructors
    Player() {
        std::cout << "No args constructor called" << std::endl;
    }
    Player(std::string name) {
        std::cout << "string arg constructor called" << std::endl;
    }
    Player(std::string name, int health, int xp) {
        std::cout << "Three args constructor called" << std::endl;
    } 

    // Deconstructor - called automatically when scope ends,
    // manually called for heap allocated stuff.
    ~Player() {
        std::cout << "Deconstructor called for " << name << std::endl;
    }
};


int main() {
    
    { //manually create code blocks scopes to execute 
        Player p1;
        p1.set_name("first");
    }

    {
        Player p2;
        p2.set_name("second");
        
        Player p3("Third");
        p3.set_name("Third");
        
        Player p4("fourth", 100, 12);
        p4.set_name("fouth");
    }

    // using pointers to allocate in heap memory space
    Player *enemy = new Player;
    enemy->set_name("Enemy");

    Player *lboss = new Player("lb", 1000,300);
    lboss->set_name("levelBoss");

    // deallocate and manually call the deconstructor on heap allocated objects.
    delete enemy;
    delete lboss;

    return 0;
}

