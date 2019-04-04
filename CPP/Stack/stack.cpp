/* 
 * 
*/
#include <iostream>
#include <thread>
#include <chrono>

//stack.hpp
#ifndef _STACK_H_
#define _STACK_H_
class stack {
public:
	int capacity;
	short *start;
	short *top;
	int ret_value;

	//constructor
	stack();

	//member functinos
	int init(int capacity);
	int push(int element);
	int pop ();
	void display();
	~stack();
};
#endif //_STACK_H_

//stack.hpp
// #include <iostream>

//constructor
stack::stack(): capacity{0}, start{nullptr}, top{nullptr}, ret_value{0} {}

int stack::init(int capacity) {
	if (capacity == 0) {
		return -1;
	}

	this->capacity = capacity;
	this->start = new short[capacity]; // malloc heap space
	this->top = this->start;
	display();
	return 0;
}

int stack::push(int element){
	// input validation
	if (element == 0) {
		return -1;
	}
	if (this->top == (this->start + this->capacity)) {
		std::cout << "stack full" << std::endl;
		return -2;
	}

	*(this->top) = element;
	std::cout << "address: " << this->top << " value:" << *(this->top) << std::endl;
	this->top ++;
	display();

	return 0;
}

int stack::pop () {
	if (this->top == this->start) {
		std::cout << "Stack is empty." << std::endl;
		return -1;
	}

	// decerement the top ptr first 
	this->top --;
	this->ret_value = *(this->top); // deref the top pointer.
	*(this->top) = 0;				// "Erase" the data
	display();

	return 0;
}

void stack::display() {
	short *temp_addr = this->start;
	std::cout << "\033[s";	//save cursor position
	// std::cout << "\033[7A";
	std::cout << "\033[2J";	// Clear the screen
	std::cout << "\033[u";	//restore cursor position
	std::this_thread::sleep_for(std::chrono::seconds(1));
	while (temp_addr <= (this->start + this->capacity)) {
		if (this->top == temp_addr ) {
			std::cout << "<top>   ";
		} else {
			std::cout << "\t";
		}
		std::cout << "address: " << temp_addr << " value: " << *temp_addr <<std::endl;
		temp_addr++; 
	}
	


}

stack::~stack() {
	//make sure you use "delete []" this is an array of memory on heap
	delete[](this->start);
}


//main.cpp
int main () {
	stack s;
	s.init(5);
	s.push(31);
	s.push(42);
	s.push(55);
	s.push(61);
	s.pop();
	s.pop();
	s.push(72);
	s.push(85);

	return 0;
}



