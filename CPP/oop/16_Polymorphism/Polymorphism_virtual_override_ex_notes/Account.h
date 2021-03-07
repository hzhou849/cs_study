//#pragma once
#ifndef _ACCOUNT_H
#define _ACCOUNT_H


#include <iostream>


/// Virtual specifier
// Basic Rule of thumb, if your class has a virtual function,
// you must ALWAYS provide a virtual destructor!
// If base class is virtual, all dervived are too, but good practice
// to explicitly write it anyways.

/// Override specifier 
// Since virtual dervided classes must match in order to work, if you make a mistake
// in the function signature, the object calling pointer will get redefined and call the
// base class. We can prevent this by using the 'override' specifier to protect it so the
// compiler will throw an error and let us know

/// Final Specifier
// On a class will prever futher inheritance
// On a member function, it will prevent further derviving

class Account
{
public:
	Account();
	virtual void withdraw(double amount);
	virtual ~Account();
};

class Account_D1 : public Account
{
public:
	Account_D1();
	virtual ~Account_D1();
	virtual void withdraw(double amount) ; // we cannot dervive any futher down this heirarcy with the 'final specifier'
};

class Account_D2 : public Account
{
public:
	Account_D2();
	virtual  ~Account_D2();
	virtual void withdraw(double amount);
};

class Account_D3 : public Account
{
public:
	Account_D3();
	virtual ~Account_D3();
	// noticed i added const to change the signature from base
	// Also the override specifier will no throw an error bc the functions don't match for polymorphism anymore
	//virtual void withdraw(double amount) const override ;  
	virtual void withdraw(double amount) const;
};	




#endif // _ACCOUNT_H
