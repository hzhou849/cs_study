/*17.6 Copy/ Move constructors and Operator= with derived classes
 *
 */

#include <iostream>

class Base {
private:
    int value;
public:
    Base(): value{0} {
        std::cout << "Base no-args constructor" << std::endl;
    }
    Base(int x) 
        :value {x} {
        std::cout << "Base (int) constructor" << std::endl;
    }

    Base (const Base &other) 
        :value {other.value} {
        std::cout << "Base copy constructor" << std::endl;
    }
    
    Base &operator=(const Base &rhs) {
        std::cout << "Base operator=" << std::endl;
        if(this == &rhs)
            return *this;
        value = rhs.value;
        return *this;
    }
    
    ~Base() {
        std::cout << "Base Destructor" << std::endl;
    }
};

class Derived : public Base{
private:
    int doubled_value;
public:
    Derived():
        Base{} {
        std::cout << "Derived no-args constructor " << std::endl;
    }
    Derived(int x)
        :Base{x}, doubled_value{x*2} {
        std::cout << "int Derived constructor" << std::endl;
    }
    Derived(const Derived &other)
        :Base{other}, doubled_value{other.doubled_value} {
        std::cout<<"Derived copy constructor" <<std::endl;
    }
    Derived &operator=(const Derived &rhs) {
        std::cout << "Derived operator=" << std::endl;
        if (this == &rhs) {
            return *this;
        }
        Base::operator=(rhs);
        doubled_value = rhs.doubled_value;
        return *this;

    }

    ~Derived() {
        std::cout << "Derived Destructor called."<<std::endl;
    }
};

int main() {
    Base b {100};
    Base b1{b};  //Copy constructor
    b = b1;     // Copy assignment

    Derived d{100};// overloaded construtor
    Derived d1 {d}; //Copy constructor
    d=d1;           //copy assignemnt
    return 0;

}