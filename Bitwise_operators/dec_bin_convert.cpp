/* Decimal to binary converter
 * 
 * Int - 32 bits - 4bytes
 * Short - 16bits - 2bytes
 * char -8bits 1 byte
 * 
 *  NOTE: BECAREFUL make sure using Unsigned variables.
 *  if not, overshifts will result in negative numbers
 *  because Linux OS uses two's compliement, the MSB 
 *  is the sign bit 
 */

#include <iostream>


int decToBin(int n) {
	int print_size = (sizeof(n) * 8) -1 ;
	int count = 0;
	std::cout << "size: " << print_size<< std::endl;

	// size of int is assumed to be 32bits
	for (int i =print_size; i >= 0 ; i-- ) {
		if (count %4 == 0 && count !=0) {
			std::cout << " ";
		}
		int shifted = n >> i; // shift to the right 'i' times
		if (shifted & 1)  { // mask '0000 0000...0001'
			std::cout << "1";
		} else {
			std::cout << "0";
		}
		count++;
	}
	std::cout << std::endl;

	return 0;
}

int hexToBin(unsigned char h) {
	unsigned int mask = 1;
	int count = 0;
	int print_size = (sizeof(h) * 8 -1)  ; // 1byte = 8bits we want 0-7bits
	std::cout << "size: " << print_size<< std::endl;
	std::cout << "0x";
	for (int i = print_size; i >= 0 ; i--) {
		if (count % 4==0 && count != 0) {
			std::cout << " ";
		}
		int temp_shifted = h >> i;
		// std::cout << "\ntemp: "<< temp_shifted << "\n"<< std::endl;
		if (temp_shifted & mask) {
			
			std::cout << "1";
		} else {
			std::cout << "0";
		}
		count++;
	}
	std::cout << std::endl;

	return 0;
}

int main() {
	// int n = 32;
	decToBin(17);
	hexToBin(0xfa);
	unsigned int mask = 1;
	unsigned int var = 5;
	unsigned int size = sizeof(var) *  8  ;
	unsigned int shifted = (var >> size);
	if (shifted & mask) {
		std::cout << "1\n";
	} else {
		std::cout << "0\n";
	}
	std::cout << "var: " << shifted <<std::endl;
	return 0;
}
// 0000 0000 0000 0000 0000 0000 0011 0101
// 0000 0000 0000 0000 0000 0000 0000 0000  

