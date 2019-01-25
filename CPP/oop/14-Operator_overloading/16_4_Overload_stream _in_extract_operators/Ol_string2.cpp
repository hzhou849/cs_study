/* the point of overloading the stream operators is 
 * so you can printout the object and define what string you want it to printout.
 * ie. std::cout << object1 << std::endl;
 * 
 * you can define it so it prints out object1.name or object1.date etc...
 * 
 * First you need to fix the operator by adding Currency const& c as the second parameter (as it come s on the right hand side).

Then you have two options:

1: Add Friend
struct Currency
{
  int Dollar;
  int Cents;

  friend ostream& operator<< (ostream &out, Currency const& c)
  {
    return out << "(" << c.Dollar << ", " << c.Cents << ")";
  }
};

2: Move the definition outside the class
struct Currency
{
  int Dollar;
  int Cents;
};

ostream& operator<< (ostream &out, Currency const& c)
{
  return out << "(" << C.Dollar << ", " << c.Cents << ")";
}
 * 
 * 
 */

#include <iostream>
#include <cstring>
#include "Ol_string.hpp"


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
    delete [] str;
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

// Equality
bool operator==(const Ol_string &lhs, const Ol_string &rhs) {
    return (std::strcmp(lhs.str, rhs.str) == 0);    //strcmp return 0 if ==, if 0==0 returns 1 true.
}

//Make lowercase
Ol_string operator-(const Ol_string &obj)  {
    char *buff = new char[std::strlen(obj.str) +1];
    std::strcpy(buff, obj.str);
    for (size_t i=0; i < std::strlen(buff); i++){
        buff[i] = std::tolower(buff[i]);
    }
    Ol_string temp {buff};
    delete [] buff;
    return temp;
}

// concat
Ol_string operator+(const Ol_string &lhs, const Ol_string &rhs) {
    char *buff = new char[std::strlen(lhs.str)+ std::strlen(rhs.str) +1]; // allocate memory in heap for total size of string +1 for null terminator
    std::strcpy(buff, lhs.str);
    std::strcat(buff, rhs.str);
    Ol_string temp {buff};
    delete [] buff;
    return temp;
    
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

// Overloaded insertion operator
std::ostream &operator<<(std::ostream &os, const Ol_string &rhs) {
    os << rhs.str;	//feed the object_passed.str to the stream
    return os;
}


// Overload the extraction operator
std::istream &operator >> (std::istream &in, Ol_string &rhs) {
    // Allocate memory on heap
    char *buff = new char [1000];
    in >> buff; // get the contents of input stream and store in buffer
    rhs = Ol_string{buff}; // depending if you have copy or move assignemnt, it will prefer move
    delete [] buff;
    return in;
}