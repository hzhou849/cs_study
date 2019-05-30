/* STL - Iterators 
 *
 * implemented as template classes
 * Allows abstracting an arbritrary container as a sequence of elements
 * They are objects that work like pointers by design
 * Most containers classes can be traversed with iterators
 * 
 * Declaring Iterators
 *  - must be declared based on the type of container type
 *    they will iterate over
 * 
 * container_type::iterator_type iterator_name;
 * 
 * std::vector<int>::iterator it1;
 * std::list<std::string>::iterator it2;
 * std::map<std::string, std::string> it3;
 * std::set<char>::iterator it4;
 * 
 * example: std::vector<int> vec {1,2,3}
 * [ 1,  2,  3,  [] ]
 *   ^           ^
 * vec.begin()   |
 *            vec.end() - location after last element
 * 
 * to get the first element:
 * 	std::vector<int>::iterator it = vec.begin();
 *  or shorthand
 *  auto it = vec.begin(); 	// compiler deduces the type based on return of vec.begin
 * 
 * 
 * Operations with Iterators
 * -------------------------
 * ++it 			- pre-increment    - All iterators support this operation
 * it++				-Post incre				All
 * it = it1 		- assignemtn			All
 * *it				-dereference			Input / Output
 * it->				-Arrow operator			I/O
 * it == it1		comparison
 * --it  it--      pre postfix				bidirectional
 * it +i it+=i     increment/decrement		Random access
 * it < it1, it <= it1 comparison			Random access
 * 
 *  
 * 
 * Example: Using iterator to display vector
 * std::vector<int> vec {1,2,3};
 * 
 * std::vector<int>::iterator it = vec.begin(); // initialize to the first element
 * while (it != vec.end()) {
 * 	std::cout << *it << " ";		// dereference the iterator
 *  ++it;
 * }
 * 
 * or 
 * 
 * for (auto it = vec.begin()); it !=vec.end(); it++) {
 * 		std::cout << *it << " ";
 * } // 1 2 3
 * 
 * 
 * Example: iterate through a set of char
 * 
 * std::set<char> suits {'C', 'H', 'S', 'D'};
 * 
 * auto it = suits.begin();		// let the compiler determine type
 * 
 * while (it != suits.end()) {
 * 		std::cout << *it << "" << std::endl;
 * 		++it;
 * }
 * // C H S D
 * 
 * 
 * Example  REVERSE iterator
 * std::vector<int>::reverse_iterator it = vec.begin(); // **NOTE:begin is the last element
 * 
 * 		still use ++it; to increment, it will be au
 * 		--it moves forward
 * 