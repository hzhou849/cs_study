/* 18.7 Override specifier
 *
 * Override specifier- used in conjunction with virtuals
 *  should be used everytime you plan to override a derived class
 *  lets you know if something is wrong during compile
 * - remember redefining a function is (writing a new version in a derivided class)
 *   will only statically bind. not dynamic
 * - bc c++ compiler sees a function with a diff signature, it will be consisdered redefined.
 *      allows us to make new versions of the same name function ie different signature etc..
 * 
 *  - allows compiler to know you are overriding and not redefining.
 *  - by adding the override specifier keyword, it will let you know in compile warning if a function
 *    is not being called properly
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_
/* Examaple 1 */
// class Base {
// public:
// 	virtual void say_hello() const {
// 		std::cout << "hello - I am a Base class object" << std::endl;
// 	}
// 	virtual ~Base() {}

// };

// class Derived: public Base {
// 	virtual void say_hello() { // Notice I forgot the const -THIS IS REDEFINING, NOT OVERRRIDING THIS WILL STILL COMPILE BC IT IS LEAGAL

// 		std::cout << "Hello - I am a Dervived class object" << std::endl;
// 	}
// 	virtual ~Derived() {}
// };

/* Example 2  - with OVERRIDE*/
class Base {
public:
	virtual void say_hello() const {
		std::cout << "hello - I am a Base class object" << std::endl;
	}
	virtual ~Base() {}

};

class Derived: public Base {
	// Will now produce commpiler error to let you know the intended function marked override
	// is marked override but does not override
	virtual void say_hello() override { 

		std::cout << "Hello - I am a Dervived class object" << std::endl;
	}
	virtual ~Derived() {}
};


#endif //_DEVICE_H_


/*Device.cpp */

int main() {
	/* bc the function signature was not the same, it is treated as a 
		redefintion and will not be dynamically bound and the dervied->sayhello will not be called
	*/
	Base *p1 = new Base();
	p1->say_hello();			// "Hello - I am Base object"

	Base *p2 = new Derived();
	p2->say_hello				// "Hello - I am Base object"

}

