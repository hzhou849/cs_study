
#include <iostream>
#include <thread>
#include "Queue.hpp"


Queue::Queue(int capacity)
	: capacity{capacity}, start{nullptr}, eq{nullptr}, dq{nullptr}, ret_value{0}, counter{0}, qfull{false} {
	
	// start = (short*)malloc (capacity * sizeof(short)); 		// c method
	start = new short[capacity * (sizeof(short))];				//c++ method oop
	eq = start;
	dq = start;
	
}

Queue::~Queue() {
	delete start; // deallocate heap data
}

int Queue::enqueue (int element) {
	if (element == 0)
		return -1;
	if (start == nullptr) 
		return -2;
	if (qfull == true) {
		std::cout << "Queue is at max capacity " << element << " not entered. "<< " State: "<< qfull << std::endl;
		return -3;
	}

	*eq = element; // add value 
	
	eq++;

	// wrap pointer if last address is reached.
	if (eq >= (start + capacity)) 
		eq = start;

	// if after increment, eq == dq the queue is at max capacity 
	if (eq == dq) 
		qfull = true;

	display();
	return 0;
}

int Queue::dequeue() {
	// if dq and eq are at the same address and qfull is false, means the queue is empty 
	if (dq == eq && qfull == false) {
		std::cout << "queue is empty" << std::endl;
		return -1;
	}

	ret_value = *dq;
	*dq = 0;	// "erase the value"
	dq++;

	if (qfull == true)
		qfull = false; // if the value is dequeued, list is no longer full

	// wrap the address around if reached end
	if (dq > (start + capacity))
		dq  = start;

	display();
	return 0;
}

void Queue::display() {
	std::cout << std::boolalpha; // makes boolean prints out true false instead of 0/1
	short* temp = start;
	std::cout << "\033[s"; // save the cursor position
	std::cout << "\033[3A"; // move cursor up 3 lines
	std::cout << "\033[2J"; // clear the screen
	std::cout << "\033[u";	// restore the cursor
	
	while (temp != (start + capacity)) {
		if (temp == eq)
			std::cout << "<eq>";
		if (temp == dq)
			std::cout << "<dq>";
		if (temp != dq || temp != eq)
			std::cout << "\t";
		std::cout << "address: " << temp << " value: " << *temp << " state: " << qfull<< std::endl;
		temp++;
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main () {
	Queue q(5);
	q.enqueue(31);
	q.enqueue(34);
	q.enqueue(45);
	q.enqueue(55);
	q.enqueue(77);
	q.dequeue();
	q.enqueue(83);
	q.enqueue(88);
	q.dequeue();
	q.dequeue();
	q.dequeue();
	q.dequeue();
	q.dequeue();
	q.dequeue();
	q.dequeue();	

	return 0;
}