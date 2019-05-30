/* Header file */
/* 
 *	The compiler, compiles each c file individually, it does not know if your
 *	function call types are passing the correct arguments
 *	which is why there is a prototype in the header
 *	so the compiler can refer to this header file the function calls
 *
 *	example:
 *	int readln(char[], int);
 *	int searchstring(char[], char[]);
*/

//prototype typedefs
typedef struct stack_t {
	short * start;
	int capacity;
	short * top;
}stack_t;


//here you can include macros
#define BUFFSIZE 100

//Function prototypes - only require the data type not the parameter names
void kill_s(stack_t *s); 
void kill_s (stack_t *s);