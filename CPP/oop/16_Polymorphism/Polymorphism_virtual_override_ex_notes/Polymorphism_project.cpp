// Polymorphism_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Virtual Functions
// Base Class Pointers

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


#include <iostream>
#include <stdlib.h>  // EXIT_SUCCESS flag

#include "Account.h"

//Smart withdraw function
void smart_withdraw(Account *account, double amount)
{
	account->withdraw(amount);
}

// Smart Reference function
void smart_withdraw(Account &account, double amount)
{
	account.withdraw(amount);
}

int main()
{
	int a = 65;
	int *address_int_variable = &a; // you can now view this in memory space

	std::cout << "\n=== Pointers ====" << std::endl;
	Account *p1 = new Account();
	Account *p2 = new Account_D1();
	Account *p3 = new Account_D2();
	//Account *p4 = new Account_D3();

	p1->withdraw(1000);
	p2->withdraw(1000);
	p3->withdraw(1000);
	//p4->withdraw(1000);

	std::cout << "\n ==== Smart_withdraw function" << std::endl;
	smart_withdraw(p1, 2000);
	smart_withdraw(p2, 2000);
	smart_withdraw(p3, 2000);
	//smart_withdraw(p4, 2000);

	std::cout << "\n ==== Smart_withdraw reference" << std::endl;
	Account acc;
	Account &ref = acc;
	ref.withdraw(1000);

	Account_D2 acc_d1;
	Account &ref1 = acc_d1;
	ref1.withdraw(1000);





	std::cout << "\n=== Clean up ====" << std::endl;
	delete p1;
	delete p2;
	delete p3;
	std::cout << "\n=== Manual cleanup over ====\n" << std::endl;
	//delete p4;


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
