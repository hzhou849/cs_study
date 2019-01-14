#include <iostream>


// queue.hpp
#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

class queue {
public:
	short *start;
	int capacity;
	short *eq;
	short *dq;
	~queue();
	
	// Constructor
	queue(int size_limit);

	//implement a queue init
	// int q_init(queue *q, int capacity); // construtor in C
	int enqueue(queue *q, int element);
	int dequeue(queue *q, short *element);
	void display (queue *q);
};
#endif // _QUEUE_HPP_

short *myShortArray = new short[5];
//queue.cpp
// #include queue.hpp
queue::queue (int size_limit) {
	capacity = size_limit;
	start = new short[size_limit]; 
	eq = start;
	dq = start;
}


int queue::enqueue (queue *q, int element) {
	if (q == nullptr) {
		return -1;
	}
	if (element == 0) {
		return -2;
	}

	*(q->eq) = element;

}

