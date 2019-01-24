#include <iostream>
// #include "Ol_string.h"


/* Ol_string.h */
#ifndef _OL_STRING_H_
#define _OL_STRING_H_

class Ol_string {
	//if not using friend, using get str method 
	friend std::ostream &operator<<(std::ostream &os, const Ol_string &rhs); //
	friend std::istream &operator>>(std::istream &in, Ol_string &rhs);
private:
	char *str;		//pointer to char[] that holds a c-style string
public:
	Ol_string();					// No args constructor
	Ol_string(const char *s);		// Overloaded constructor
	Ol_string (const Ol_string &source); //copy constructor
	Ol_string (Ol_string &&source);		// Move constructor
	~Ol_string();							// Destructor

	Ol_string &operator=(const Ol_string &rhs); // Copy assignment
	Ol_string &operator= (Ol_string &&rhs);		// Move assignment

	void display() const;

	// getters
	int get_length() const;
	const char *get_str() const;
};

#endif //_OL_STRING_H_


/* Ol_string.cpp  - source file*/ 
// #include <iostream>
#include <cstring>
// #include "Ol_string.hpp"

// Constructos
Ol_string::Ol_string()
	:str{nullptr} {
	str = new char[1];
	*str = '\0';
}

Ol_string::Ol_string(const char *s)
	:str{nullptr} {
	if (s == nullptr) {
		str = new char[1];
		*str = '\0';
	} else {
		str = new char [strlen(s) +1];
		strcpy(str, s);
	}
}

//Copy constructor
Ol_string::Ol_string(const Ol_string &source) 
	:str{nullptr} {
	str = new char[strlen(source.str)+1];
	strcpy(str, source.str);
	std::cout << "Copy constructor called." << std::endl;
}

// Move constructor
Ol_string::Ol_string(Ol_string &&source)
	:str(source.str) {
	source.str = nullptr;
	std::cout << "Move constructor used" << std::endl;	
}

// Destructor
Ol_string::~Ol_string() {
	delete [] str; // free heap allocated memory 'str'
}

//Copy Assignment
Ol_string &Ol_string::operator=(const Ol_string &rhs) {
	std::cout << "Using copy assignemnt" << std::endl;

	if (this == &rhs)
		return *this;
	delete [] str;
	str = new char [strlen(rhs.str) +1];
	strcpy(str, rhs.str);
	return *this;
}

// Move Assignment
Ol_string &Ol_string::operator=(Ol_string &&rhs) {
	std::cout << "Using move assignment" << std::endl;
	if (this == &rhs)
		return *this;
	delete [] str;
	str = rhs.str;  // store the address in str pointer
	rhs.str = nullptr; // delete the reference.
	return *this;
}

// Display Method
void Ol_string::display() const { // this is a const method.
	std::cout << str << ":" << get_length() << std::endl;
}

//getters
int Ol_string::get_length() const { return strlen(str); }
const char *Ol_string::get_str() const {return str;}

// overloaded insertion operator
std::ostream &operator<<(std::ostream &os, const Ol_string &rhs) {
	os << rhs.str;
	return os;
}

// overload the extraction operator
std::istream &operator>>(std::istream &in, Ol_string &rhs) {
	// create a buffer to temp store the input
	char *buff = new char[1000]; // allocate memory in heap
	in >> buff;

	rhs = Ol_string{buff}; // using move assignment, efficient 
	delete [] buff;
	return in;
}


/*main.cpp */
int main() {
	// we are overloading the iostream bc std::cout/cin does not know how to process a custom object class we created.
	Ol_string name1 {"Name1"};
	Ol_string name2 {"Name2"};
	Ol_string name3;

	std::cout << "Enter the third name: ";
	std::cin >> name3;

	std::cout << "The three names are" << name1 << ", "<<name2 <<"and " << name3 << std::endl;
	
	std::cout << "\nEnter the three names separated by a space:";
	std::cin >> name1 >> name2 >> name3;

	std::cout << "The 3 names entered are" << name1 << ", "<< name2 << ", " << name3 << std::endl;
	return 0;
}