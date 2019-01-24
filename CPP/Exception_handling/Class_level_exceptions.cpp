#include <iostream>
#include <memory>

class  IllegalInputException{
public:
	IllegalInputException() = default;  // tagging default tell compiler to use default con/destructor
	~IllegalInputException() = default;
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

	}
	return 0;
}