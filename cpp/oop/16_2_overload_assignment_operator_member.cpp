/* 16-2 - Overload Unary/Binary operators as member methods
 * (++, --, - !)
 * 
 * When we create our objects operators don't know what to compare, so we can define 
 * operators to our liking.
 * To overload a unary operators, 
 * 
 * FORMAT:
 * (COPY)
 * prototype - ReturnType Type::operator<Op>();
 * function call  - Number Number::operator-() const;
 *                - Number Number::operator++();    // pre-increment;
 *                - Number Number::operator++(int); // post-increment;
 *                - bool Number::operator!() const;
 * 
 *                Number n1 {100};
 *                number n2 = -n1   //n1.operator-();
 *                n2 = ++n1;        // n1.operator++();
 *                n2 = n1++;        // n1.operator++(int);
 * 
 * Binary operators (+, -, ==,!=, <>, etc..)
 * 
 * ReturnType Type::lhs.operator<op>(const &Type rhs);
 * 
 * ie.fucntion call -  Number Number::operator+(const &Number rhs) const;
 * Number n1 {100}, n2 {200};
 * Number n3 = n1 + n2      //n1.operator+(n2);
 * 
 */

#include <iostream>
#include <cstring>

//Ol_string.hpp
#ifndef _OL_STRING_H_
#define _OL_STRING_H_

class Ol_string {
private:
    char *str;  //pointer to char[] that holds c-style string
public:
    // Constructors
    Ol_string();                    // No args cosntructor
    Ol_string(const char* str);     // Overloaded constructor
    Ol_string(const Ol_string &source);  //Copy constructor
    Ol_string(Ol_string &&source);       // Move constructor
    ~Ol_string();                        //Destructor


    // Member functions   prototypes

    // Overloaded operator prototype

    //returning a reference to a 'Ol_string' object
    // overloading the '=' assignment operator to our deep copy version
    Ol_string &operator=(const Ol_string &rhs);      
    Ol_string &operator=(Ol_string &&rhs);      //Move constructor
    void display() const;
    int get_length() const;
    const char *get_str() const;
};
#endif // _OL_STRING_H

/* Ol_string.cpp */
// No args
Ol_string::Ol_string()
    :str{nullptr} {
    str = new char[1];      //allocate memory space in heap
    *str = '\0';
}

// overloaded constructor
Ol_string::Ol_string(const char *s)
    :str{nullptr} {
        if (s == nullptr) {
            str = new char[1];
            *str='\0';
        }else {
            str = new char[std::strlen(s)+1];
            std::strcpy(str,s);
        }
}


// Copy constructor 
Ol_string::Ol_string(const Ol_string &source)
    :str{nullptr} {
        str = new char[std::strlen(source.str) +1]; // strlen doesn't count null terminator, must add one for null terminator
        std::strcpy(str, source.str);
}

// Move Constructor
Ol_string::Ol_string(Ol_string &&source) 
    :str{source.str} {      // assign the source.str (previous) to str (destination)
        source.str = nullptr;   // null out the previous
        std::cout<< "Move constructor called." << std::endl;
    }


/* Operator = COPY assignement */
// L-value copying the variable
// return type is reference Ol_string
Ol_string& Ol_string::operator=(const Ol_string &rhs ) {
    std::cout << "copy= operator overload called" << std::endl;

    if (this == &rhs)
        return *this; // dereference the pointer bc we are not returning a pointer back

    // de-allocate 'this' 
    delete [] str; // this->str
    str = new char[std::strlen(rhs.str)+1];
    std::strcpy(this->str, rhs.str);
    return *this;
}

/*Operator = MOVE assignement */
// this is R-Value copying the data contents
Ol_string& Ol_string::operator=(Ol_string &&rhs) {
    std::cout << "Using move assignement" << std::endl;

    if (this == &rhs)    // input validation
        return *this;
    
    // Dealloc the LHS (destination) existing data first
    delete [] this->str;
    
    // steal the pointer
    this->str = rhs.str;

    // Null out the rhs ( we don't want to delete the data in the heap, we just want the pointer)
    //IMPORTANT: we have to nullptr rhs.str otherwise at end of scope, destructor will destroy the data
    //          at &rhs.str so if we point it to null, the destructor can't find our data.
    rhs.str = nullptr;  //since this->str is now pointing to what  rhs.str is pointing to, we can now nullptr rhs.ptr

    //return the left side object current object by reference to allow for chain.
    return *this;

}


// Destructor
Ol_string::~Ol_string() {
    std::cout << "destructor called" << std::endl;
    delete [] str;      // '[]' must be used for array memory 
}

//Display method
void Ol_string::display() const {
    std::cout << str << ": " << get_length() << std::endl;
}

//length getter
int Ol_string::get_length() const {
    return std::strlen(str);
}

// string getter;
// 1st const is return typ, 2nd makes the function const
const char *Ol_string::get_str() const {
    return str;
}


// Main.cpp
//#include "Ol_string.h"
int main() {
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

