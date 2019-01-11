#include <iostream>
#include <cstring>
#include "Ol_string.hpp"

int main() {
    std::cout << std::boolalpha << std::endl; /* prints true false instead of 1, 0 for booleans */

//    Ol_string dev_a {"Device A"};
//    Ol_string dev_b {"Device B"};

//    Ol_string dev_c = dev_a;

//    dev_a.display();
//    dev_b.display();

//    std::cout <<(dev_a == dev_b) << std::endl;       // false;
//    std::cout << (dev_a == dev_c) << std::endl;      // True;

//    dev_a.display();     // "Device A"
//    Ol_string dev_a_l = -dev_a;      // "device a"
//    dev_a_l.display();               

//    Ol_string dev


// test cases
    Ol_string dev_a{"Alpha"};
    Ol_string dev_b{"Bravo"};

    Ol_string dev_c = dev_a;
    dev_a.display();                // Alpha
    dev_b.display();                //Bravo

    std::cout << (dev_a == dev_b) << std::endl;     // false
    std::cout << (dev_a == dev_c) << std::endl;     // true

    dev_a.display();             // Alpha
    Ol_string dev_a2 = -dev_a;
    dev_a2.display();

    Ol_string dev_ab = dev_a + "blaha";         // ok with member function
    //Ol_string dev_ab = "dev_a" + dev_b;       // compiler error must be L-value on lhs

    Ol_string two_devices = dev_b + "" + "blaha";
    two_devices.display();

    return 0;



}
