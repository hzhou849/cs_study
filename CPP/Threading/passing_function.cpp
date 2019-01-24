/* http://www.cplusplus.com/forum/general/73423/*/


#include <iostream>
#include <functional> // std::function


// external function that takes no parameters an does nothing used to pass it along 
void func1() {
	std::cout<<"in global func1" << std::endl;

}

class Processor {
public: 
	Processor();
	~Processor();
	int value;
	void memberFunc();
	void CallAFunc(std::function <void()> f_arg);
};


Processor::Processor(): value{0} {}
Processor::~Processor() {}

void Processor::memberFunc(){
	std::cout << "in memberFunc. value: " << value << std::endl;
}

void CallAFunc(std::function <void()> f_arg) {
	f_arg();	// call it normally
}

int main() {
	// call global function
	CallAFunc(func1); 

	// call a member function - more complicated
	Processor p;
	p.value = 10;

	CallAFunc(std::bind(&Processor::memberFunc, std::ref(p) ));
	return 0;
}



// Method 2
void f(int a, int b) {
	std::cout << "a: " << a << " b: " << b << std::endl;
}


void callit( std::function< void(int) > ptr )  // note our 'ptr' only takes 1 parameter
{
  ptr( 10 );  // passing '10' as the parameter
}

int main()
{
  callit( std::bind( f, std::placeholders::_1, 20 ) );  // prints "a = 10, b = 20"
}


//method 3 - ugly pointer magic...
static void function1( char* c ) {
    printf( "%s", c );
}

void function2( void* ptr ) {
    void(* func)(char*) = (void(*)(char*))ptr;
    func( "a" );
}

int _tmain(int argc, _TCHAR* argv[])
{
    void* f = function1;
    function2( f );
    return 0;
}