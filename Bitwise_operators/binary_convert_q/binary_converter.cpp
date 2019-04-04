/* Binary Converter 
 *
 * Binary converter with Queue implementatino
 * 
 */

#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <cstring>

 
/* Queue class */
class Queue {
private:
	short *start;
	short *eq;
	short *dq;
	int capacity;
	int value;
public:
	Queue(int capacity);
	~Queue();
	int enqueue (int value);
	int dequeue (int mode);
	void display_q();
};

Queue::Queue(int size): start{nullptr}, eq{nullptr}, dq{nullptr}, capacity{size}, value{0} {
	this->start = new short[capacity];
	this->eq = start;
	this->dq = start;
	this->capacity = size;
	// start = (short*)malloc(sizeof(short) * capacity);
	std::cout << "Queue created: \n";
	std::cout << " start: " << start << std::endl;  // address of start = &(*start)
	std::cout << " eq " << &(*eq) << std::endl; 
}
Queue::~Queue(){
	delete[] this->start;
	// delete eq;
	// delete dq;
	
}

int Queue::enqueue(int value) {
	if (value == 0) {
		return -1;
	}
	if (eq == start + capacity){
		std::cout << "Queue limit reached" << std::endl; 
		return -1;
	}

	*eq = value;
	std::cout << "enqueued: " << *eq  << " address: "<< &*eq<< std::endl;
	eq++;

	return 0;
}

int Queue::dequeue(int mode) {
	int element;

	if (dq == eq) {
		std::cout << "Queue is empty. "<< std::endl;
		return -1;
	}
	element = *dq;

	// for verbvose mode
	if (mode != 0 ) 
		std::cout << "dequeued: " << element << " address: " << &*dq << std::endl;

	dq++;
	return element;
}

void Queue::display_q() {
	short *temp = start;

	while (temp != (start + capacity)) {
		std::cout << "address: " << &(*temp) << " value: " <<std::showbase << std::uppercase << std::hex << *temp;
		//std::cout << "address: " << temp << std::endl; will also work
		if (temp == eq) {
			std::cout << " <- eq" ; 
		}
		if ( temp == dq) {
			std::cout << " <- dq";
		}
		std::cout << std::endl;
		temp++;
	}
}
 


/* Binary converter class */
class BinConverter {
private: 
	uint32_t mask = 1;
	char *lastBinary='\0';
	// uint32_t size = 7; // 0-7 size is 8 index 0
public:
	BinConverter();
	~BinConverter();
	uint32_t convert(uint32_t number);
	uint32_t convert(Queue *q);
	std::string convert_str(uint32_t number);
	char* convert_cstr(uint32_t number);	// c-string version

	
};

BinConverter::BinConverter(){ 
	lastBinary = (char*) malloc (sizeof(char) * 8 + 1);
} // Note this syntax, must carry over Template variables

BinConverter::~BinConverter() {
	free (lastBinary);
}

uint32_t BinConverter::convert( uint32_t  number) {
	uint32_t size = (sizeof(uint32_t) * 8) -1; // 1 byte = 8bits 0-7
	// std::cout << "size: "<< size << std::endl;
	uint32_t temp;
	int counter=0;
	for (int i = size; i >=0; i--) {
		if (counter %4 == 0) {
			std::cout << " ";
		}
		counter++;
		temp = number >> i;
		// if (temp & mask) {
		// 	std::cout << "1";
		// }else {
		// 	std::cout << "0";
		// }
	}
	std::cout << " " << std::endl;

	return 0;
}

std::string BinConverter::convert_str(uint32_t number) {
	// int counter = 0;
	uint32_t temp;
	// uint32_t size = (sizeof(uint32_t) * 8) -1; // 0 index count
	uint32_t size = 7;
	std::string bitString;

	// std::cout << "size: " << size << std::endl;

	for (int i=size; i>=0; i-- ) {
		temp = number >> i;
		if (temp & mask) {
			bitString +="1";
		} else {
			bitString += "0";
		}
	}

	return bitString;
}

char* BinConverter::convert_cstr(uint32_t number) {
	uint32_t temp=0;
	uint32_t size = 7 ; // at index 0, index = datatype -1
	char *bitString = "string";
	// bitString = new char [size + 1]; // +1 for null terminator C++ style
	bitString = (char*)malloc(sizeof(char) * size + 1);
	bitString[8]='\0'; // add null terminator
	


	for (int i=size; i>=0; i--) {
		temp = number >> i;
		if (temp & mask) {
			bitString[size-i] = '1';
		} else {
			bitString [size-i] = '0';
		}
		//wcout is used to printout cstrings
		// std::wcout << "bitstring: " << bitString[8-i] <<std::endl; // wcout c_strings

	}

	this->lastBinary = strcpy(lastBinary, bitString);
	// delete[] bitString; // C++ malloc  if using 'new'
	free (bitString);

	return lastBinary;

}

uint32_t BinConverter::convert (Queue *q) {
	int q_dvalue = q->dequeue(0); // get the initial queue value
	std::string bin_value;
	
	if (q == 0) {
		return -1;
	}

	while (q_dvalue > 0 ) {
		convert(q_dvalue);
		std::cout << "q_dvalue: " << std::hex<< q_dvalue << " dec: " << std::dec<< q_dvalue<<" binary: " << convert_cstr(q_dvalue) << std::endl;
		q_dvalue = q->dequeue(0); // update the value	
	}

	return 0;

}


/* Driver class */
int main() {
	BinConverter bc; // makes this a uint32_t converter

	Queue qObj(5);
	qObj.enqueue(0x01);
	qObj.enqueue(0x31);
	qObj.enqueue(0xB2);
	qObj.dequeue(1);
	qObj.enqueue(0xFA);
	qObj.enqueue(0x1A);
	qObj.enqueue(0xB2);
	qObj.enqueue(0xCD);

	
	qObj.display_q();

	bc.convert(&qObj);
		



	return 0;
}
