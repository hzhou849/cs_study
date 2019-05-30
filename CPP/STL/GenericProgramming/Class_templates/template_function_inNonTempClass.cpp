/*
 * Template Function in non-template class
 *
 * 
 * With templates, you cant split the code into .h and .cpp 
 * files like you can with non-templates without export which 
 * virtually no compiler supports, or ever will, though comeau does.
 * When you include the .h in a file and try to use the templated 
 * function, the compiler tries to instantiate the template 
 * substituting the generic type(s) for specific type(s) but 
 * it cannot do that unless it can see the definition of the template.
 * 
 * 
 * From what I know, 
 * 
 * 
 * 
 * 
 * in order to get a templated function in a NON templated class to 
 * work, you keep the templated function definition in the .h header file 
 * 
 * since CPP files get processed at link time, and headers at compile
 * time, Basically templates need to processed at compile time.
 */


// Example:

/* someClass.hpp */
class someClass 
{
public:
	someClass();
	~someClass();
	void nonTemplatedFunc();
	template <typename T> void templatedFunc( T input );
};
// Templated definitions stay in hpp
template <typename T> void someClass::templatedFunc( T input )
{

}


/* someClass.cpp */
someClass::someClass()
{

}

someClass::~someClass()
{

}

void someClass::nonTemplatedFunc() 
{

}

// writing the templated function definition 
// here will cause a compile error.
// template <typename T> void someClass::templatedFunc( T input )
// {

// }

