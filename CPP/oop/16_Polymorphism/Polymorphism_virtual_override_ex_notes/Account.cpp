#include "Account.h"

// ACCOUNT 
Account::Account() {}
Account::~Account()
{
	std::cout << "BASE_ACCOUNT DECONSTRUCTOR CALLED" << std::endl;
}

void Account::withdraw(double amount)
{
	std::cout << "BASE_CLASS:" << std::endl;

}


// Class ACCOUNT_D1
Account_D1::Account_D1() {}
Account_D1::~Account_D1() 
{
	std::cout << "DERV1_ACCOUNT Deconstructor called" << std::endl;
}

void Account_D1::withdraw(double amount)
{
	std::cout << "DERV1_CLASS:" << std::endl;
}


// Class Account_D2
Account_D2::Account_D2() {}
Account_D2::~Account_D2() {
	std::cout << "DERV2_CLASS Deconstructor called" << std::endl;
}

void Account_D2::withdraw(double amount)
{
	std::cout << "DERV2_CLASS:" << std::endl;
}


// Class Account_D3
Account_D3::Account_D3() {}
Account_D3::~Account_D3() {
	std::cout << "DERV3_CLASS Deconstructor called" << std::endl;
}

void Account_D3::withdraw(double amount) const
{
	std::cout << "DERV3_CLASS:" << std::endl;
}
