/* Binary Converter 
 *
 * Binary converter with Queue implementatino
 * 
 */

#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <cstring>
#include <vector>
#include "Semaphore.hpp"
 
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
	std::cout << "enqueued: " << *eq  << "\taddress:  "<< &*eq<< std::endl;
	eq++;

	return 0;
}

// mode - verbose display
// 0 - turn off verbose mode
// 1 or N- enable display mode
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
		std::cout << "Q address: " << &(*temp) << " value: " <<std::showbase << std::uppercase << std::hex << *temp;
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

/* Stack class */
class Stack {
private:
	uint16_t *start;
	uint16_t *top;
	int capacity=5;
public:
	Stack() {
		
		// start = (uint16_t*)malloc(sizeof(uint16_t) * size);
		start = new uint16_t[capacity];
		top = start;

	}
	~Stack(){
		free(start);
	}

	int push(uint16_t number) {
		if (number == 0) {
			return -1;
		}
		if (top == (start + capacity)) {
			std::cout << "\nStack full\n" << std::endl;
			return -1;
		}

		*top = number;
		std::cout << "pushed: " << *top << "\taddress: " <<top << std::endl; 
		top++;
		return 0;
	}

	int pop() {
		if (top ==  start) {
			std::cout << "stack is empty" << std::endl;
			return -1;
		}
		// decrement top position first
		--top;
		std::cout << "popped: " << *top << " address: " << top << std::endl;
		return *top;
	}

	void display() {
		uint16_t *temp = start;
		while (temp != (start + capacity)) {
			//&(*temp)  printing address , bc we are deref what temp points to. temp->&start(we want this address)
			std::cout << "stack value: " << *temp << "\taddress: \t"<<&(*temp);

			if (temp == top) {
				std::cout << "  <-Top";
			}
			std::cout << std::endl;
			temp++;
		}
	}

};


/* Binary converter class */
class BinConverter {
private: 
	uint16_t mask = 1;
	char *lastBinary='\0';
	// uint16_t size = 7; // 0-7 size is 8 index 0
public:
	BinConverter();
	~BinConverter();
	uint16_t convert(uint16_t number);
	uint16_t convert(Queue *q);
	std::string convert_str(uint16_t number);
	char* convert_cstr(uint16_t number);	// c-string version

	
};

BinConverter::BinConverter(){ 
	lastBinary = (char*) malloc (sizeof(char) * 8 + 1);
} // Note this syntax, must carry over Template variables

BinConverter::~BinConverter() {
	free (lastBinary);
}

uint16_t BinConverter::convert( uint16_t  number) {
	uint16_t size = (sizeof(uint16_t) * 8) -1; // 1 byte = 8bits 0-7
	// std::cout << "size: "<< size << std::endl;
	uint16_t temp;
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

std::string BinConverter::convert_str(uint16_t number) {
	// int counter = 0;
	uint16_t temp;
	// uint16_t size = (sizeof(uint16_t) * 8) -1; // 0 index count
	uint16_t size = 7;
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

char* BinConverter::convert_cstr(uint16_t number) {
	uint16_t temp=0;
	uint16_t size = 7 ; // at index 0, index = datatype -1
	char *bitString;
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

uint16_t BinConverter::convert (Queue *q) {
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

/* Thread processor class */
class Thread_processor {
private:
	std::vector<std::thread*> vec_threads; // using pointers so we dont copy the threads itself into vector, just address
	std::mutex tp_mutex;
	Semaphore sema_p;
	Stack s;
	void processing_func();
	
public:
	Thread_processor();
	~Thread_processor();
	void addQueue(Queue *q);
};

Thread_processor::Thread_processor(){
	for (int i=0; i < 3; i++) {
		std::cout << "Creating thread " << i << std::endl;
		// create thread pointers on heap.
		std::thread *t = new std::thread(&Thread_processor::processing_func, this); 
		this->vec_threads.push_back(t);
	}
}
Thread_processor::~Thread_processor() {
	for (auto temp: vec_threads) {
		temp->join();		// join the threads 
		delete temp;		// free the thread pointers on heap
	}
}

void Thread_processor::processing_func() {

	std::cout << "runnning....\n\n" << std::endl;
	uint16_t fetched_value =0;
	BinConverter convert;
	// run the threadpool
	while(true) {
			std::cout << "runnning loop....\n\n" << std::endl;

		sema_p.wait(std::this_thread::get_id()); 
		tp_mutex.lock();
		fetched_value = s.pop();
		std::this_thread::sleep_for(std::chrono::seconds(fetched_value));
		tp_mutex.unlock();
		convert.convert_str(fetched_value);
	}
}

void Thread_processor::addQueue(Queue *q){

	uint16_t value=0;
	

	//reassign to local stack for processing.
	while (value < 65535){

		// std::cout << "value: "<< value << std::endl;
		value = q->dequeue(0);

		tp_mutex.lock(); // lock the stack 
		s.push(value);
		tp_mutex.unlock();
		sema_p.notify();

	}

	s.display();

}




/* Driver class */
int main() {
	BinConverter bc; // makes this a uint16_t converter

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

	Queue qObj2(5);
	qObj2.enqueue(0x14);
	qObj2.enqueue(0x08);
	qObj2.enqueue(0x0A);
	qObj2.enqueue(0x09);
	qObj2.enqueue(0x1F);

	Thread_processor tp; // create the thread processor object
	// tp.addQueue(&qObj2);
	
	std::this_thread::sleep_for(std::chrono::seconds(5));
	



	return 0;
}
