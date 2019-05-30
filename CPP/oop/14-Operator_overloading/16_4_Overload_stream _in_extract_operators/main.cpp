/* 16-4 Overloading the stream insertion and Extraction operators
 *
 * since overloading operators as member functions, 
 * the left operand must be a user-defined class
 * ie object << cout; // does not make sense, s
 * so it will have to be implemented as a non-member function
 * 
 * return ostream as reference do not return by value!
 */


#include <iostream>
#include "Ol_string.hpp"

int main() {
    Ol_string dev_a {"Device_1"};
    Ol_string dev_b {"Device_2"};
    Ol_string dev_c;

    std::cout << "Enter the name of device 3"<< std::endl;;
    std::cin >> dev_c;

    std::cout << "Devices detected: " << dev_a << dev_b << dev_c << std::endl;

    return 0;
}