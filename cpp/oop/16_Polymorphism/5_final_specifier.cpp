/* 188 - final specifier
 *
 * C++ 11 provides the final specifier
 * When used in CLASS level, prevents a class from being dervided from
 * ensures objects are copied safely without slicing
 * final classs -better compiler optimization
 * 
 * When used in METHOD level
 * Prevents virtual method from being overridden in dervided classes.
 * better compiler optimization
 * 
 * 
 * 
 */
  
 //Example final class - compiler will generate a compiler error if try to dervive from final

 class My_class final {	 // cannot derive from this point on 

 };

 class Dervived final: public Base {	// if specified here, cannot dervive from this point on

 };


 //Example final method.

class A {
public:
	virtual void do_something();

};

class B: public A{
	virtual void do_something() final;	//prevent further overriding further down in heirarcy and produces error
};

class C: public B {
	virtual void do_something();		// compiler Error - Cannot override.
};
