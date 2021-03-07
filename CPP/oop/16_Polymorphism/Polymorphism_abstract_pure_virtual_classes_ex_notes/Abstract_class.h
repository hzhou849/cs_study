// Abstract class used to implement pure virtual function

#ifndef _ABSTRACT_CLASS_H_
#define _ABSTRACT_CLASS_H_

#include <iostream>


//Abstract Base class
class Abstract_class  
{
private:
	//Attributes common to all shapes
public:
	Abstract_class();
   	virtual ~Abstract_class();
	virtual void pure_feature1() = 0; // pure virtual function
	virtual void pure_feature2() = 0; // Pure virtual function
};

// Abstract derived class A
class Abstract_derived_A : public Abstract_class // Abstract class 
{
public:
	Abstract_derived_A(); 
	virtual ~Abstract_derived_A();
};

// Abstract derived Class B
class Abstract_derived_B : public Abstract_class // Abstract class
{
public:
	Abstract_derived_B();
	virtual ~Abstract_derived_B();
};


// Concrete class
class Concrete_class : public Abstract_derived_A
{
public:
	Concrete_class();
	~Concrete_class();
	virtual void pure_feature1() override;
	virtual void pure_feature2() override;
};


// Concrete class2
class Concrete_class2 : public Abstract_derived_A
{
public:
	Concrete_class2();
	~Concrete_class2();
	virtual void pure_feature1() override;
	virtual void pure_feature2() override;
};


// Concrete class
class Concrete_class3 : public Abstract_derived_A
{
public:
	Concrete_class3();
	~Concrete_class3();
	virtual void pure_feature1() override;
	virtual void pure_feature2() override;
};


#endif // _ABSTRACT_CLASS_H_