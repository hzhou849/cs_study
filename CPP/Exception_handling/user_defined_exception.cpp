/* User defined Exceptions 
 *
 * Create own exception classes and throw instances of those classes
 * 
 * Best practice:
 * - throw object not a primitive type
 * - thrown and object by value
 * - catcn and object by reference (or const reference)
 *
 * ex:
 * if (a == 0)
 * 	throw DivideByZeroException();
 * 
 * catch (const DivideByZeroException &ex) {
 * 		std::cerr << "message" << std::endl;
 * }
 * catch (const NegativeValueException &ex) {
 * 		std::cerr << "message" << std::endl;
 * }

 */

#include <iostream>

class DivideByZeroException{
};
class NegativeValueException{
};

double calc_function(int a, int b) {
	if ( b== 0) {
		// throw 0;
		throw DivideByZeroException();		// throw here
	}
	if ( a <0 || b <0) {
		// throw std::string {"negative value error"};
		throw NegativeValueException();
	}
	return static_cast<double>(a)/b;

}
int main() {
int value;
	try {
		calc_function(1, 0);
		std::cout<< "blah" << std::endl;
	}

	// catch (int &e) { 	// always catch by reference, that is the best practice we are catching int in this case.
	// 	std::cerr << "exception caught" << e << std::endl;
	// }
	// catch (std::string &ex) {  // string exception caught
	// 	std::cerr << "condition 2" << ex << std::endl; 
	// }
	// catch (...) {	// generic catch block for all data types but you will NOT have access to the exception object!
	// 	std::cerr << "Unknown exception" << std::endl;
	// }
	catch(const DivideByZeroException &ex) {
		std::cerr << "error message" << std::endl;
	}
	catch (const NegativeValueException &ex) {
		std::cerr <<"error message" << std::endl;
	}

	std::cout<< "exit normally" << std::endl;
	return 0;
}

