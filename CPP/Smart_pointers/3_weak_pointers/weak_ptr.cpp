/* Smart Pointers - Weak Pointers
 *
 * 
 * Provides a non-owning "weak" reference
 *
 * usage:
 *	weak_ptr<T>
 *
 *  - Points to an object of type T on the heap
 *  - Does not participate in ownership relationships
 *  - Does NOT increment or decrement reference use_count()
 *  - Used to prevent strong reference cycles which could prevent objects from being deleted
 * 
 * 
 * 	why weak pointers useful?
 * lets say we have a circular or cyclic reference (like a deadlock)
 * A->B
 * A<-B 
 * 
 * When the go out of scope, the pointers will be deleted on the stack, but their
 * shared resoure on the heap will not be deallocated. -> memory leak!!!!
 * This shared strong ownership will prevent heap from being deallocated!
 * 
 * A cannot get destroyed because it will have a use_count of 1 (from b)
 * and B cannot get destroyed because it will have a use_count of 1 (From a) = deadlock
 * 
 * SOLUTION: make one of the pointers  weak pointer ie. A->B ; A<--weak_ptr--B
 *  - now the heap storage will deallocate properly
 */

#include <iostream>
#include <memory>

class B; // Forward declaration - lets the compiler know this prototype exists

class A
{
private:
	std::shared_ptr<B> b_ptr;

public:
	A();
	~A();
	void setB(std::shared_ptr<B> &b);
};

class B
{
private:
	// std::shared_ptr<A> a_ptr;  // original will cause memory leak circular reference
	std::weak_ptr<A> a_ptr;

public:
	B();
	~B();
	void set_A(std::shared_ptr<A> &a);

};


// cpp implementation
A::A()
{
	std::cout << "A Constructor" << std::endl;
}

A::~A()
{
	std::cout << "A Destructor" << std::endl;
}

void A::setB(std::shared_ptr<B> &b)
{
	b_ptr= b;
}



// Class B
B::B()
{
	std::cout << "B Constructor" << std::endl;
}

B::~B() 
{
	std::cout << "B Destructor" << std::endl;
}

void B::set_A(std::shared_ptr<A> &a)
{
	a_ptr = a;
}


// Main driver class
int main(int argc, char *argv[])
{
	// Notice when running this code, the destructor does not get called.
	// but when we modified one of the class pointers to weak_pointer, then the destructor will get called properly
	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();
	a->setB(b);
	b->set_A(a);

	return 0;
}