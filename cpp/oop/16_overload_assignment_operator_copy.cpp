/* 16-0
 * L-Value detected will use this copy, R-Value will use move assignemnet
 * OVerloading the copy assignment operator =
 * Default is memberwise shallow copy, 
 * overloaded version will do a deep copy onto heap space.
 * 
 * FORMAT:
 * prototype - Type &operator=(const Type &rhs);
 * function call  -Type &Type::operator=(const Type &rhs);
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


//hpp
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
    ~Ol_string();                        //Destructor


    // Member functions   prototypes

    // Overloaded operator prototype
    //returning a reference to a 'Ol_string' object
    // overloading the '=' assignment operator to our deep copy version
    Ol_string &operator=(const Ol_string &rhs);      
    void display() const;
    int get_length() const;
    const char *get_str() const;
};
#endif // _OL_STRING_H

//cpp

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

// return type is reference Ol_string
Ol_string& Ol_string::operator=(const Ol_string &rhs ) {
    std::cout << "= operator overload called" << std::endl;

    if (this == &rhs)
        return *this; // dereference the pointer bc we are not returning a pointer back

    // de-allocate 'this' 
    delete [] str; // this->str
    str = new char[std::strlen(rhs.str)+1];
    std::strcpy(this->str, rhs.str);
    return *this;
}

// Destructor
Ol_string::~Ol_string() {
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
    // Ol_string empty;      //no args
    // Ol_string buffer1("device name1");
    // Ol_string buffer2 {buffer1};

    // empty.display();
    // buffer1.display();
    // buffer2.display();


    Ol_string a {"data blah balh"};     // Ol constructor
    Ol_string b;                        //no-args constructor
    b = a;                              // copy assignemnt b.operator=(a)
    b = "this is a test";               //b.operator=("this is a test")
}

