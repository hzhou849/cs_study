/*  Section 15
 *   17-4 Constructors destructor inheritance
 *
 *  NOTE: Derived class only inherit base constructors, NOT base overloads
 *          unless explictly called by "using Base::Base" 
 *          HOWEVER this wil not take care initializing the derived class values
 */

#include <iostream>

class Base{
private:
    int value;
public:
    Base():
        value{0} {
        std::cout << "Base no-args constructor" <<std::endl;
    }

    Base(int x): value{x} {
        std::cout << "Base(int) overloaded constructor" << std::endl;
    }

    ~Base() {
        std::cout << "Base Destructor "<<std::endl;
    }
};

class Derived: public Base{
    using Base::Base; // to inherit the Base overload, but this will not take care of initializing the derived class values.
private:
    int doubled_value;
public:
    Derived() :doubled_value{0} {
        std::cout<<"Derived no-args constructor" << std::endl; 
    }

    Derived(int x) : doubled_value {x*2} {
        std::cout << "Derived (int) overloaded constructor" << std::endl;
    }

    ~Derived() {
        std::cout << "Derived deconstructor" <<std::endl;
    }
};

int main() {
    Base b;
    Base b{100};

    return 0;
}