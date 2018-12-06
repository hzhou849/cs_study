#include <iostream>
#include <string>

/* when compiling make sure you compile all source cpp files in your project */

#include "Account.hpp"
int main() {

    Account frank_account;
    double mybalance {0};
    frank_account.set_balance(1000);
    
    mybalance = frank_account.get_balance();

    std::cout << "Balance: " << mybalance << std::endl;
    
    return 0;
}