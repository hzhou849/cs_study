/* 190 - Pure vitrual functions and abstract classes 
 * Abstract classes
 *	- Cannot instantiate objects
		ie Shape shape; 	// error 
			Shape *ptr = new Shape(); // error
 *	- are used as base classes in inheritance hierarchies
 *  - Often referred to as Abstract Base Classes
 * 
 * Concrete class
 * - Used to instantiate objects from
 * - All their member functions are defined
 * 	ie. Checking Account, Savings account,
 * 		Faculty, staff
 * 		Enemy, Level Boss etc...
 * 
 *  Abstract base class
 * 	- too generic to directly dervive objects from
 *  - serves as parent to Derived classes that may have objects
 * 	- constains at least one pure virtual function
 * 
 *  Pure virtual function
 * 	- what is a virtual function? it is Used to make a class abstract.
 *  - specified '=0' ie virtual void function () = 0; // pure virtual function
 *  - typically do not provide implementation.
 *  - Dervied class MUST override the base class 
 *  - if the derived class does not override then the derived class is also abstract
 *  - used when it doens't make sense for a base class to have an implementation 
 *    but concrete classes must implement it.
 * 
 * we can use pointers and references to dynamically refer to concrete classes dervived from them
 * 
 * shape *ptr = new Circle();
 * ptr->draw();
 * ptr->rotate();
*/
#include <iostream>
#include <vector>

//Shape.hpp
// #ifndef _SHAPE_H_
// #define _SHAPE_H_

class Shape {	//Abstract Base class remember cannot instantiate this as an object.
private:
	// attribute common to all shapes
public:
	virtual void draw() = 0;	// pure virtual function
	virtual void rotate() = 0;	// pure virtual function
	virtual ~Shape() {}
};

// #endif	//_SHAPE_H_

//Open_shape.hpp
// #ifndef _OPEN_SHAPE_H_
// #define _OPEN_SHAPE_H_


class Open_Shape: public Shape { // abstract class
public:
	virtual ~Open_Shape() {}
};

// #endif //_OPEN_SHAPE_H_

//Closed_Shape.hpp
class Closed_Shape: public Shape { // abstract class
public:
	virtual ~Closed_Shape() {};
};


//Line.hpp
class Line: public Open_Shape {		//Concrete class
public:
	virtual void draw() override {
		std::cout << "Drawing a line" << std::endl;
	}

	virtual void rotate() override {
		std::cout << "Rotating a line" << std::endl;
	}

	virtual ~Line() {}
};

//Circle.hpp
class Circle: public Closed_Shape {	// Concrete class
public:
	virtual void draw() override {
		std::cout <<"Drawing a circle" << std::endl;
	}
	virtual void rotate() override {
		std::cout << "Rotating a circle" << std::endl;
	}
	virtual ~Circle() {}
};

//Square.hpp
class Square: public Closed_Shape { // Concrete class
public:
	virtual void draw() override {
		std::cout << "Drawing a square" << std::endl;
	}
	virtual void rotate() override {
		std::cout << "Rotating a square" << std::endl;
	}

	virtual ~Square() {}
	
};

void screen_refresh(const std::vector <Shape*> &shapes)  { // pass by refernce
	std::cout << "Refreshing" << std::endl;
	for (const auto p:shapes)
		p->draw();
}

//main.cpp
int main() {
	// Shape s;					// cannot compile as these are virtual classes
	// Shape *p = new Shape();	// cannot compile as these are virtual classes

	// Circle c;	// ok
	// c.draw();	// ok


	// Shape *ptr = new Circle();
	// ptr->draw();			// circle.draw()
	// ptr->rotate();			// circle.rotate()

	Shape *s1 = new Circle();
	Shape *s2 = new Line();
	Shape *s3 = new Square();

	// type of variable for this vector is a shape pointer
	std::vector <Shape*> shapes{s1, s2, s3};
	// for (const auto p: shapes) { 	// moved to helper function
	// 	p->draw();
	// }

	screen_refresh(shapes);

	// Free memory.
	delete s1;
	delete s2;
	delete s3;

	return 0;
}