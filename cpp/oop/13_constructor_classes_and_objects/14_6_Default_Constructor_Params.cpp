#include <iostream>
#include <string>

/* Traditiaonal method */
// class Obj_Name {
// private:
//     std::string name;
//     int value1;
//     int value2;
// public:
//     //Overloaded constructors
//     Obj_Name();
//     Obj_Name(std::string name_val);
//     Obj_Name(std::string name_val, int v1, int v2);
// };

// Obj_Name::Obj_Name()
//     :Obj_Name{"none", 0,0 } {
//         std::cout << "No args constructor." << std::endl;
// }

// Obj_Name::Obj_Name(std::string name_val)
//     :Obj_Name{name_val, 0,0} {
//         std::cout << "One arg constructor" << std::endl;
// }

// Obj_Name::Obj_Name(std::string name_val, int v1, int v2) 
//     :name{name_val}, value1{v1}, value2{v2} {
//         std::cout << "Three arg constructor"<< std::endl;
// }

/* defaulted version - notice we just have one constructor that does everything now*/
class Obj_Name {
private:
    std::string name;
    int value1;
    int value2;
public:
    Obj_Name(std::string name_val="None", int value1=0, int value2=0);
};

Obj_Name::Obj_Name(std::string name_val, int v1, int v2) 
    :name{name_val}, value1{v1}, value2{v2} {
        std::cout << "Three arg constructor"<< std::endl;
}

int main() {
    Obj_Name a;
    Obj_Name b {"Something"};
    Obj_Name c {"test b",100};

    return 0;
}
