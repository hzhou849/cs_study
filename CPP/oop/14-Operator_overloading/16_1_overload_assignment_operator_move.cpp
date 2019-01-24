/* 16-1
 * Move assignemnt operator
 * L-Value detected will use this copy, R-Value will use move assignemnet
 * 
 * ALso you will need to implement a move constructor
 * This will use Move instead of copy which can be expensive
 *  the move assignement will destroy the older one in the process as data is moved from
 * one variable to the next
 * FORMAT:
 * (COPY)
 * prototype - Type &operator=(const Type &rhs);
 * function call  -Type &Type::operator=(const Type &rhs);
 * 
 * (MOVE) - since this is R-value reference this is denoted with '&&'
 * NOTE: not const, bc we need to modify this object (null the ptr) when we move the data.
 * prototype - Type &operator=(Type &&rhs);
 * function call - Type &Type::operator=(Type &&rhs);
 * 
 * ex:
 * read return type is a reference to a Ol_string object
 * This prevents extra copies and allows chain assignemnts ie s1=s2=s3
 * Ol_string &Ol_string::operator=(const Ol_string &rhs); 
 * 
 * 
 * 
 * s2 = s1;             // write this
 * s2.operator=(s1);    // operator method is called.
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

// Destructor
Ol_string::~Ol_string() {
    std::cout << "destructor called" << std::endl;
    delete [] str;      // '[]' must be used for array memory 
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
    // Ol_string empty;      //no args
    // Ol_string buffer1("device name1");
    // Ol_string buffer2 {buffer1};

    // empty.display();
    // buffer1.display();
    // buffer2.display();

    

    // Ol_string a {"data blah balh"};     // Ol constructor
    // Ol_string b;                        //no-args constructor
    // b = a;                              // copy assignemnt b.operator=(a)
    // b = "this is a test";               //b.operator=("this is a test")

    Ol_string a {"FFFFF"};          // Constructor initialization
    // Ol_string b {"blah"};
    a = Ol_string{"new data"};       // construct temp object with "new data" then move assign to a
    a = "r-value data";                  // "r-value data" is an r-value, so move will be detected and called.

    // b = a;                      // a is an L-value so copy will be called          
}

