/*
 * CLI/ CLR C++ Programming project
 *
 * Key CLI Syntax concepts
 * 
 * 'ref'				= Added before class designation for CLI/CLR
 *							- ie: ref class <class_name>{};
 * 
 *  '^' aka carot; hat	= handle to object operator - objects only! 
 *							- This designates a pointer to be exclusively managed by the .NET auto Garbage collector
							- This passes control to CLI for managing and cleaning up objects
 *							- Also replaces * for pointers
 *							- ie: Object^ objVar = gcnew Object;
 *								  delete p;			// CLI make cleanup optional, since it manages object Garbage collection for you. 
 *							- Does use R!{} as its own destructor class
 *   'gcnew'				= replaces 'new' when allocating memory, no parenthesis()
 *
 *	 
 * Pointer Arithmatic      - Increment/decrement operations does not work on ^ handle operators
 *						   - you also cannot convert int ^p = array (will not work)
 *						   - you will need a set of *pointers and ^ pointers
 * 
 * Finalizer Destructors '!myClass()' 
 *							- Automatically gets called if 'delete' is not used 
 *							- declare in Protected access specifier 
							- Aka Finalizer class
							- File cleanup by CLI can be overridden by using 
							   ~myClass() does not get called
 * 
 * Knowing when to use the ^ hat is super-duper important, hard to make progress in C++/CLI when that's still murky. 
 * bool and double are value types, not object types, and variables of those types must therefore 
 * NOT be declared with ^. With the hat, it becomes a boxed copy of the value (System.ValueType under the hood) 
 * and the compiler is liable to lose its marbles badly.
 * 
 * NativeObject* n = new NativeObject();
ManagedObject^ m = gcnew ManagedObject();
 */


#pragma once
#include <iostream>
#include <vector>


ref class AdamsHal
{
public:
	AdamsHal();
	~AdamsHal();
	!AdamsHal();

	void testSleep(double^ time);
	int getChannelData(std::vector<double> *inputVec);
	int getChannelDataFixed(std::vector<double> *inputVec);
	
private:
	static int instanceCounter = 0;

};

