/* Std::exception class heirarchy
 *
 * c++ provides a class hierarchy of exception classes
 * - std::exception is the base class
 * - all subclasses implement the what() virtual function
 * - we can create our own user-defined exception subclasses.
 * 
 * virtual const char *what() const noexcept;
 * 
 * 'noexcept' - keyword tagged on function signature means no exceptions are thrown in that function,
 * 				if it occurs, program will error and exit. no handling
 */

#include <iostream>
#include <memory>

// method 1 - minimal features, bare object
// class  IllegalInputException{
// public:
// 	IllegalInputException() = default;  // tagging default tell compiler to use default con/destructor
// 	~IllegalInputException() = default;
// };

//method2 - using std::exception
class IllegalInputException : public std::exception {
public:
	IllegalInputException() noexcept = default;
	~IllegalInputException() = default;

	virtual const char* what() const noexcept {
		return "Illegal input exception";
	}
};

class Application {
private:
	std::string name;
	double value;
public:
	Application(std::string name, double value);
	~Application();
};

Application::Application(std::string name, double value) 
	: name{name}, value{value} {

		if (value < 0.0) 
			throw IllegalInputException{};
	}
Application::~Application() {}



int main() {

	try {
		std::unique_ptr<Application> app_ptr {new Application{"app1", -1.0}};
	}
	catch (const IllegalInputException &ex) {
		std::cerr << ex.what() << std::endl; // displays the virtual what() method return statement we wrote 
	}
	return 0;
}