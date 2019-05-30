#include <iostream>
#include <vector>

/*
Printing raw hex values. 


std::uint16_t Pga308::read(bool otp, std::uint16_t bank, std::uint16_t reg)
{
    std::uint16_t command_byte = 0x80 | // Read Bit
                                 static_cast<std::uint16_t>(otp << 6) |
                                 static_cast<std::uint16_t>(bank << 4) |
                                 static_cast<std::uint16_t>(reg);

    std::cout << std::hex << static_cast<unsigned int>(command_byte) << std::endl;

    std::vector<std::uint8_t> data{ 0x55, static_cast<std::uint8_t>(command_byte) };

    // m_uart.write(data);
    // m_uart.read();

    return 0;
}



When using Char types, C++ tries to print ASCII
make sure you use the static_cast<unsigned> on the value 
before printing otherwise it will not work. Even
if the data type is unsigned char, you must reinterpret cast.
*/

int main (int argc, char *argv[]) 
{
	uint8_t* bank_array;

	// bank_array = new char[8 * sizeof (char)];
	bank_array = (uint8_t*)malloc(sizeof(uint8_t) * 8); // C-Style malloc

	bank_array[0] = 0xFF;
	bank_array[1] = 0x14;
	bank_array[2] = 0x03;


	for (int i=0; i<8; i++) 
	{	
		// std::cout << "Direct Pointer: "<< (bank_array+i) << std::endl;

		/* Must use reinterpret static cast<unsigned> to print hex */
		std::cout << "Bank value "<<i<<":"<< std::showbase<<std::hex<< static_cast<unsigned>(bank_array[i])<< std::endl;
	}



	 double *temp_ptr {nullptr};
    temp_ptr = new double[5 * (sizeof(double))]; // allocate array size of double

   *(temp_ptr+2) = 999; //pointer offset notation 
	//if useing array[x] format you must reinterpret with static cast
	// to see the hex value dump
	// ie. <<cout<<std::hex<<static_cast<int>(array[i])
    std::cout << "temp_ptr: " << temp_ptr[2] << std::endl; // pointer subscript notation array syntax requires 
    std::cout << "temp_ptr: " << (temp_ptr +1)<< std::endl; 
    std::cout << "temp_ptr: " << (temp_ptr +2)<< std::endl; 
    
    delete[] temp_ptr;



	free(bank_array);
	return 0;
}



