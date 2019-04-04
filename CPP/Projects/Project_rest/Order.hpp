#ifndef _ORDER_HPP_
#define _ORDER_HPP_

#include <iostream>
#include <queue>
#include <vector>
#include "Menu.hpp"

class Order {
private:
	std::vector<Item> vecOrder;
	int item_counter;
public:
	Order();
	~Order();
	void addOrder(Item i);
	void orderedItems();
	int get_item_counter();
	void decrement_counter();
	

};

Order::Order(): item_counter{-1}  {}
Order::~Order() {}

void Order::addOrder(Item i) {
	item_counter++; // increment the item counter
	this->vecOrder.push_back(i);
}
void Order::orderedItems() {
	std::cout << "\nOrdered Items: " << std::endl;
	for (auto &oi : vecOrder) {
	std::cout << "[ "<< oi << " ]" << std::endl;
	// for (auto i = var.begin(); i !=var.end(); i++) {
	// 	std::cout << (*i) << std::endl;
	// }
	} 
}

int Order::get_item_counter() {
	std::cout << "Item counter: " << item_counter << std::endl;
	return item_counter;
}

void Order::decrement_counter() {
	if (item_counter <= 0 ) {
		std::cout << "Cannot decrement. Item counter is at 0. " << std::endl;
	} else {
		int previous_count {0};
		previous_count = item_counter--; //post fix, assign then decrement item counter
		std::cout << "Item counter decremented. Prev: " << previous_count << " now: " << item_counter << std::endl;   
	}
}





#endif //_ORDER_HPP_