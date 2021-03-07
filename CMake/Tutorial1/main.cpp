#include <iostream>


int main(int argc, char* argv[]) 
{
	float first_no, second_no, result_add, result_div;


	std::cout <<"Enter first number:\t";
	std::cin>> first_no;
	std::cout << "Enter Second number:\t";
	std::cin>> second_no;

	result_add = first_no + second_no;
	std::cout << "Addition result:\t" << result_add << std::endl;

	return 0;

}

