/*
 * Enum Classes and Overrideing ostream to print them. - CPP
 *
 *
 * Enum class syntax
 * Usage:
 * 	enum class someObj { obj1, obj2, obj3}
 * 
 *  to call you need the namespace
 * 	someObj::obj1
 *  someObj::obj2 etc..
 * 
 * NOTE: to display enum classes, you need to override the << operator
 * 		bc it does not know how to display it. 
 *  OR you can static_cast<unsigned int>(enumtype) << to your stream
 * 
 * The problem with traditional enums:
 * 	Enums are user-defined lists
 *   the problem arises because behind the hood, C
 * 	 stores the enum elements as integers in a 0-index
 * 
 * example
 * enum color { red, green , blue};
 * 
 * behind the hood, red=0, green=1, blue=2;
 * 
 * 
 * enum class Foo : uint16_t 
{
  Bar,
  Baz,
  Bork,
};
 * 
#include <type_traits> 

std::underlying_type<Foo>::type v = 10; //v is uint16_t
 * 
 */

#include <iostream>

/* Traditional ENUM */
// cannot have second enum with same elements
// compile error - bc scope collision
enum color {red, green, blue};
// enum color2 {red, green, blue, black};	

/* Enum Classes */
enum class someObj: uint16_t { obj1, obj2, obj3 };


/* OSTREAM overrides */
// Method 1
// Fixed ostream override to a specific enum class 
std::ostream& operator << (std::ostream& os, const someObj& objArg)
{
	os << static_cast<std::underlying_type<someObj>::type>(objArg);
	// os << static_cast<std::underlying_type<A>::type>(obj);
	return os;
}

// Method 2
//Templated ostream override to be reused for multiple enum class overrides 
//enable if only type enum
template <typename T>
std::ostream& operator << (typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& objArg )
{
	return stream << static_cast < typename std::underlying_type<T>::type>(objArg);
}

// This function takes enum or integers since they are the same behind the hood
void display(int input) 
{
	switch(input)
	{
		case red   : std::cout << "red"   << std::endl; break;
		case green : std::cout << "green" << std::endl; break;
		case blue  : std::cout << "blue"  << std::endl; break;
	}
		// requires ostream override
		std::cout << "input: " << input << std::endl;  //prints 0,1,2 ...n order of enum passed
}

// enum class display tightly binds the arg types passed
// can only accept enum class
void ec_display(someObj input) 
{
	switch(input)
	{
		case someObj::obj1 : std::cout << "obj1 passed" << std::endl; break;
		case someObj::obj2 : std::cout << "obj2 passed" << std::endl; break;
		case someObj::obj3 : std::cout << "obj3 passed" << std::endl; break;
	}
		std::cout << "numerical position representation - input: " << input << std::endl;
		//or if no override you can do this.
		std::cout << static_cast<unsigned int>(input) << std::endl;
}






int main() 
{
	
	/* Using traditional enum */
	// c1 stores 'red' or '0'
	color c1 = red;								
	
	std::cout << "c1: " << c1 << std::endl;

	display(red);
	display(1);		// you can spoof the function by injecting numbers
	// compile error, cannot re-assign enums
	// int red =2;				


	/* Using enum classes */
	ec_display(someObj::obj2);





}

