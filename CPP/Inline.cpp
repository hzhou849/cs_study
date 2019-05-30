/*inline functions 
 *
 * inline functions c++ 11 help improve execution time
 * by replacing the function call with the function code itself.
 * think, like a macro and fucntion call is the placeholder
*/

example:
inline void func1() {
	// some code from funct1

}
before:
int main() {
	//call a function
	func1() // compiler will replace this call with the function code above
}

after:
int main () {
	// some code from funct1

}