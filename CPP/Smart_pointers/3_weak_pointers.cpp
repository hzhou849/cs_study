/* Weak pointers 
 *
 * Provides no owning "weak" reference
 * - points to an object of T type on heap
 * - Does not participate in owning releationship
 * - Always created from a weak pointer
 * - Does not increment or decrement reference use_count()
 * - used to prevent strong reference cyccels which could prevent objects from being deleted.
 * - just "vists them temporarily"
 * 
 * weak_ptr - circular or cyclic reference
 * A refers to B, B referes to A - shared strong ownership prevents heap deallocation.
 * 
 * A(shared_ptr<B>) -> B(shared_ptr<A>
 * A(shared_ptr<B> <- B(shared_ptr<A>
 * 
 *  stack 				heap (not arrays, this is a box with use counter)
 * a[] --->          A[1]--> B[]
 * b[] --->          B[1]-->A[]  (if this is a weak ptr, it will break the circular reference)
 * 
 * will result in memory leak, chicken in egg problem. when this goes out of scope, they will
 * be destroyed on the stack but not on the heap and we will have a memory leak problem
 * a keeps b alive, b keeps a alive.
 * 
 * Solution:
 * - make one of the pointers a non-owning or 'weak' pointer
 * - now heap will be deallocated properly
 * 
 * A(shared_ptr<B>) -->  B (weak_ptr<A>)
 * 					<--
*/
#include <iostream>
#include <memory>



//demo of the chicken and egg scenario

class B; // forward declaration - because compiler needs to know it exists for us to write A (like a prototype)

class A{
private:
	std::shared_ptr<B> b_ptr;
public:
	void set_B(std::shared_ptr<B> &b) {
		b_ptr = b;
	}
	A() {
		std::cout << "A Constructor" << std::endl; 
	}
	~A() {
		std::cout << "A destructor.." <<std::endl;
	}
};

class B {
private:
	// std::shared_ptr <A> a_ptr;  // make weake to break the strong circular reference
	std::weak_ptr <A> a_ptr;
public:
	void set_A (std::shared_ptr<A> &a) {
		a_ptr =a;
	}
	B() {
		std::cout << "B Constructor" << std::endl;
	}
	~B() {
		std::cout << "B destructor" << std::endl;
	}
};


int main() {
	// std::shared_ptr<A> a = std::make_shared<A>();


	std::shared_ptr<A> a {new A {}};
	std::shared_ptr<B> b {new B {}};

	a->set_B(b);
	b->set_A(a);

	return 0;

}
