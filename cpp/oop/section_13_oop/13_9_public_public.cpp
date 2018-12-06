#include <iostream>
#include <string>

class Player {
private:
    //attributes
    int health;
    int xp;
    std::string name;

public:
    //methods
    void talk(std::string text_to_say) {
        std::cout << name << "says" << text_to_say << std::endl;
    }

    void set_name(std::string player_name) {
        name =player_name;
    }

    void get_name(){
        std::cout << "Name: " << name << std::endl;
    }
    bool is_dead();

};

int main() {
    Player frank;
    frank.set_name("Franks");
    frank.get_name();
    return 0;
}
