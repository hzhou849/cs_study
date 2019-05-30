/* Shared pointers 
 *
 * Points to an object of type T on the heap
 * it is NOT unique- there can be many shared pointers pointing to the same object on heap
 * Establishes shared ownership relationship
 * 
 * CAN be assigned and copied.
 * CAN be moved.
 * 
 * Doesn't support managing arrays by default
 * unique pointers can be used to allocate arrays of objects on a heap, shared pts do not support this by default
 * When the use_count() is zero, the managed objected on the heap is destroyed. ie using a reference counter
 * 
 * ex1:
 * {
 * 	std::shared_ptr<int> p1 {new int {100}};
 * 	*p1 = 200;
 * 	std::cout << *p1 << std::endl; // 200
 * } // garbage collection auto deleted
 * 
 * ex 2: use_count() - returns the number of shared_pts objects managing the heap object
 * {
 * 		std::shared_ptr<int> p1 {new int {100}};
 * 		std::cout << p1.use_count() << std::endl; 		// 1
 * 
 * 		std::shared_ptr<int> p2 {p1};					// Shared ownership
 * 		std::cout << p1.use_count() << std::endl;		// 2
 * 
 * 		p1.reset();										// decrement the use count; p1 is nulled out.
 * 		std::cout << p1.use_count() << std::endl;		// 0
 * 		std::cout << p2.use_count() << std::endl;		//1;
 * }	// auto clean up
 * 
 * 
 * ex 3: shared_pointers can be copied, assigned and moved.
 * {
 * 		std::vector<std::shared_ptr<int>> vec;
 * 		std::shared_ptr<int> ptr {new int{100}};
 * 	
 * 		vec.push_back(ptr);			// OK copy IS allowed
 * 		std::cout << ptr.use_count() << std::endl;		//2 - ptr heap object is being pointed to by bother 'ptr' and vec[0]
 * }	automatically deleted.
 * 
 * ex 4. Make_shared (c++ 11) 
 * {
 * 		std::shared_ptr<int> p1 = make_shared<int>(100);		// use_count : 1
 * 		std::shared_ptr<int> p2 {p1};							// use_count : 2
 * 		std::shared_ptr<int> p3;								// does not point to anything yet
 * 		p3 = p1;												// use_count : 3
 * }	// auto cleanup
 * - Use make_shared if can, it is more efficeint - compiler generates more efficeint code and passes the value into the constructor directly
 * - All 3 pointers point to the SAME object on the heap
 * - when use_count == 0, heap object is deallocated.
 * - p1 will be responsible for cleanup since stack order of destruction is p3, p2 then p1
 * 
 * 
 *  test function to check for use count. takes a shared pointer as arg
 * void func(std::shared_ptr<Test> p ) {	// this is a copy, use count should be +1 until this func is out of scope
 * 		std::cout << "Use count: " << p.use_count << std::endl;
 * }
*/

#include <iostream>
#include <memory>
#include <vector>

void funct(std::shared_ptr<int> p) {
	std::cout << "Use count: " << p.use_count() << std::endl;
} 

int main() {
	std::shared_ptr<int> ptr = std::make_shared<int>(100);
	funct(ptr);
	std::cout << "current: " << ptr.use_count() << std::endl;	
	{
		std::shared_ptr<int> ptr1 = ptr;
		std::cout << "current: " << ptr.use_count() << std::endl;
		{
			std::shared_ptr<int>ptr2 = ptr;
			std::cout << "current: " << ptr.use_count() << std::endl;	
			ptr.reset();
		}	
		std::cout << "current ptr1: " << ptr1.use_count() << std::endl;	
	}
	std::cout << "current: " << ptr.use_count() << std::endl;	


	std::shared_ptr <int> a1 {new int {100}};
	std::shared_ptr <int> a2 {new int {200}};
	std::shared_ptr <int> a3 {new int {300}};

	std::vector<std::shared_ptr<int>> vec;
	vec.push_back(a1);
	vec.push_back(a2);
	vec.push_back(a3);

	for (const auto &item: vec) {
		std::cout << *item << std::endl;
		std::cout << "use count: " << item.use_count() << std:: endl; // should be 2 each object  has 2 copies. original + vector object
	}
	

	return 0;
}