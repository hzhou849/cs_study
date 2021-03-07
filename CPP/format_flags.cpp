/* 
 * CPP - Format flags
 * 
 * set formatting flags for the entire file and change/restore
 * default settings
 * 
 * 
 * In this example set the document to hex cout and restore 
 * 
 *  Default when displaying integer values is  decimal (base 10)
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
 * 		std::cout << std::resetioflags (std::ios::basefield); - set it back to default decimal


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





//method 1
#include <iostream>
#include <ios>  		//required package

int main() 
{	
	// Backup of saved state should be done as early as possible
	// otherwise you may have an incorrect state with changes already.
	std::ios_base::fmtflags backupFlag( std::cout.flags() );		// save current state
	std::cout << std::hex << 123 << std::endl;;


	std::cout.flags ( backupFlag );			// restore flag state
	std::cout << 123 << std::endl;
}

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
