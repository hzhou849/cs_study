
#include "I_interface.h"

// I_interface class
I_interface::~I_interface()
{
	std::cout << "I_interface destructed!!" << std::endl;
}

// Definition for this overload operator must be in the cpp file
std::ostream &operator<< (std::ostream &os, const I_interface &inputObj)
{
	inputObj.print(os);
	return os;
}



// Base_class
Base_class::Base_class() {}
Base_class::~Base_class()
{
	std::cout << "Base Class Destructed!!" << std::endl;
}

void Base_class::withdraw (double amount)
{
	std::cout << "Base_class::withdraw called" << std::endl;
}

void Base_class::print(std::ostream &os) const
{
	os << "BaseClass::print()" << std::endl;
}


// Derived1 Class
Derived1::Derived1() {}
Derived1::~Derived1() 
{
	std::cout << "Derived1 Destructed!!" << std::endl;
}

void Derived1::withdraw (double amount)
{
	std::cout << "Derived1::withdraw called" << std::endl;
}

void Derived1::print(std::ostream &os) const
{
	os << "Derived1::print()" << std::endl;
}


// Derived2 Class
Derived2::Derived2() {}
Derived2::~Derived2() 
{
	std::cout << "Derived2 Destructed!!" << std::endl;
}

void Derived2::withdraw (double amount)
{
	std::cout << "Derived2::withdraw called" << std::endl;
}

void Derived2::print(std::ostream &os) const
{
	os << "Derived2::print()" << std::endl;
}


// Derived3 Class
Derived3::Derived3() {}
Derived3::~Derived3()
{
	std::cout << "Derived3 Destructed!!" << std::endl;
}

void Derived3::withdraw (double amount)
{
	std::cout << "Derived3::withdraw called" << std::endl;
}

void Derived3::print(std::ostream &os) const
{
	os << "Derived3::print()" << std::endl;
}


// Random Dog class
Dog::Dog() {}
Dog::~Dog()
{
	std::cout << "DogClass - Deconstructed!" << std::endl;
}
void Dog::print(std::ostream &os) const
{
	os << "Woof Woof!" << std::endl;
}