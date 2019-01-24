/* 109 - Pass by reference
 * 
 * Passing the refernce and not a copy of a variable in a function.
 * 
 * Pointers vs reference
 * 
 * pointers - A pointer variable that holds memory address of another variable. A pointer needs to be
 * 			dereferenced with * operator to access memory location it points to.
 * 
 * reference -ref variable is an alias ie. another name for an existing variable. A reference 
 * 			like a pointer is also implemented by storing the address of an object.
 * 			A ref can be thought of as a constant pointer(not to be confused with  a pointer to a constant value.)
 * 			with automatic indirection. ie the compiler will apply the * operator for you.
 */

//Example 1
void scale_number(int &num);		// prototype

int main() {
	int number {1000};
	scale_number(number);		//call
	std::cout << number << std::endl;		//100
}

void scale_number (int &num) {	// definintion. Behind the scences, you are taking the reference of 'number'
	if (num > 100)
		num = 100;
}

//Example 2 - Swap
// Pass by copy will not work bc the duplicate parameters will be lost when swap() looses scope.
void swap (int &a, int &b) {
	int temp = a;
	a =b;
	b = temp;
}

int main() {
	int x{10}, y{20};
	std::cout << x << "" << y << std::endl; //10 20
	swap(x, y);
	std::cout << x << "" << y << std::endl; //20 10

	return 0;
}