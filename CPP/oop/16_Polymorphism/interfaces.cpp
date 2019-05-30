/* C++ interfaces example
 *
 * since C++ doesn't have keyword Interfaces are 
 * implemented thought an Abstract base class
 * Abstract (pure virtual classes) cannot be used to instantiate 
 * an object of an abstract class.
 * 
 * classes that are used to instantiate objects are called concrete classes
 * 
 */

#include <iostream>

// Interface class
class I_BaseShape {
protected:
	int width;
	int height;
public: 				// pure virtual function providing interface framework
	virtual int getArea() = 0;		// this is a pure virtual function
	virtual void displayType() =0; // pure virtual function
	void setWidth (int w) { width = w;}
	void setHeight(int h) {height = h;}

};

// doesn't have to be a base class, but anything derived from a 
class Base: public I_BaseShape { // inherits from the interface
public:
	virtual int getArea() override {
		return (width * height );
	}

	virtual void displayType () override{
		std::cout << "Base class" << std::endl;
	}

};

class Derived : public Base {
public:
	virtual int getArea() override {
		return (width * height /2);
	}
	virtual void displayType() override {
		std::cout << "Dervived class"<< std::endl;
	}
};



int main () {
	Base b;
	Derived d;

	b.setHeight(8);
	b.setWidth(4);

	d.setHeight(17);
	d.setWidth(3);

	std::cout << b.getArea() << std::endl;
	std::cout << d.getArea() << std::endl;
	b.displayType();
	d.displayType();

	Base *p1 = new Base();
	Base *p2 = new Derived();

	p1->displayType();
	p2->displayType();
}