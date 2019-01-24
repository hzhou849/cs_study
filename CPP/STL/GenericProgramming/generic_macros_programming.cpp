/* *
 * C++ STL generic programming
 * uses the c++ preprocessor directives 
 * preprocessor doesn't know compiler syntax and symantics of c++
 * 
 * AVOID using preprocessor macros, and try to use C++ fucntion templates
 * 
 * 
 * using macros:
 * #define MAX(a,b) ((a>b) ? a: b)
 * 
 * std::cout << MAX(10,20) << std::endl; 	//20
 * std::cout << MAX('A', 'C') << std::endl; // C
 * 
 * 
 * Macros are blind substitution.
 * problem can arise if you try to compile macros
 * ex2
 * 
 * #define SQUARE(a) a*a
 * 
 * result = SQUARE(5);		//Expect 25
 * result = 5*5				// Get 25
 * 
 * result = 100/ SQUARE(5)		// Expect 4
 * result = 100/5*5				// Get 100! 
 * reason? cpp will blind subsitute and the equation will be processd as:
 *  result = (100/5) * 5 => 100
 * 
 * solution to this is to use '()' parenthesis to wrap up everything - best practice
 * #define SQUARE(a) ( (a) *(a) )
 * result = SQUARE(5); 		//Expect 25
 * result = ( (5)*(5) )		// get 25
 * 
 * result = 100/SQUARE(5)	// Expect 4
 * result = 100/((5)*(5))  // get 4
*/