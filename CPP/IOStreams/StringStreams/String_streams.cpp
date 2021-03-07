/* C++ - String streams
 *
 * Strings streams allows us to use in-memory strings objects as streams
 * meaning we can read and write data to strings in the same way we can read/write
 * data to any stream
 * 
 * - Allows us to read/write from strings in memory much as we would read/write to files
 * - very powerful
 * - very useful for data validation
 * 
 * three classes when using string streams:
 * -----------------------------------------
 * 1) stringstream - allows both read and write
 * 2) istringstream - read only (INPUT)
 * 3) ostringstream - write only (OUTPUT) - has its out .str() method that is an internal string buffer
 * 
 * to use:
 * 	1) #include <sstream>
 *  2) Declare a string stream object
 *  3) connect it to a std::string variable
 *  4) read/write data from/to the string stream using formated I/O


MEMORY leak in loops be careful. Similar to +=.
use oss.str("") to reset the memory otherwise memory leak!!!!
	std::string string_value;
	std::stringstream oss;
	while (!s_interrupted)
	{
		oss.str(""); // reset string stream to prevent memory leak.
		m_disp.reset_cursor_pos();


	oss.clear() // clears and resets any flags ie std::hex etc..
 */





#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <string>

int main() {

	// example 1: - read from istring stream object
	int num {};
	double total {};
	std::string name {};
	std::string info {"Moe 100 1234.5"};

	std::istringstream iss {info};
	iss >> name >> num >> total;  // name = "Moe", num = 100, total = 1234.5

	std::cout << name << num << total << std::endl;


	// example 2: write to ostringstream object

	int num2 {100};
	double total2 {1234.5};
	std::string name2 {"Moe"};

	std::ostringstream oss {};
	oss << num2 << " " << name2 << " " << total2;

	std::cout << oss.str() << std::endl;


	// example: data validation from stringstream
	// checks to see if user input is an integer and not character
	int value{};
	std::string input {};

	std:: cout << "Enter an integer: " ;
	std::cin >> input;

	std::stringstream ss{input}; // bind the input into a stringstream object
	if (ss >> value) 			// extract the value from the string stream object
		std::cout << "An integer was entered" << :: std::endl;
	else
		std::cout << "Conversion to int failed, and int was NOT entered" << std::endl;


	// example 1 - string extraction - INPUT std::istringstream iss {info};
	iss >> name >> num >> total;
	std::cout << "\n12345678901234567890 - Istringstream" << std::endl;
	std::cout << std::setw(10) << std:: left << name
				<<std::setw(5) << num
				<<std::setw(10) << total <<std::endl;

	// example 2 - Ostringstream - OUTPUT

	std::ostringstream oss2{};
	std::cout << "\n12345678901234567890 - Ostringstream" << std::endl;
	oss2 << std::setw(10) << std:: left << name
		<<std::setw(5) << num
		<<std::setw(10) << total <<std::endl;
	std::cout << oss2.str() << std::endl;

	// Example 3 - imporved data validation algorithm
	// this will loop until a valid input is received ie an int value
	std::cout << "\n-----Data validation ver2 -----------------" << std::endl;

	int value_a {};
	std::string entry {};
	bool done = false;

	/* note if you enter a decimal 12.38, the 12 will get extracted and .38 will stay in the buffer
	 * you must flush the buffer after otherwise the .38 might get printed with next printout
	 */
	do {
		std::cout << "Please enter an integer: "<<std::endl;
		std::cin >> entry;
		std::istringstream validator {entry};
		if (validator >> value_a) //if validator(entry value) can be extraced by value (or get converted to int)
			done = true;
			// std::cout << entry<< std::endl;
		else
			std::cout << "not a valid integer, try again" << std::endl;
			// std::cout << entry << std::endl;
		
		// discards the input buffer - requires #include <limits>
		// translation  ->using numeric limits upto the std::streamsize(max) until '\n' character is reached
		// read the max number of the streamsize to look for the '\n' and ignore (delete)all of it for next time
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // means ignore everything upto '\n'

	} while (!done);

}
