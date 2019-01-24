/* OOP Circular Queue version
	see cq2_better version , using the boolean 'qfull' better than the counter


		if (qfull == true) {
		std::cout << "Queue is at max capacity " << element << " not entered. "<< " State: "<< qfull << std::endl;
		return -3;
	}

	int Queue::dequeue() {
	// if dq and eq are at the same address and qfull is false, means the queue is empty 
	if (dq == eq && qfull == false) {
		std::cout << "queue is empty" << std::endl;
		return -1;
	}
 */
#include <iostream>
#include <thread>
#include <chrono>

#ifndef  _CQ_H_
#define _CQ_H_

class cq {
private:
	int capacity;
	short *start;
	short *eq;
	short *dq;
	int ret_value;
	int counter;

public:
	// constructor
	cq(int capacity);
	~cq();

	// Member functions
	int add(int element);
	int remove();
	void display();
};

#endif //_CQ_H_

//cq.cpp
// #include "cq.h"

//Constructor
cq::cq(int capacity): capacity{capacity}, start{nullptr},eq{nullptr}, dq{nullptr}, ret_value{0}, counter{0} {
	// allocate memory in heap space.
	// this->start = new short [capacity];
	this->start = (short*)malloc (capacity * sizeof(short));	// C method
	this->eq = this->start; // initialize the eq
	this->dq = this->start; // initialize the dq
}

int cq::add(int element) {
	if (element == 0) {
		return -1;
	}
	if (this->counter >= this->capacity) {
		std::cout << "Queue full" << std::endl;
		return -1;
	}

	// write into queue
	*(this->eq) = element;
	this->eq++; // increment the eq 
	this->counter++;

	//handle the wrap around address is at last address
	if (this->eq == (this->start + this->capacity)) {
		this->eq = this->start;
	}

	display();
	return 0;
}

int cq::remove() {
	if (this->counter <= 0) {
		std::cout << "Queue is empty" << std::endl;
		return -1;
	}

	this->ret_value = *(this->dq);
	*(this->dq) = 0; //"erase " the data
	this->dq++;
	this->counter--; // decrement the counter 

	if (this->dq == (this->start + this->capacity)) {
		this->dq = this->start;
	}

	display();
	return 0;
}

void cq::display() {
	short *temp_addr = this->start;

	std::cout << "\033[s";	//save the cursor position
	std::cout << "\033[3A";
	std::cout << "\033[2J"; // clear the screen
	std::cout << "\033[u";  // restor cursor position

	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	std::cout << "counter: " << this->counter<< std::endl;
	while (temp_addr != this->start + this->capacity) {
		if (temp_addr == this->eq) {
			std::cout << "<eq>";
		}
		if (temp_addr == this->dq) {
			std::cout << "<dq>";
		}
		if (temp_addr != this->eq || temp_addr !=this->dq){
			std::cout << "\t";
		}
		std::cout << "address: " << temp_addr << " value: " << *temp_addr <<  std::endl;
		temp_addr++;
		
	}
}

//main.cpp
int main() {
	cq q(5);
	q.add(31);
	q.add(42);
	q.add(57);
	q.add(63);
	q.remove();
	q.add(70);
	q.add(71);
	q.remove();
	q.remove();
	q.remove();
	q.remove();
	q.remove();
	q.remove();

	return 0;
}


//Destructor
cq::~cq () {
	delete(this->start);
}




