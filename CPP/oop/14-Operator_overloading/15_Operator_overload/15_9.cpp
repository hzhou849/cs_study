/* operator overload */

#include <iostream>
#include <cstring>


//hpp
#ifndef _OL_STRING_H_
#define _OL_STRING_H_

class Ol_string {
private:
    char *str;  //pointer to char[] that holds c-style string
public:
    Ol_string();                    // No args cosntructor
    Ol_string(const char* str);     // Overloaded constructor
    Ol_string(const Ol_string &source);  //Copy constructor
    ~Ol_string();                        //Destructor

    // Method prototypes
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

int main() {
    Ol_string empty;      //no args
    Ol_string buffer1("device name1");
    Ol_string buffer2 {buffer1};

    empty.display();
    buffer1.display();
    buffer2.display();
}

