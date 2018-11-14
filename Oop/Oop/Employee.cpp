#include "Employee.hpp"
#include <string>

int Employee::GetEmployeeId()
{
	return this->employeeId;
}

Employee::Employee(std::string firstName, std::string lastName, int employeeId)
	: Person(firstName, lastName)
{
	this->employeeId = employeeId;
}