#include <iostream>
#include <string>

// create own default no args constructor
// used to initialize default values to avoid wildcards

class ObjectName {
private: 
    std::string name;
    int value1;
    int value2;

public:
    void set_name(std::string n) {
        name = n;
    }

    void set_value1 (int v) {
        value1 = v;
    }

    //default constructor
    ObjectName(){
        name = "";
        value1=0;
        value2=0;
    }
    //constructor overloads can be added here.

}