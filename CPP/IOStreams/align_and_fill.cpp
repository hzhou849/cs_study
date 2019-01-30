/* Stream manipulators - align and fill 
 *
 * Default whe displaing floating point values is:
 * setw - not set by default
 * left - when no field width, right  - when using field width
 * fill - not set by default - blank space is sused
 * 
 * some of these manipulators affect only the next data element put on the stream
*/

#include <iostream>
#include <iomanip>

int main() {
	double num {1234.5678};
	std::string hello {"Hello"};

	std::cout << num << hello << std::endl;

	// will display "1234.57Hello"


	
	/* using setw will right justify the spacing by number of spaces passed in arg ie 10 
	 *  ** note only the next item (num in this case) is will be justified not the whole string
	 * sets right justified (all items passed will end at arg1)
	 */
	std::cout << std::setw(10) << num <<hello << std::endl;

	/*1 2 3 4 5 6 7 8 9 0 1 2 3 4 5...
	 *      1 2 3 4 . 5 7 H e l l o  // the last char in 'num' the '7' is at space 10, hello is unaffected 
	 *  							 // notice on the num variable passed is affected with std::setw

	 */




	// Filling  spaces - requires a setw() in order to work

	std::cout << std::setfill('-');
	std::cout << std::setw(10) << num << hello << std::endl;  //dispaly "---1234.57Hello"


	// field justification - left justified
	//1234567890 ruler
	//1234.57***Hello
	std::cout << std::setw(10) << std::left << num << hello << std::endl; // only affects num
}