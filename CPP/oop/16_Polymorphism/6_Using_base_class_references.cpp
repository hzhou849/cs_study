/* 189 - Using A Base class reference
 *
 * for references see 109 in Functions
 * Differnce?
 * Poinnters - is a variable that holds memory address of another variable. 
 *			- needs to be dereferenced with * operator to access the memory location 
 *			  it is pointing to.
 * Reference	- variable is an alias, that is, another name for an already existing variable
 * 				- like a pointer also implemented by storing the address of an object.
 * 				- can be thought of as a "Constant pointer" (not to be confused with pointer
 * 				  storing a constant value!) with automatic indirection 
 * 				  (compiler will apply the * operator to dereference for you.)
 * allows for Base class references with dynamic polymorphism
 * Useful when we pass objects to functions that expect a Base class reference
 * 
 */

// Using base class references
Account a;
Account &ref = a;
ref.withdraw(1000); // Account:: withdraw


Trust t;
Account &ref1 = t;
ref1.withdraw(1000); // Trust::withdraw


//Example 2 - here you can see it accepts a refernce  as arg1
//			  and will dynamically bind the class you want to override
			- allows us to write a general do_withdraw function and use polymorphism.
//Base class
void do_withdraw(Account &account, double amount) {
	account.withdraw(amount);
}

Account a;
do_withdraw(a, 1000);	// Account:: withdraw

Trust t;
do_withdraw(t, 1000);	// Trust::withdraw


// Example 3:

int main() {
	Account a;
	Account &ref = a;
	ref.withdraw(1000);		// Account::withdraw

	Trust t;
	Account &ref1 = t;
	ref1.withdraw(1000);	// Trust::withdraw

	Account a1;
	Savings a2;
	Checking a3;
	Trust a4;

	do withdraw(a, 1000); // in Account::withdraw
	do withdraw(a, 1000); // in Savings::withdraw
	do withdraw(a, 1000); // in Checking::withdraw
	do withdraw(a, 1000); // in Trust::withdraw

	return 0;
}