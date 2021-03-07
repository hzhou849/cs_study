// Abstract Interface Class Demo

#include <iostream>
#include "I_interface.h"

// Method 2 of printing
void print(const I_interface *inputObj)
{
	std::cout << "Printer_function:"<< *inputObj << std::endl;
}

int main (int argc, char *argv[])
{
	Base_class *p1 = new Base_class();
	std::cout << *p1 << std::endl;

	Base_class *p2 = new Derived1();
	std::cout << *p2 << std::endl;

	Dog *ptr = new Dog();
	std::cout << *ptr << std::endl;

	print(ptr);

	delete p1;
	delete p2; 
	delete ptr;
}