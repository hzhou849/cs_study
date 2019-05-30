/* Exceptions handling 
 * 
 * Usually we use exception handling when a function throws an error and the
 * function we created has no idea what to do with it.
 * 
 * - if exception handler exists, c++   will unwind the stack to look for the catch function
 * - if c++ cannot find the appropiate type handler, it will go up the call stack and pop off  until it
 *   either finds one or program terminates and exception is not handled.
 * 
 * - during stack unwind, best to use RAII or organize destructors accordingly to prevent memory leaks. 
 *   bc if the function gets popped off the stack, all its local variables get destroyed along with it.
 * 
 * - Class Level Exceptions:
 *   Exceptions can be thrown within a class.
 * 	a) Method - these work the same way as they do for function as we've seen.
 * 	b) Constructor - constructors may fail.
 * 					- Constructors do not return a value
 * 					- Throw an exception in the constructor if you cannot initialize an object.
 * 	c) Destructor	- DO NOT throw exceptions in the destructor!
 * 
*/
#include <iostream>
// #include <string>
// #include <exception>

double calc_function(int a, int b) {
	if ( b== 0) {
		throw 0;		// throw here
	}
	if ( a <0 || b <0) {
		throw std::string {"negative value error"};
	}
	return static_cast<double>(a)/b;

}
int main() {
int value;
	try {
		calc_function(1, 0);
		std::cout<< "blah" << std::endl;
	}

	catch (int &e) { 	// always catch by reference, that is the best practice we are catching int in this case.
		std::cerr << "exception caught" << e << std::endl;
	}
	catch (std::string &ex) {  // string exception caught
		std::cerr << "condition 2" << ex << std::endl; 
	}
	catch (...) {	// generic catch block for all data types but you will NOT have access to the exception object!
		std::cerr << "Unknown exception" << std::endl;
	}

	std::cout<< "program continues" << std::endl;
	return 0;
}