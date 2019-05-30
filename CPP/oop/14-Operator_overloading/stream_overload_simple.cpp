/* Function templates
 * 
 * allows for generic Function and classes
 * allow pluggin-in any data type.
 * 
 * write by using placeholers - like a blueprint, compiler generates
 * appropriated function/class from the blueprint
 * (this happens in compile time, not runtime to allow benefit of typechecking before the program executes)
 * 
 * Generic programming/ meta-programming
 * we provide generic representation of a fucntion and cpp writes it for us.
 * 
 * ex suppose we want to write a function to handle multiple data types
 * ie: traditional way
 * int max(int a, int b){
 * 	return (a > b) ? a:b;
 * }
 * 
 * double (double a, double b) {
 * 	return (a>b) ? a:b;
 * }
 * 
 *  Using function templates, we can just write a blueprint
 * - this will not compile, we need to explicitly tell the compiler this is a template function
 * 
 * template <typename T> // or template <class T>
 * T max(T a, T b) {
 * 	return (a>b) ? a:b; 
 * }
 * - code is still not generated yet, user has to use template keyword first: 
 * to use template
 * 1) must declare and init values
 * int a {10};
 * int b {20};
 * 
 * std::cout << max<int>(a,b);		// the < > angle brackets tells the compiler to generate code from the template were using
 * std::cout << max<double> (c,d);
 * std::cout << max(c,d);			// **Often, the compiler will know which type automatically based on datatype passed.
 * 
 * std::cout << max<char>('A', 'Z')
 * 
 * 
 * You can also mix data types
 * 
 * template <typename T1, typename T2>
 * void func(T1 a, T2 b) {
 * 	std::cout << a << b<< std::endl;
 * } 
 * 
 * 
 */

#include <iostream>

template <typename T> 
T max (T a, T b) {
	return (a > b) ? a:b;
}

template <typename T3>
T3 min (T3 a, T3 b) {
	return (a < b) ? a:b;
}

template <typename T1, typename T2>
void func (T1 a, T2 b) {
	std::cout << a <<" "<< b << std::endl;
}

struct Device{
	std::string name;
	int number;

	// OVerloaded operators
	//Method 1 - using friend
	friend std::ostream &operator<<(std::ostream &outstream, const Device &rhs) {
		outstream << "Name: "<<rhs.name << " number: " <<rhs.number;
		return outstream;
	}
	
	bool operator<(const Device &rhs) const { //overload the '<' operator
		return this->number < rhs.number;
	}
	bool operator>(const Device &rhs) const {
		return this->number > rhs.number;
	}
};


// //Method 2 - if not using friend must move the overloaded function to outside external function
// std::ostream &operator<<(std::ostream &outstream, const Device &rhs) {
// 	outstream << "Name: "<<rhs.name << "number: " <<rhs.number;
// 	return outstream;
// }

int main() {
	Device d1 {"device1", 1};
	Device d2 {"device2", 2};
	Device d3 = max(d1, d2); // this comparison cannot be may, operator needs to be overloaded to work.

	std::cout << d1 << std::endl;
	std::cout << "d3: " << d3<<std::endl;

	//test the templates
	func<int, int>(10, 20);
	func(10,20);
	func("A", "B");
	func (1000, "Testing");
	func (2000, std::string{"somethign"});
	func (d1, d2);
}

