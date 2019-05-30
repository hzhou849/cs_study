/* C++ Standard template libraries 
 *
 * - Essentially Data structures that can store objects of 
 *   almost any type. - implemented as template base classes
 * -Each container has member functions
 *  *some are specific to each container
 *  *others are available to all containers
 * 
 * 	- Each container has its own associated header file
 *    #include <container_type>
 * 
 * **specific containers have their own additional functions
 * Common methods provided by STL containers (functionalities provided)
 *  	Default constructor	- initializes empty container
 * 		Overloaded Constructors
 * 		copy constructors	- initializes containers as a copy of another
 * 		Move constructors	- moves existing container to new container
 * 		Destructor			- self explanatory, clean up
 * 		Copy assignment		- (operator =) copies..
 * 		Move assignment		- (operator = ) move instead of copy
 * 		size				- returns number of elements in container
 * 		empty				- returns boolean if empty?
 * 		insert				- Insert an element into the container
 * 
 * 		Operator < <=		- Returns boolean comparisons
 * 				> >=
 * 				== !=
 * 		swap				- swap elements of 2 containers
 * 		erase				- remove element(s) from container
 * 		clear				- remove all
 * 		begin/end			- returns Iterators of first and end
 * 		rbegin/rend			-returns reverse iterators
 * 		cbegin/cend			-returns constant iterators to first element or end?
 * 		crbegin/crend		-returns constant reverse iterators...""""
 * 
 * 	What types of objects can be stored in container?
 * 	All primitive types are ok
 * A copy of element will be stored in the container
 * must contain the following functions or overload operators:
 * 1) copy/movable and assignable.
 * 2) must have comparision.
 * 
 * -YOUR objects must be Copyable and assignable.
 *  - you may have to overload your own copy/move operators
 *  or Move for efficiency
 * 
 * - YOur objects must  support comparisions
 * 
*/