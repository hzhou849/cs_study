#include <iostream>
#include "Menu.hpp"
#include "Order.hpp"


int main() {
	Menu m;
	Item item1 = m.filletMignon();
	Item item2 = m.burger();
	Item item3 = m.tunaRoll();
	std::cout << item1 << std::endl;
	std::cout << item2 << std::endl;
	std::cout << item3 << std::endl;

	Order order1;
	order1.addOrder(item1);
	order1.addOrder(item2);
	order1.addOrder(item3);

	order1.orderedItems();
	order1.get_item_counter();
	order1.decrement_counter();
	order1.decrement_counter();
	order1.decrement_counter();

	order1.get_item_counter();


	return 0;
}