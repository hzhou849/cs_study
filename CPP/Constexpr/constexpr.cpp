/*
 *
 * Const vs Const expression
 * 
 * 
 *  1) difference is that Const needs to be defined aboved main
 * 
 * 2)before c11 you could not call a function where a Const was expected
 * 3) Constexpr lets the compiler know something exist so when you call it during compile
      it will know what you are referring to .
 * 
 */

#include <iostream>

class classObj
{
public:
	classObj();
	static const int c1;
	static constexpr int c2 = 1; // constexpr can be defined in here

};
classObj::classObj()
{
	
}	


//Scenario 2
//int factorial( int n )		// should not work?

// this will be evaluated on compile time. invoked on compile time.
constexpr int factorial(int n)  // now the compiler will know what this is on compile time.
{
	auto result = 1;
	for (auto i = 1; i <=n; ++i)
		result *=i;
	
	return result;
}
const int classObj::c1 = 0;		// const must be initialized here

int main()
{

	classObj co;
	
	std::cout << "c1 value: "<<classObj::c1 << std::endl;


	// scenario 2
	//if we are trying to initalize an array, this would not work
	// bc the compiler does not know the size of the array yet.
	int a[factorial(2)] = {};



	return 0;
}


