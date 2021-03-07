// Shared Pointers
// 
// Most of the stuff is the same with Unique pointers except you can share and copy with shared pointers
//


#include <iostream>
#include <memory>
#include <vector>


int main (int argc, char *argv[])
{
	{
		// C++11 prefered more efficient for the compiler, it can create it in one shot 
		std::shared_ptr<int> p1 = std::make_shared<int>(100); 	// use_count: 1
		std::shared_ptr<int> p2 {p1};						// use_count: 2
		std::shared_ptr<int> p3;
		p3 = p1;											// use_count: 3

		// All three of these pointers point to the SAME object in the heap!
		// When the use_count drops to 0, the heap object is deallocated.
	}

	{
	// use_count - the number of shared_ptr objects managing the heap object
		std::shared_ptr<int> p1 {new int {100} };
		std::cout << p1.use_count() << std::endl;		// 1

		std::shared_ptr<int> p2 {p1};					// shared ownership

		std::cout << p1.use_count () << std::endl;		//2

		p1.reset();										// decrement the use_count; p1 is nulled out

		std::cout << p1.use_count() << std::endl;		// 0
		std::cout << p2.use_count() << std::endl;		// 1
	}
	// Automatically deleted

	{
		std::vector<std::shared_ptr<int>> vec;
		std::shared_ptr<int> ptr {new int {100} };

		vec.push_back(ptr);			// OK - copy IS allowed with shared pointers

		std::cout << ptr.use_count() << std::endl; // 2 
	}
	// Automatically deleted



	

}