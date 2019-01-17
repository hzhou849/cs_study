/* Queue cpp
 * https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/
 * 
 * list intitialization constructor is used:
 * bc list initialization is done immediately it offers benefits:	
 * 1) For initialization of non-static const data members:

	2) For initialization of reference members:

	3) For initialization of member objects which do not have default constructor:

	4)For initialization of base class members : Like point 3, parameterized constructor of 

	5)When constructor’s parameter name is same as data member

	6) For Performance reasons:
	It is better to initialize all class variables in Initializer List instead of assigning values inside body. 

		traditional method:
		/ Without Initializer List 
		class MyClass { 
		    Type variable; 
		public: 
		    MyClass(Type a) {  // Assume that Type is an already 
		                     // declared class and it has appropriate  
		                     // constructors and operators 
		      variable = a; 
		    } 
		}; 
		Here compiler follows following steps to create an object of type MyClass
		1. Type’s constructor is called first for “a”.
		2. The assignment operator of “Type” is called inside body of MyClass() constructor to assign
		3. And then finally destructor of “Type” is called for “a” since it goes out of scope.
			Now consider the same code with MyClass() constructor with Initializer List

		// With Initializer List 
		class MyClass { 
		    Type variable; 
		public: 
		    MyClass(Type a):variable(a) {   // Assume that Type is an already 
		                     // declared class and it has appropriate 
		                     // constructors and operators 
		    } 
		}; 
		With the Initializer List, following steps are followed by compiler:
		1. Copy constructor of “Type” class is called to initialize : variable(a). 
			The arguments in initializer list are used to copy construct “variable” directly.
		2. Destructor of “Type” is called for “a” since it goes out of scope.

		As we can see from this example if we use assignment inside constructor body there 
		are three function calls: constructor + destructor + one addition assignment operator call. 
		And if we use Initializer List there are only two function calls: 
		copy constructor + destructor call. 

	short *myShortArray = new short[5];
*/
#include <iostream>
#include <thread>
#include <chrono>
	// start = new short[capacity];  c++ OOP malloc array in heap space

// queue.hpp
#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

class queue {
public:
	short *start;
	int capacity;
	short *eq;
	short *dq;
	int ret_value;
	~queue();
	
	// Constructor
	queue();
	int q_init(int capacity);
	//implement a queue init
	// int q_init(queue *q, int capacity); // construtor in C
	int enqueue (int element);
	int dequeue ();
	void display ();
};
#endif // _QUEUE_HPP_

//queue.cpp
// #include queue.hpp

// Constructor
queue::queue (): 	// list initialization better performance 
	start{nullptr}, capacity{0},  eq {nullptr}, dq {nullptr}, ret_value{0} {
}

int queue::q_init (int capacity) {
	
	if (capacity == 0) {
		return -2;
	}
	this->start = new short [capacity];
	this->capacity = capacity;
	this->eq = this->start;
	this->dq = this->start;
	// this->ret_value = new int; dont' need to make this in heap, object already isalready is.
	return 0;
}

int queue::enqueue (int element) {
	if (this->eq == (this->start + this->capacity)) { // *remember start + 5 = 6 spaces 
		this->eq --; // bring the eq back to the last address if passes limit
		std::cout << "Max capacity reached"<<std::endl;
		return -1;
	}
	if (element == 0) {
		return -2;
	}

	*(this->eq) = element;
	std::cout << "Enqueued - address: " << this->eq << " value: " << *(this->eq) << std::endl;
	this->eq++;	//increment the eq pointer;
	display();
	return 0;
}

int queue::dequeue() {
	if (this->dq == this->eq) {
		this->dq --;
		std::cout << "Queue is empty."<<std::endl;
	}

	(this->ret_value) = *(this->dq); // derefrence the address eq is pointing to.
	std::cout << "dequeued: " << (this->ret_value)<<" "<<(this->dq) << std::endl;
	*(this->dq) = 0;
	this->dq ++;
	display();
	return 0;
}

void queue::display() {
	short *temp_addr = this->start;
	
	std::cout << "\033[2J"; //clear the screen
	std::cout << "\033[7A"; // move cursor up x lines
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "eq: " << this->eq << " dq: " << this->dq << std::endl; 
	while (!(temp_addr >= (this->start + this->capacity))) {  // !(a >= b) same as (a !> b)
		if (temp_addr == this->eq) {
			std::cout << "<eq> ";
		}
		if (temp_addr == this->dq) {
			std::cout << "<dq> ";
		}
		if (temp_addr != this->eq || temp_addr != this->dq) {
			std::cout << "\t";
		}

		std::cout << "  address: " << *temp_addr << " value: " << temp_addr << std::endl;
		temp_addr++; // increment the address space
	}
}

queue::~queue() {
	delete(this->start); // free malloc memory space on heap
};

// main.cpp
int main() {
	queue q;
	q.q_init(5);
	q.enqueue(31);
	q.enqueue(42);
	q.enqueue(55);
	q.dequeue();
	q.dequeue();
	q.dequeue();
	q.enqueue(68);
	q.enqueue(72);
	q.enqueue(84);
	q.dequeue();
	q.dequeue();
	q.display();
	return 0;
}

