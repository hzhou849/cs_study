#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <iostream>
#include "Item.hpp"

class Menu {

	public:
		Item filletMignon() {
			return Item("Fillet Mignon", 30, std::chrono::seconds(5));
		}
		Item burger() {
			return Item("Burger", 10, std::chrono::seconds(2));
		}
		Item fries() {
			return Item("Fries", 5, std::chrono::seconds(1));
		}
		Item salmonRoll() {
			return Item("Salmon Roll", 10, std::chrono::seconds(3));
		}
		Item tunaRoll() {
			return Item("Tuna_Roll", 8, std::chrono::seconds(3));
		}
};


#endif