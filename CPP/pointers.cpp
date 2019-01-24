#include <iostream>
#include <string>
#include <vector>

// class Player {
//     //attributes
//     char *name;
//     int health;
//     int xp;
//     // methods
// };

int main() {
   int a {999};
   int *num;

   num = &a;
    // num = nullptr;

    std::cout << "value of a: " << a<< std:: endl;
    std::cout << "add of a: " << &a<< std:: endl;
    std::cout << "value of num: " << *num << std:: endl;
    std::cout << "sizeof num: " << sizeof(num) << std::endl;
    std::cout << "Address : " << &num << std::endl;
}