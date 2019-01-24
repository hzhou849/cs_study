/* Smart Pointers 
 *
 * usage: must use {} list declaration
 * std::unique_ptr<type> ptr {new type {arg1, arg2, etc..}}
 * 
 * Unique_ptr<T>
 * - points to object of type T
 * - is unique, can only be one unique_ptr<T> pointer to the object in the heap
 * - owns what it points to 
 * - cannot be assigned or copied
 * - CAN be moved
 * - when pointer is destroyed when out of scope, what it points to is automatically destroyed
 * 
//  *  * unique pointers can be used to allocate arrays of objects on a heap, shared pts do not support this by default??verify

 * 
 *  ptr.get()  - returns the raw address
 * 	ptr.reset() - sets pointer to nullptr
 * 	new_ptr = std::move(ptr) - new_ptr now owns pointer, and ptr is set to null
 * 	ptr.release() - releases ownership of associated raw pointer from object. returns raw poniter
 * 
 *  ex.
 * {
 * 	std::unique_ptr<int> p1 {new int {100}};
 * 	std::cout << *p1 << std::endl; //100
 * 
 * 	*p1 = 200
 * 	std::cout << *p1 << std::endl; // 200
 * } 	// automatically deleted.
 * 
 * ex.2
 * {
 * 	std::unique_ptr<int> p1 {new int {100}};
 * 	std::cout << p1.get() << std::endl; // 0x564388 returns pointer to managed object in case you need a raw pointer
 * 
 * 	p1.reset(); // p1 is now set to 'nullptr'
 * 
 * 	if (p1) {	// check initialization 
 * 		std::cout<< *p1 << std::endl; // won't execute	
 * 	}
 * } automatically cleaned up.
 * 
 * 
 * ex.3 call user defined types
 * 	std::unique_ptr<account> p1 {new Account {"something"}};
 * 	std::cout << *p1 << std::endl;		// display account
 * 
 * p1 ->deposit(1000);
 * p1 ->withdraw (500);
 * 
 * 
 * ex.4 vector and move. - Unique pointers cannot be copied but CAN be moved
 * 	std::vector <std::unique_ptr<int>> vec;
 * 	std::unique_ptr<int> ptr {new int {100}};
 * 
 * 	vec.push_back(ptr); 		// error - copy not allowed
 * 
 * 	// in this case, ptr gives up ownership of the pointer, and is moved to the vector.
 * 	//vector now owns the pointer, and ptr = nullptr. when vector goes out of scope, 
 *  // it will be deallocated accordingly
 * 	vec.push_back(std::move(ptr));	//move ok
 * */

#include <iostream>
#include <memory>
#include <vector>

class Test {
private:
	int data;
public:
	Test(): data{0} {
		std::cout << "Test constructor: " << data <<  std::endl;
	}
	Test(int data): data{data} {
		std::cout << "Test constructor: " << data << std::endl;
	}
	int get_data() const {
		return data;
	}

	~Test() {
		std::cout << "Deleting object..." << std::endl;
	}

};

int main() {

	/* Raw pointers */
	// Test t1 {1000};
	// Test *t1 = new Test{1000};	// heap allocation
	// delete t1;	// free heap memory.

	/* Unique pointers */
	std::unique_ptr<Test> t1 {new Test{1010}};		// c++ 11
	
	
	// std::unique_ptr<Test> t2 = std::make_unique<Test>(1000);		// c++ 14
	// std::unique_ptr<Test> t3 {new Test()};

	// t3 = t1;	// result in error as you don't have access to '=' operator to copy 

	// t3 = std::move(t1); // t1 moves to t3, t3 owns pointer now and t1 is set to nullptr

	// if(t1 == nullptr) {
	// 	std::cout << "t1 is now nullptr, t3: " << t3->get_data() << std::endl;
	// }

	/*Test with dynamic polymorphism */
	// std::unique_ptr<Base> ptr1 {new Derived{1000}};
	// std::cout << *a1 << std::endl; // requires overloaded iostream operator '<<'
	// ptr1->member_function(500);


	/* Vectors */
	// std::unique_ptr<Test> t4 {new Test{22}};
	// std::vector<std::unique_ptr<Test>> t_vec1;
	// // t_vec1.push_back(t1); // will not compile bc you are copying
	// t_vec1.push_back(t4); // will not compile
	// t_vec1.push_back(std::move(t4));

	// for (auto const &list: t_vec1) {
	// 	std::cout << list->get_data() << std::endl;
	// }

	std::unique_ptr<int> point {new int {22}};
	std::vector<std::unique_ptr<int>> vec1;
	// vec1.push_back(point);		// wilkl not compile error copy
	vec1.push_back(std::move(point));

	for (auto &list: vec1) { 	// 'list' needs to hold a pointer
		std::cout << *list << std::endl; // dereference *list
	}
	
	return 0;
}

