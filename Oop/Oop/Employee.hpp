#pragma once
#include "Person.hpp"
#include <string>

class Employee : public Person
{
private:
	int employeeId;
public:
	int GetEmployeeId();
	Employee(std::string firstName, std::string lastName, int employeeId);
};