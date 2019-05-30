/*
 * Hex to Binary converter for bit manipulation
 * 
 * Setting a bit - use bitwise OR operator to set a bit
 * example:
 * 	num |= 1UL << n;		// This will set the Nth bit of num
 * 
 * Clearing a bit:			
 * 	number &= ~(1UL << n);  // This will clear the Nth bit of number. 
 * 							//Must invert the bit string with bitwise NOT operator
 * 							// then AND it
 * 
 * Toggling a bit:
 * 	number ^= 1UL << n; 	// using the XOR ^ operator
 * 
 * Checking a bit		
 *  To check a bit, shift the number n times to the right, then bitwise AND it.
 * 	bit = (number >> n) & 1U;
 *  That will put the value of the nth bit of number into the variable bit
 *  so if you want to check bit 5, shift 5 times to the right and mask 1 to get the result
 * 
 * Changing Nth bit to x
 * 	- Setting the Nth bit to either 1 or 0 by using 2's compliment c++ implementation
 *  number ^= (-x ^  number)
 * 	- Bit n will be set if x is 1 and cleared if x is 0. If x has some other value,
 * 		you will get x = !!x will booleanize it to 0 or 1
 * 
 * To make this independent of 2's complement negation behaviour (where -1 has all bits set, unlike on a 1's complement or sign/magnitude C++ implementation), use unsigned negation.

 * number ^= (-(unsigned long)x ^ number) & (1UL << n);
 * or
 * 
 * unsigned long newbit = !!x;    // Also booleanize to force 0 or 1
 * number ^= (-newbit ^ number) & (1UL << n);
 * It's generally a good idea to use unsigned types for portable bit manipulation.
 * 
 * or
 * 
 * number = (number & ~(1UL << n)) | (x << n);
 * (number & ~(1UL << n)) will clear the nth bit and (x << n) will set the nth bit to x.
 * 
 * It's also generally a good idea to not to copy/paste code in general and so many people 
 * use preprocessor macros (like the community wiki answer further down) or some sort of encapsulation.
 * 
 * 
 */


#include <iostream>
#include <cstdint>
#include <cstring>
#include <stdint.h>


class BinConverter {
private:
	uint8_t mask = 1;							// 8bit 2bytes
	char *lastBinary = '\0';
	// uint32_t size = 7; 						// 0-7 size is 8 index 0
public:
	BinConverter();
	~BinConverter();
	uint8_t convert(uint8_t hexNum);
	std::string convert_str(uint16_t number);
	char* convert_cstr(uint8_t number);			// C-string version

};

/* Constructor */
BinConverter::BinConverter() {
	/* C memory allocation */
	lastBinary = (char*) malloc (sizeof(char) * 8 +1);		// uses 'free' to deallocate memory

	/* C++ memory allocation */
	lastBinary = new char[8 * (sizeof(char)) + 1];			// use 'delete[]' to deallocate memory
}

/* Destructor */
BinConverter::~BinConverter() {
	free (lastBinary);
}

uint8_t BinConverter::convert (uint8_t hexNum) {
	uint32_t size = (sizeof(uint8_t) * 8)  -1;			// using 32bit to store theorethical size 1 byte = 8bits 0-7
	std::cout << "size: " << size << std::endl;

	uint8_t temp;					// Temp buffer for bit manipulation
	int counter = 0;
	for (int i = size; i >= 0; i--) {
		if (counter % 4 == 0) {
			std::cout << " ";
		}

		counter++;
		temp = hexNum >> i;		// shift from 7 to 0 spaces right
	}


}
