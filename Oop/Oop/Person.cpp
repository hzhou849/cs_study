#include "Person.hpp"
#include <string>
using namespace std;

std::string Person::GetFirstName()
{
	return this->firstName;
}

std::string Person::GetLastName()
{
	return this->lastName;
}

Person::Person(std::string firstName, std::string lastName)
{
	this->firstName = firstName;
	this->lastName = lastName;
}