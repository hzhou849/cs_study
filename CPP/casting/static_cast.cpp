/*
 * C++ Static casting
 *  
 * 
 * NOTE: in order for uint8 to print number values properly you must cast to "unsigned" during cout
 */


#include <iostream>
// #include <iomanip> // optional

int main () 
{
	uint16_t writeData =  0xffaa;

	std::cout << std::hex <<std::showbase << "Original data: " << (writeData & 0x00ff) << std::endl;

	uint8_t LSB = static_cast<unsigned>(writeData) & 0x00ff;
	LSB += 2;
	
	uint8_t writeData2 = 0xfa;
	std::cout << "LSB converted: " << static_cast<unsigned>(LSB) << std::endl;
	std::cout << "LSB2 : " << (unsigned) writeData2 << std::endl;	// cast required to print hex values

}
