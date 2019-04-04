#include <iostream>

//stack2.hpp
#ifndef _STACK2_HPP_
#define _STACK2_HPP_

class stack2 {
private:
	short *start;
	short *top;
	int capacity;
public:
	stack2(int size);
	~stack2();
	int push(int value);
	int pop();
	void printout();

};
#endif //_STACK2_HPP_


//stack.cpp

// constructor
stack2::stack2(int size): start{nullptr}, top{nullptr}, capacity{size} {
	this->start = new short[size];
	//c style- this->start = (short*)malloc(sizeof(short)*capacity);
	this->top = this->start;
	this->capacity = size;
}

stack2::~stack2() {
	delete[] (this->start);
}

int stack2::push(int value) {
	if (value == 0) {
		return -1;
	}

	if (this->top == (this->start + this->capacity)) {
		std::cout << "Stack full" << std::endl;
		return -1;
	}

	*(this->top) = value;
	this->top++;	
	return 0;
}

int stack2::pop() {
	int temp_value;

	if (this->top == this->start) {
		std::cout << "Stack empty" << std::endl;
	} else {
		this->top--; // decrement the top back to last entry
		temp_value = *(this->top);
		*(this->top) = 999;
		std::cout << "popped: " << temp_value << std::endl;
	}
	return temp_value;
}

void stack2::printout() {
	short *temp;
	temp = this->start;
 
	/*C++  
	  short * temp  - creates an variable on stack 0x7fffd19b9a20
	  pointer temp stores an address 0xff01
	 * &temp = 0x7fffd19b9a20 on stack value.
	 * temp = (this->start==0xff01);
	 * &(*temp) = this->start == 0xff01;
	 * 
	 */

	while (temp < (this->start + this->capacity)) {
		std::cout << "address: " << &(*temp) << " value: " << *temp << std::endl;
		temp++;
	}

}



int main() {
	int popped;
	stack2 s(5);
	s.push(31);
	s.push(42);
	s.push(59);
	s.pop();
	s.push(68);
	s.push(73);
	s.push(98);
	s.push(103);
	s.printout();

}