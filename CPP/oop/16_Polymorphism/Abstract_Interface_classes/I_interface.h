// Abstract Interface Class

#ifndef _I_INTERFACE_H_
#define _I_INTERFACE_H_

#include <iostream>

/// Interface Class 
// An abstract class that has only PURE VIRUTAL functions
// These functions provide a general set of services to the user of the class

// a great use of the interface methodology, is we don't need to use friend of std::ostream
// overload the operator anymore
// now we can delete all the friend prototype functions and implementation and just have
// one at the interface class.

// Interface Class
class I_interface
{
private:
	// Note this deinfition of overload must be int he cpp file
	friend std::ostream &operator<< (std::ostream &os, const I_interface &inputObj);

public:
	virtual ~I_interface();
	virtual void print(std::ostream &os) const = 0; // pure virtual function
};


// Base Class
class Base_class : public I_interface // inherit the interface class
{
private:
	// Originally we would have to write this implentation for each derived class
	// This will dramatically clean up the code
	// Not required since we are using interface methodology
	// friend std::ostream &operator<< (std::ostream &os, const Base_class &inputObj);

public:
	Base_class();
	virtual ~Base_class();
	virtual void withdraw (double amount);
	
	// implementation of interface pure virtual function
	virtual void print(std::ostream &os) const override;
};

// Originally we would have to write this implentation for each derived class
// Not required since we are using interface methodology
// std::ostream &operator<< (std::ostream &os, const Base_class &inputObj)
// {
// 	os << "Account Display";
// 	return os;
// }



// Dervived Class 1
class Derived1 : public Base_class
{
private:
	// friend std::ostream &operator<< (std::ostream &os, const Derived1 &inputObj);
public: 
	Derived1();
	virtual ~Derived1();
	virtual void withdraw (double amount) override;
	virtual void print(std::ostream &os) const override;
};
// Not required since we are using interface methodology
// std::ostream &operator<< (std::ostream &os, const Base_class &inputObj)
// {
// 	os << "Account Display";
// 	return os;
// }



// Dervived Class 2
class Derived2 : public Base_class
{
private:
// friend std::ostream &operator<< (std::ostream &os, const Derived2 &inputObj);
public:
	Derived2();
	virtual ~Derived2();
	virtual void withdraw (double amount) override;
	virtual void print(std::ostream &os) const override;
};
// Not required since we are using interface methodology
// std::ostream &operator<< (std::ostream &os, const Base_class &inputObj)
// {
// 	os << "Account Display";
// 	return os;
// }


// Dervived Class 3
class Derived3: public Base_class
{
// private:
// friend std::ostream &operator<< (std::ostream &os, const Derived3 &inputObj);
public:
	Derived3();
	virtual ~Derived3();
	virtual void withdraw (double amount) override;
	virtual void print(std::ostream &os) const override;
};
// Not required since we are using interface methodology
// std::ostream &operator<< (std::ostream &os, const Base_class &inputObj)
// {
// 	os << "Account Display";
// 	return os;
// }



// With the interface we can just add a random class easily and we can reuse the
// print override calls
class Dog: public I_interface
{
public:
	Dog();
	virtual ~Dog();
	virtual void print(std::ostream &os) const override;

};

#endif //_I_INTERFACE_H_