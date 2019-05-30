/*
 *
 * Binary conversion
 * 
 */


#include <iostream>
#include <cstdint>
#include <stdint.h>

#ifndef _BITCONVERT_
#define _BITCONVERT_

class bitConvert
{
private:
	uint8_t mask;													// Mask used to isolate LSB

public:
	bitConvert();
	~bitConvert();
	

	template <typename T> void printBinary ( T inputHex );			// output terminal converted hex to binary 
	template <typename T> T getBit ( T inputHex );					// Retrieved request Register bit
	
};

/* 
 * Function to convert input decimal/hex number to binary
 * Generic takes a input of type 'T' and prints the sequence of bits.
 */
template <typename T> void  bitConvert::printBinary( T inputHex  )
{
	inputHex = static_cast<unsigned>(inputHex);
	int size = ( sizeof (T) * 8 ) -1;			// convert size T bytes to bits size  -1 for 0-index
	int counter = 0;
	T temp = 0;							
	

	std::cout << "Binary conversion of " <<std::hex << inputHex << ": ";
	for (int i = size; i >=0; i-- )				// popping off MSB first
	{
		// seperate 4bits for readability
		if (counter %4 == 0)
		{
			std::cout << " ";
		}
		counter++;

		// construct the sequence of 
		temp = inputHex >> i;
		if (temp & this->mask) {
			std::cout << "1";
		} else {
			std::cout << "0";
		}
		
	}
	std::cout << std::endl; 		// new line after the loop ends

}



#endif //_BITCONVERT_


