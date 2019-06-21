/* 
 * extern keyword
 * 
 *  by putting 'extern' keyword in front of a variable 
 * ie : 
 * 	extern int var;
 * then memory for that variable will NOT be allocated, var will
 * only be declared.
 * 
 * Therefore, we put extern explicitly for C variables 
 * when we want to declare them without defining them. 
 * 
 * Also, as the extern extends the visibility to the whole program, 
 * by using the extern keyword with a variable we can use the variables 
 * anywhere in the program provided we know the declaration of them 
 * and the variable is defined somewhere.
 * 
 * 1. A declaration can be done any number of times but definition only once.
 * 2. “extern” keyword is used to extend the visibility of variables/functions().
 * 3. Since functions are visible throughout the program by default. The use of extern is not needed in function declaration/definition. Its use is redundant.
 * 4. When extern is used with a variable, it’s only declared not defined.
 * 5. As an exception, when an extern variable is declared with initialization, it is taken as the definition of the variable as well.
 * 
 * 
 * example 1:
 * 		int var; 
 * 		int main(void) 
 * 		{ 
 * 		   var = 10; 
 * 		   return 0; 
 * 		}
 *  Here var is defined ( and declared implicitly) globally.
 * 
 * Example 2:
 *  extern int var;
 * 	int main(void)
 * 	{
 * 		return 0;	
 * 	} 
 * 
 *  Var is never used here and no problem on compile.
 * 
 * example 3:
 * extern int var;
 * int main(void)
 * {
 * 		var = 10;
 * 		return 0;
 * }	
 * this will not compile bc var is not defined anywhere and var has
 * no memory allocated to it. Program is trying to change the value of 10
 * of a variable that doesn't exist.
 * 
 * 
 * Example 
 * #include "somefile.h"  assuming extern in var is defined in this file
	extern int var; 
	int main(void) 
	{ 
	var = 10; 
	return 0; 
	} 
