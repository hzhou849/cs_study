#ifndef _Threadpool_HPP_
#define _Threadpool_HPP_


#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include "Order.hpp"
#include "Item.hpp"

class Threadpool {
private:
	std::vector <std::thread*> threads;	// using ptrs so we don't copy the threads itsef into the queue. just addressses
	std::queue<Item> q_tasks;
public:
	Threadpool();
	~Threadpool();
	void add_process_queue(std::vector<Order> order);

};

Threadpool::Threadpool() {}
Threadpool::~Threadpool(){}

void Threadpool::add_process_queue(std::vector<Order> order) {
	std::queue<Item> q_tasks;
}



#endif //_Threadpool_HPP_