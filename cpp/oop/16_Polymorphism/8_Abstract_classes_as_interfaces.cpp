/* 191 - Abstract classes as interfaces
 *
 * Whas is using a class as an interface?
 * - is a class that only has pure virtual functions. must be declared as public
 * - Each subclass is free to implement these services as needed
 * - Every service (method) must be implemented
 * - The service type information is strictly enforced. function prototypes must match exactly
 * 
 * unlike java or c#, c++ does NOT provide a specific keyword or way to create a 
 * interface as part of the c++ core language. we use Abstract classes with  pure virtual functions
 * to achieve the functionality/concept of an interface.
 * 
 * Why use interface?
 * suppose we want to be able to provide any user defined object the ability to be printed on a stream
 * like cout, we can do this by creating a printable interface class that provides the service in terms
 * of a pure virtual function and then our user defined classes simply can be derived from printable and override 
 * this pure virtual function.
 * 
 * Example:
 * class Printable {			// pure virtual function
 * 	friend ostream &operator << (ostream &, const Printable &obj);
 * public:
 * 	virtual void print(ostream &os) const = 0;
 * 	virutal ~printable() {};
 * };
 * 
 * ostream &operator << (ostream &os, const Printable &obj) {
 * 	obj.print(os);
 * 	return os;
 * }
 * 
 * so..for anyclass to be "printable" it must be: 
 * 1) derived from printable 
 * 2)it must override the pure virtual function print that is in the printable interface
 * 
 * class Any_Class : public Printable {
 * public :
 *	// Must override Printable::print()
	virtual void print(ostream *os) override {		// bound dynamically
		os << "Hi from Any_class";
	}
 * };
 * 
 * // Example 1
 * Any_class *ptr = new Any_class ();
 * std::cout << *ptr << std::endl;
 * 
 * void function1 (Any_class &obj) {
 * 	std::cout << *ptr << std::endl;
 * }
 * 
 * void function2 (Printable &obj) {
 * 	std::cout << obj << std::endl;
 * }
 * 
 * function1(*ptr);		// "Hi from Any_class"
 * function2(*ptr);		// "Hi from Any_class"
 */

// //Example 2
// // what this means is if you want to be a concrete class, you must derive Shape and
// // override the the draw and pure virtual functions.
// class Shape {		// Abstract class that can be used as an interface class
// public:
// 	// only contains pure virtual functions
// 	virtual void draw() = 0;
// 	virtual void rotate() = 0;
// 	virtual ~Shape() {};
// };

// class Circle: public Shape {
// public:
// 	virtual void draw() override { /*code */};
// 	virtual void rotate() override {/*code */};
// 	virtual ~Circle() {};
// };

// // Example. naming convention for interface classes.
// class I_Shape {
// public:
// 	virtual void draw() = 0;
// 	virtual void rotate() =0;
// 	virtual ~I_Shape() {};
// };

// class Circle: public I_Shape {
// public:
// 	virtual void draw() override {/*code */};
// 	virtual void rotate() override {/*code */};
// 	virtual ~Circle() {};
// };

// // We can now use pointers to shape objects
// vector <I_Shape *> shapes;

// I_shape *p1 = new Circle();
// I_Shape *p2 = new Line();
// I_Shape *p3 = new Square();

// for (auto const &shape: shapes) {
// 	shape->rotate();
// 	shape->draw();
// }

// // delete pointers


/*Interfaces full example  - here is the problem, with pointers declared, it will not execute properly*/

#include <iostream>

class Account {
	friend std::ostream &operator<<(std::ostream &os, const Account &acc);
public:
	virtual void withdraw(double amount){
		std::cout<<"In Account::withdraw"<<std::endl;
	}

	virtual ~Account(){}
};

std::ostream &operator<<(std::ostream &os, const Account &acc) {
	os<<"Account display";
	return os;
}


class Checking: public Account {
	friend std::ostream &operator<<(std::ostream &os, const Checking &acc);
public:
	virtual void withdraw(double amount) {
		std::cout << "In checking::withdraw"<<std::endl;
	}
	virtual ~Checking() {}
};

std::ostream &operator<<(std::ostream &os, const Checking &acc) {
	os << "Checking Display";
	return os;
}



class Savings: public Account {
	friend std::ostream &operator<<(std::ostream &os, const Savings &acc);
public:
	virtual void withdraw (double amount) {
		std::cout << "In Savings::withdraw" << std::endl;
	}

	virtual ~Savings() {}
};

std::ostream &operator<<(std::ostream &os, const Savings &acc){
	os << "Savings Display";
	return os;
}


class Trust: public Account {
	friend std::ostream &operator<< (std::ostream &os, const Trust &acc);
public: 
	virtual void withdraw (double amount) {
		std::cout <<"In Trust::withdraw" << std::endl;
	}
	virtual ~Trust() {}
};

std::ostream &operator<<(std::ostream &os, const Trust &acc) {
	os << "Trust display";
	return os;
}

int main() {
	// Account a;
	// std::cout << a<<std::endl;

	// Checking c;
	// std::cout << c << std::endl;

	// Savings s;
	// std::cout << s <<std::endl;

	// Trust t;
	// std::cout << t << std::endl;


	/* the problem is that there printout will only
	print the "Account display" checking display will not work bc we've got no
	virtual function going on...in Account class is withdraw we don't have no virtual
	function that allows us to work with the context of "<<" operator. - this can be solved 
	in next tutorial file with interfaces.

	Account *p1 = new Account ();
	std::cout << *p1 << std::endl;

	Account *p2 = new Checking ();
	std::cout << *p2 << std::endl;

	return 0;
}





