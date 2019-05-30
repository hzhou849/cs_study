#pragma once
#include <string>

class Person
{
private:
	std::string firstName;
	std::string lastName;
public:
	Person(std::string firstName, std::string lastName);
	std::string GetFirstName();
	std::string GetLastName();
};