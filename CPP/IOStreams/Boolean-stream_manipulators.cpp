/* Stream Manipulators  - Booleans
 *
 * std:: boolalpha - enable true false
 * std:: noboolalpha - diasble true/false and use 0,1
 * 
 * function flag method
 * - can also use this flag method to set the flag for the entire program
 * std::cout.setf(std::ios:boolalpha)
 * 
*/ 

#include <iostream>
#include <iomanip> // Must include for manipulators

int main() {
	std::cout << "noboolalpha-default (1 == 1):" << (1 == 1) << std::endl;
	std::cout << "noboolalpha-default (2==2) :" << (1 ==2 ) << std::endl; 

	// setting still stays for fututre insertions
	std::cout << std::boolalpha; // change to true/false
	std::cout << "noboolalpha-default (1 == 1):" << (1 == 1) << std::endl;
	std::cout << "noboolalpha-default (2==2) :" << (1 ==2 ) << std::endl; 

	// to disable - use "std::noboolalpha"
	std::cout << std::noboolalpha; // change to true/false
	std::cout << "noboolalpha-default (1 == 1):" << (1 == 1) << std::endl;
	std::cout << "noboolalpha-default (2==2) :" << (1 ==2 ) << std::endl; 

	// flag method
	std::cout.setf(std::ios::boolalpha);
	std::cout << "setf(flag method)-default (1 == 1):" << (1 == 1) << std::endl;
	std::cout << "setf(flag method)-default (2==2) :" << (1 ==2 ) << std::endl; 

	// reset the flag 
	std::cout << std::resetiosflags(std::ios::boolalpha);
	std::cout << "setf(flag method)-reset flag (1 == 1):" << (1 == 1) << std::endl;
	std::cout << "setf(flag method)-reset flag (2==2) :" << (1 ==2 ) << std::endl; 
	
}


