// Test Abstract Pure Virtual function
// Abstract classes are used purely to be overriden


#include <iostream>
#include <vector>

#include "Abstract_class.h"

// Example Function of what we can do with this powerfull methodology
void screen_refresh(const std::vector<Abstract_class*> *input_vector)
{
	std::cout << "Refreshing" << std::endl;
	for (const auto temp: *input_vector)
	{
		temp->pure_feature2();
	}
}

int main(int argc, char* argv[])
{
	int a = 65;
	int *ptr = &a;

	Abstract_class *objPtr = new Concrete_class();
	// objPtr->pure_feature1();
	// objPtr->pure_feature2();

	Abstract_class *objPtr2 = new Concrete_class2();
	Abstract_class *objPtr3 = new Concrete_class3();



	//Store the Abstract Class Pointers into a vector
	//
	std::vector<Abstract_class*> vector_concrete_class{objPtr, objPtr2, objPtr3};
	for (const auto p : vector_concrete_class)
	{
		p->pure_feature1(); // dynamic bound will know which override to use
	}

	screen_refresh(&vector_concrete_class);



	//  Notice - the full deconstruction in this order will occur.
	// Concrete class destructed!
	// Abstract Derived Class A destructed! 
	// BASE Abstract class destructed!
	delete objPtr; 
	delete objPtr2; 
	delete objPtr3; 
}

