/* Binary converter 
 *
 * using cstring and malloc  instead of c++ 11 std
 */ 

#include <iostream>
#include <cstdint>
#include <stdint.h>

 
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
	int dequeue ();
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
	eq = nullptr;
	dq = nullptr;
	capacity = 0;
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

int Queue::dequeue() {
	int element;

	if (dq == eq) {
		std::cout << "Queue is empty. "<< std::endl;
		return -1;
	}
	element = *dq;
	std::cout << "dequeued: " << element << "address: " << &*dq << std::endl;
	dq++;
	return element;
}


void Queue::display_q() {
	short *temp = start;

	while (temp != (start + capacity)) {
		std::cout << "address: " << &(*temp) << " value: " <<std::showbase << std::uppercase << std::hex << *temp<< std::endl;
		//std::cout << "address: " << temp << std::endl; will also work
		temp++;
	}
}
 
/* Binary converter class */
class BinConverter {
private: 
	uint32_t mask = 1;
	
	
public:
	BinConverter();
	// ~BinConverter();
	uint32_t convert(uint32_t number);
	uint32_t convert(Queue q);
	
};


BinConverter::BinConverter(){ 
} // Note this syntax, must carry over Template variables

uint32_t BinConverter::convert( uint32_t  number) {
	uint32_t size = (sizeof(uint32_t) * 8) -1; // 1 byte = 8bits 0-7
	std::cout << "size: "<< size << std::endl;
	uint32_t temp;
	int counter=0;
	for (int i = size; i >=0; i--) {
		if (counter %4 == 0) {
			std::cout << " ";
		}
		counter++;
		temp = number >> i;
		if (temp & mask) {
			std::cout << "1";
		}else {
			std::cout << "0";
		}
	}
	std::cout << " " << std::endl;

	return 0;
}



int main() {
	BinConverter bc; // makes this a uint32_t converter

	Queue qObj(5);
	qObj.enqueue(0x01);
	qObj.enqueue(0x31);
	qObj.enqueue(0xB2);
	qObj.dequeue();
	qObj.enqueue(0xFA);
	qObj.enqueue(0x1A);
	qObj.enqueue(0xB2);
	qObj.enqueue(0xCD);

	
	qObj.display_q();
		



	return 0;
}
