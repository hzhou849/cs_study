/* Custom Deleters 
 * 
 * Sometimes, when we destroy a pointer we need more than just destroy the object on the heap
 * These are special use cases 
 * C++ allows you to provide custom deleters
 * can't use make_shared or make unique when you create your smart pointer objects.
 *  bc these objects don't support that
 * 
 * ex custom deleter function
 * 
 * 	void custom_deleter(some_class *raw_pointer) {
 * 		// your custom delete code
 * 		delete raw_pointer;
 * 	}
 * 
 * shared_ptr<some_class> ptr {new Some_class{}, custom_deleter};  // provide the deleter function on declaration
 * 
 * ex 2: using lambda expression - this way we write the function right where we need to use it inline.
 * -- The idea is that the deleter code will execute right when the pointer is destroyed.
 * shared_ptr<Test> ptr (new Test{100}), [] (Test *ptr) {
 * 		std::cout << "\tusing my custom deleter" << std::endl;
 * 		// any other code I want to run in this embedded lambda function
 * 		delete ptr;
 * 
 * });
 * 
 * 
*/

#include <iostream>
#include <memory>

class Test {
private:
	int data;
public:
	Test(): data(0) { std::cout << "Test Constructor: " << data << std::endl;}
	Test(int data): data{data} {std::cout << "Test constructor: "<< data << std::endl; }
	int get_data() const {return data;}
	~Test() {std::cout << "test destructor" << data << std::endl;}
};

void my_deleter(Test *raw_ptr) {
	std::cout << "Using custom delete function" << std::endl;
	delete raw_ptr;
}

int main() {
	// artificial scope used here
	{
		//using a function
		std::shared_ptr<Test> ptr1 {new Test{100}, &my_deleter}; // must use 'new' for this not make_shared
	}
		// Using lambda expression
	{
		std::shared_ptr<Test> ptr2{new Test{2},
		[] (Test *ptr) {
			// this will exeucte when pointer is about to be destroyed
			std::cout << "Using custom lambda deleter" << std::endl;
			delete ptr;
		}};
	}
}
