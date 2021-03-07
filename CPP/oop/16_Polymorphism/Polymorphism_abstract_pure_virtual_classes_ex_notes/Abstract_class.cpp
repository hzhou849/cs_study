// Abstract_class - Pure virtual functions
// Note; Interface class is a class of pure virtual functions to acheive it.
#include "Abstract_class.h"

// Abstract Base Class
Abstract_class::Abstract_class() {}
Abstract_class::~Abstract_class() 
{
	std::cout << "BASE Abstract class destructed!" << std::endl;
}



// Abstract derived class A
Abstract_derived_A::Abstract_derived_A() {}
Abstract_derived_A::~Abstract_derived_A() 
{
	std::cout << "Abstract Derived Class A destructed! " << std::endl;
}



// Abstract derived Class B
Abstract_derived_B::Abstract_derived_B() {}
Abstract_derived_B::~Abstract_derived_B()
{
	std::cout << "Abstract Derived Class B Destructed! " << std::endl;
}



// Concrete class - Implementation of the pure virutal abstract classes
Concrete_class::Concrete_class() {}
Concrete_class::~Concrete_class()
{
	std::cout << "Concrete class destructed!" << std::endl;
}

void Concrete_class::pure_feature1()
{
	std::cout << "Con1- Pure Virtual Feature-1 Executed " << std::endl;
}

void Concrete_class::pure_feature2()
{
	std::cout << "Con1 - Pure Virtual Feature-2 Executed" << std::endl;
}


// Concrete class2 - Implementation of the pure virutal abstract classes
Concrete_class2::Concrete_class2() {}
Concrete_class2::~Concrete_class2()
{
	std::cout << "Con2 class destructed!" << std::endl;
}

void Concrete_class2::pure_feature1()
{
	std::cout << "Con2- Pure Virtual Feature-1 Executed " << std::endl;
}

void Concrete_class2::pure_feature2()
{
	std::cout << "Con2 - Pure Virtual Feature-2 Executed" << std::endl;
}


// Concrete class3 - Implementation of the pure virutal abstract classes
Concrete_class3::Concrete_class3() {}
Concrete_class3::~Concrete_class3()
{
	std::cout << "Con3 class destructed!" << std::endl;
}

void Concrete_class3::pure_feature1()
{
	std::cout << "Con3- Pure Virtual Feature-1 Executed " << std::endl;
}

void Concrete_class3::pure_feature2()
{
	std::cout << "Con3 - Pure Virtual Feature-2 Executed" << std::endl;
}


