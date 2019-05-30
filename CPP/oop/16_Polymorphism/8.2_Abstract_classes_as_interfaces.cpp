/* 191 - Abstract classes as interfaces - solution implementing interfaces
 *
 *
 *
 * Interfaces full example  - here is the problem, with pointers declared, it will not execute properly
 * */

#include <iostream>


/* Will NOT work */

// class Account {
// 	friend std::ostream &operator<<(std::ostream &os, const Account &acc);
// public:
// 	virtual void withdraw(double amount){
// 		std::cout<<"In Account::withdraw"<<std::endl;
// 	}
// 	virtual ~Account(){}
// };
// std::ostream &operator<<(std::ostream &os, const Account &acc) {
// 	os<<"Account display";
// 	return os;
// }
// class Checking: public Account {
// 	friend std::ostream &operator<<(std::ostream &os, const Checking &acc);
// public:
// 	virtual void withdraw(double amount) {
// 		std::cout << "In checking::withdraw"<<std::endl;
// 	}
// 	virtual ~Checking() {}
// };
// std::ostream &operator<<(std::ostream &os, const Checking &acc) {
// 	os << "Checking Display";
// 	return os;
// }
// class Savings: public Account {
// 	friend std::ostream &operator<<(std::ostream &os, const Savings &acc);
// public:
// 	virtual void withdraw (double amount) {
// 		std::cout << "In Savings::withdraw" << std::endl;
// 	}

// 	virtual ~Savings() {}
// };
// std::ostream &operator<<(std::ostream &os, const Savings &acc){
// 	os << "Savings Display";
// 	return os;
// }
// class Trust: public Account {
// 	friend std::ostream &operator<< (std::ostream &os, const Trust &acc);
// public: 
// 	virtual void withdraw (double amount) {
// 		std::cout <<"In Trust::withdraw" << std::endl;
// 	}
// 	virtual ~Trust() {}
// };
// std::ostream &operator<<(std::ostream &os, const Trust &acc) {
// 	os << "Trust display";
// 	return os;
// }

/* Method 2 - with Interface implementation*/
//Interface - allows shared classes and fucntion that can be dynamically bound
//          - and can be used across hierarchies and just basic functions
//			- allows flexibility and resuability of code.
// 			- create anything that is of I_Display type inherited and you can overload the print() pure virtual function
class I_Display {
	friend std::ostream &operator<<(std::ostream &os, const I_Display &obj);
public:
	virtual void print(std::ostream &os) const =0; // pure virtual function
};
std::ostream &operator<<(std::ostream &os, const I_Display &obj) {
	obj.print(os);
	return os;
}


class Base: public I_Display {		//"inherit the interface"
public:
	virtual void withdraw (double amount) {
		std::cout << "Base::withdraw" << std::endl;
	}
	virtual void print(std::ostream &os) const override {
		os << "Base display";
	}
	virtual ~Base() {}
};

class Derived_A: public Base {
public:
	virtual void withdraw (double amount) {
		std::cout << "Derived_A" << std::endl;
	}
	virtual void print(std::ostream &os) const override {
		os <<"Derived_A display";
	}
	virtual ~Derived_A() {}
};

class Derived_B: public Base{
public:
	virtual void withdraw (double amount) {
		std::cout << "Derived_B" << std::endl;
	}
	virtual void print(std::ostream &os) const override {
		os << "Derived_B display";
	}
	virtual ~Derived_B() {}
};

class Derived_C: public Base {
public:
	virtual void withdraw (double amount) {
		std::cout<<"Derived_C" << std::endl;
	}
	virtual void print(std::ostream &os) const override {
		os << "Derived_C display";
	}
	virtual ~Derived_C() {}
};

class Derived_test: public I_Display {
public:
	virtual void print(std::ostream &os) const override {
		os << "tester display";
	}
};

// we can even write a function and pass I_Display objects
void print(const I_Display &obj) {
	std::cout << obj << std::endl;
}


int main() {
	// we know this will work
	// Account a;
	// std::cout << a<<std::endl;

	// Checking c;
	// std::cout << c << std::endl;

	// Savings s;
	// std::cout << s <<std::endl;

	// Trust t;
	// std::cout << t << std::endl;


	/* the problem is that there printout will only - this will NOT work bc there are no virtual functions to use
	print the "Account display" checking display will not work bc we've got no
	virtual function going on...in Account class is withdraw we don't have no virtual
	function that allows us to work with the context of "<<" operator. - this can be solved 
	in next tutorial file with interfaces.

	Account *p1 = new Account ();
	std::cout << *p1 << std::endl;

	Account *p2 = new Checking ();
	std::cout << *p2 << std::endl;
	*/

	Base *p1 = new Base();
	std::cout << *p1 << std::endl;

	Derived_test *p2 = new Derived_test(); 
	print(*p2);

	return 0;
}





