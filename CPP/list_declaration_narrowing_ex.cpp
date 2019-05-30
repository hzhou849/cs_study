#include <iostream>

using namespace std;    // Use the entire std namespace
using std::cin;         // Use only what you need
using std::cout;
using std::endl;

int main() {
   
   
    /*list declaration allows narrowing check 
     *
     * main.cpp:12:42: error: narrowing conversion of ‘9966217342047006033I128’ from ‘__int128’ to ‘long int’ inside { } [-Wnarrowing]
     * long var_a{11111111111111111110077777};
     * prevents narrowing ie from long to in or in this case
     * _int128 to int 64
	 * 
	 *  Compile will warn you of possible truncation.

	 * List initialization does not allow narrowing (§iso.8.5.4). That is:
	 * 
	 * An integer cannot be converted to another integer that cannot hold its value. For example, char to int is allowed, but not int to char.
	 * A floating-point value cannot be converted to another floating-point type that cannot hold its value. For example, float to double is allowed, but not double to float.
	 * A floating-point value cannot be converted to an integer type.
	 * An integer value cannot be converted to a floating-point type.
     */
    long var_a{11111111111111111110077777};
    std::cout<< "var_a:"<< var_a << endl;

    

    return 0;
}

// List initialization constructors
https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/
 * 
 * list intitialization constructor is used:
 * bc list initialization is done immediately it offers benefits:	
 * 1) For initialization of non-static const data members:
		const data members must be initialized using Initializer List. 
		In the following example, “t” is a const data member of Test class 
		and is initialized using Initializer List.

	2) For initialization of reference members:
		Reference members must be initialized using Initializer List. In the following example, 
		“t” is a reference member of Test class and is initialized using Initializer List

	3) For initialization of member objects which do not have default constructor:
		In the following example, an object “a” of class “A” is data member of class “B”,
		 and “A” doesn’t have default constructor. Initializer List must be used to initialize “a”.

	4)For initialization of base class members : Like point 3, parameterized constructor of 
		base class can only be called using Initializer List.

	5)When constructor’s parameter name is same as data member
		If constructor’s parameter name is same as data member name then the data 
		member must be initialized either using this pointer or Initializer List. In the following example, both member name and parameter name for A() is “i”.

	6) For Performance reasons:
	It is better to initialize all class variables in Initializer List instead of assigning values inside body. 

		traditional method:
		/ Without Initializer List 
		class MyClass { 
		    Type variable; 
		public: 
		    MyClass(Type a) {  // Assume that Type is an already 
		                     // declared class and it has appropriate  
		                     // constructors and operators 
		      variable = a; 
		    } 
		}; 
		Here compiler follows following steps to create an object of type MyClass
		1. Type’s constructor is called first for “a”.
		2. The assignment operator of “Type” is called inside body of MyClass() constructor to assign
		3. And then finally destructor of “Type” is called for “a” since it goes out of scope.
			Now consider the same code with MyClass() constructor with Initializer List
			
		// With Initializer List 
		class MyClass { 
		    Type variable; 
		public: 
		    MyClass(Type a):variable(a) {   // Assume that Type is an already 
		                     // declared class and it has appropriate 
		                     // constructors and operators 
		    } 
		}; 
		With the Initializer List, following steps are followed by compiler:
		1. Copy constructor of “Type” class is called to initialize : variable(a). 
			The arguments in initializer list are used to copy construct “variable” directly.
		2. Destructor of “Type” is called for “a” since it goes out of scope.

		As we can see from this example if we use assignment inside constructor body there 
		are three function calls: constructor + destructor + one addition assignment operator call. 
		And if we use Initializer List there are only two function calls: 
		copy constructor + destructor call. See this post for a running example on this point.
		This assignment penalty will be much more in “real” applications where there 
		will be many such variables. Thanks to ptr for adding this point.