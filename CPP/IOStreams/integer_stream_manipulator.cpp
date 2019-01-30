/* Formatting Integer types 
 *
 * Default when displaying integer values is  decimal (base 10)
 * ex:
 * 		std::cout << std::showbase <<  std::uppercase ;
 * noshowbase - prefix used to show hex or oct
 * nouppercase - when displaying a prefix and hex values it will be lower case - default is lowercase?
 * noshowpos - no '+' is displayed for positive numbers
 * 
 * these manipulators affect all further output to the stream
 * 
 * setting/resetting using setf():
 * 		std::cout.setf(std::ios::showbase);
 * 		std::cout.setf(std::ios::uppercase);
 * 		std::cout.setf(std::ios::showpos);
 * 
 * Reset to default:
 * 		std::cout << std::resetioflags (std::ios::basefield); - set it back to decimal
 * 		std::cout << std::resetioflags (std::ios::showbase);
 * 		std::cout << std::resetioflags (std::ios::showpos);
 * 		std::cout << std::resetioflags (std::ios::uppercase);
 */

#include <iostream>
#include <iomanip>

int main() {
	int num {255};
	
	std::cout << std::dec << num << std::endl;	//255
	std::cout << std::hex << num << std::endl;  // ff
	std::cout << std::oct << num << std::endl;  //377


	// show base prefix 
	std::cout << std::showbase; 				//std::noshowbase
	std::cout << std::dec << num << std::endl;	//255
	std::cout << std::hex << num << std::endl;  // 0xff - prefix 0x for hex
	std::cout << std::oct << num << std::endl;  //0377 - prefix '0' for octal


	// uppercase - toggle back useing 'nouppercase'
	std::cout << std::showbase << std::uppercase;
	std::cout << std::hex << num << std::endl;		//0XFF

	// displaying the positive sign
	int num1{255};
	int num2 {-255};
	std::cout << std::dec;
	std::cout << std::endl;
	std::cout << num1 << std::endl; 	// 255
	std::cout << num2 <<std::endl;		//-255

	std::cout << std::showpos;			// std::noshowpos

	std::cout << num1 << std::endl;		// +255
	std::cout << num2 << std::endl;		//-255
}


