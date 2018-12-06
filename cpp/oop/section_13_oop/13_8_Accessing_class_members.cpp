#include <iostream>
#include <string>
#include <vector>

class Player {
public:
    //attributes
    std::string name;
    int health; 
    int xp;
   
    // methods
    void talk(std::string text_to_say){
        std::cout << name <<" says " << text_to_say << std::endl;
    }
    bool is_dead();
};

class Account {
public:
    // attributes
    std::string name ;
    double balance;

    //methods
    void deposit(double bal){
        balance += bal;
        std::cout<< "In deposit"<<std::endl;
    }
    void withdraw(double bal) {
        balance -= bal;
        std::cout << "In withdraw" << std::endl;
    }

    void show_balance() {
        std::cout << "Balance: " << balance << std:: endl;
    }
};

int main() {

    Account frank_account;
    frank_account.name = "Frank' Account";
    frank_account.balance = 5000.00;

    frank_account.deposit(100);
    frank_account.show_balance();
    frank_account.withdraw(300);
    frank_account.show_balance();
    
    // stack memomry 
    Player frank;
    Player hero;

    frank.name = "Frank";
    frank.health = 100;
    frank.xp = 12;
    frank.talk ("Hi there!");

    Player players[] {frank, hero};
    std::vector<Player> player_vec{frank};
    player_vec.push_back(hero);

    // created on the heap
    Player *enemy {nullptr};
    enemy = new Player;

    // free memory on heap
    delete enemy;


    return 0;
}