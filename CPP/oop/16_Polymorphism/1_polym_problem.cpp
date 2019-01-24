/* 18.3 - Polymorphism
 *
 * class bindings happen either
 * Polymorphism 2 types: - Compile-time 
 *                          i) Function overloading
 *                          ii) Operator overloading
 *                       - Runtime
 *                          deferr binding to run-time.
 *                          i) function overriding
 *  
 * the problem, passing the class objects to display function there is no way to distinguish
 * which object type whether it is derrived or base class or whatever is declared in function signature parameters
 * (statically bound)
 * 
 * for dynamic polymorphism, we must have:
 * - inheritance
 * -Base class pointer or base class reference
 * - virtual functions
 * 
*/

#include <iostream>
class Base {
public:
    void test_func() const {
        std::cout<<"Base Class" << std:: endl;
    }
};

class Derived: public Base {
public:
    void test_func() const {
        std::cout <<"Derived class" << std::endl;
    }
};

void display(const Base &obj) {     // because not dynamic polym, compiler only knows &obj is bound to Base type.
    std::cout<<"object class passed: " << std::endl;
    obj.test_func();
};

int main() {

    Base b;
    b.test_func();
    Derived d;
    d.test_func();

   display(b);
   display(d);

    // ptr can hold the address of any Base type address or inherited class types
   Base *ptr = new Derived(); // allocate new Derived object on heap memory

   ptr->test_func();        // problem is ptr is declared as type Base, therefore compiler will statically bound to Base.test_func();

    return 0;
}


 
