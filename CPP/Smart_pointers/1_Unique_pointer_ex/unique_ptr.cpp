// Unique Pointer Examples
//

#include <iostream>
#include <memory>
#include <vector>

class testClass
{
private:
	friend std::ostream &operator<< (std::ostream &os, const testClass &inputObj);

public:
	testClass(std::string name, double amount);
	~testClass();
	std::string name;
	int amount;
};

testClass::testClass(std::string name, double amount)
{
	this->name = name;
	this->amount = amount;
}

testClass::~testClass() 
{
	std::cout << "testClass destroyed!" << std::endl;
}

std::ostream &operator<< (std::ostream &os, const testClass &inputObj)
{
	 os << inputObj.name << "; " << inputObj.amount;
	 return os;
}



int main(int argc, char *argv[])
{
	/* Ex 1 - create a new pointer and initialize value to 100 */
	{

		std::unique_ptr<int> p1 { new int {100} };
		std::cout << *p1 << std::endl; // 100

		*p1 = 200;

		std::cout << *p1 << std::endl; // 200
	}
	//automatically deleted out of scope


	/* Example 2 */
	{
		std::unique_ptr <int> p1 {new int {100} };
		std::cout << p1.get() << std::endl;		// address ie.0x564388

		p1.reset(); // p1 is now a nullptr

		if (p1)
			std::cout <<  *p1 << std::endl;	// won't execute
	}
	// automatically deleted


	/* Example3 - Cannot copy pointers, only move */
	{
		std::vector < std::unique_ptr<int> > vec;
		std::unique_ptr<int> ptr { new int{100} };

		// vec.push_back(ptr); // ERROR! Copy not allowed

		vec.push_back( std::move(ptr) ); // ptr gives up owner ship to the vector
	}
	// automatically deleted when vector goes out of scope

	std::unique_ptr<int> tt (new int);
	*tt = 100;

	// std::unique_ptr<int> t33 = std::make_unique<int>(100);// c++ 14

	std::unique_ptr<int> t1 { new int {100} };
	std::unique_ptr<int> t3;

	t3 = std::move(t1);

	if (!t1)
		std::cout << "t1 is a nullptr" << std::endl;

	std::vector<std::unique_ptr<testClass>> vec;
	
	std::unique_ptr<testClass> tempPtr {new testClass {"tester", 3000 }};

	vec.push_back(std::unique_ptr<testClass>{new testClass{"Bob", 1000}});
	vec.push_back(std::unique_ptr<testClass>{new testClass{"James", 2000} } );
	// vec.push_back(std::unique_ptr<testClass>(tempPtr)); 				// notice we cannot share this pointer bc it is unique. we must move it
	vec.push_back(std::unique_ptr<testClass>(move(tempPtr)));			// Ownership is transfered so we can store it in the vector

	// for (auto p : vec ) // *ERROR we cannot refernce this pointer bc it is doing a copy
	// we have to do it by refernce - const to protect it
	for (const auto &p : vec )
	{
		std::cout << *p << std::endl;  // notice we have to use a pointer dereference here
	}
	

	return 0;

}