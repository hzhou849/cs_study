/* Display Buffer */


#include <iostream>
// #include <string>

#include <cstring>
#include <sstream>

class DisplayBuffer {
private:
	char buffer[100][1000]; // use the heap instead.
	char* buffer_heap;
public:
	DisplayBuffer();
	~DisplayBuffer();

	void add_line( std::ostringstream s );
	void dump_buffer();
};	

DisplayBuffer::DisplayBuffer (): buffer_heap{nullptr} {
	buffer_heap {}
};

DisplayBuffer::~DisplayBuffer() {};


int main() {
	std::ostringstream s1;

	int i = 99;	
	s1 << "hello" << i << std::endl;;
	std::cout << s1.str();
	std::string var = s1.str();
	std::cout << var << std::endl;

	int n = var.length();
	

	//declaring character array
	char char_array[n+1];

	//copy the contents of the stirng to char array
	strcpy(char_array, var.c_str());

	for (int i=0; i<n; i++) {

		std::cout << char_array[i]<< std::endl;
	}
	return 0;
}
