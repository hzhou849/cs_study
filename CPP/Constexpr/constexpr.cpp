/*
 *
 * Const vs Const expression
 * 
 */

#include <iostream>

class classObj
{
public:
	classObj();
	static const int c1;
	static constexpr int c2 = 1;

};
classObj::classObj()
{
	
}	

const int classObj::c1 = 0;		// const must be initialized here

int main()
{

	classObj co;
	
	std::cout << "c1 value: "<<classObj::c1 << std::endl;
	return 0;
}
