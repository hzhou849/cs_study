#ifndef _ITEM_HPP_
#define _ITEM_HPP_
#include <iostream>
#include <chrono>

class Item {
	//overload stream operators for output
	friend std::ostream &operator << (std::ostream &os, const Item &rhs);
	// friend std::istream &operator >> (std::istream &in, Item &rhs);
private:
	std::string _name;
	int _price;
	std::chrono::seconds _cook_time;
public:
	Item(std::string name, int cost, std::chrono::seconds cook_time);
	~Item();
};


//Item.cpp
Item::Item(std::string name, int price, std::chrono::seconds cook_time)
	: _name{name}, _price{price}, _cook_time{cook_time} {
}

Item::~Item() {}



//overloaded ostram operator
std::ostream &operator<<(std::ostream &os, const Item &rhs) {
	os << "Name: "<< rhs._name << "; Price: "<< rhs._price << "; Cook Time: " << rhs._cook_time.count();
	return os;
}
#endif //_ITEM_HPP_