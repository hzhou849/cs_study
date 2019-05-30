/* C++ Generic arrays
 *
 * STL does have an array class
 * NOTE: since c++ 11, the STL has a std::array which is a template based
 * 		 array class, use std::array instead of raw arrays whenever possible
 * 
 * 		we should use std::array, or std::vectors 
 * 
 * we want to create our own, how do we pass the size of an array?
 * - we don't want to use new,
 * - and we can't pass it as an arg, bc it could be a value for the element?
 * - how to distinguish arg passed is for size?
 * 
  // we use "Non-type template parameters"
 *
 * 
 * 1. make it a template class
#include <iostream>
#include <string>

class Array {
	int size {N};		// how do we get 'N'???
	int values[N];		// N needs to be known at compile time.

	friend std::ostream &operator << (std::ostream &os, const Array &arr){
		os << "[";
		for (const auto &val: arr.values)
			os << val << "";
		os << "]" << std::endl;
		return os;
	}
public:
	Array() = default;
	Array(int init_val) {
		for (auto &item: values)
			item = init_val;	
	}
	void fill (int val) {
		for (auto &item: values)
			item = val;
	}

	int get_size() const {
		return size;
	}
}
 */
// solution 
// to make this a generic array, we need to make values generic 
// add typename T into template declaration and make values type T
#include <iostream>
#include <string>

template<typename T, int N> // defines N here at compile time
class Array {
	int size {N};		// how do we get 'N'???
	
	// int values[N];		// N needs to be known at compile time. 
	T values [N];			// now this is generic

	// displalys the array
	friend std::ostream &operator << (std::ostream &os, const Array<T,N> &arr){ //arg2 passing this object Array<N>
		os << "[";
		for (const auto &val: arr.values)
			os << val << "";
		os << "]" << std::endl;
		return os;
	}
public:
	Array() = default;
	Array(T init_val) {	// overloaded constructor
		for (auto &item: values)
			item = init_val;	
	}
	void fill (T val) {
		for (auto &item: values)
			item = val;
	}

	int get_size() const {
		return size;
	}

	// overload subscript operator for ease of use
	T &operator[] (int index) { 		// this return type is no longer an int, it is now a T
		return values[index];
	}
};

int main () {
	Array <int, 5> nums; 		// create and array of 5 ints
	std::cout << "size of num is:" << nums.get_size() << std::endl;

	nums.fill(0); 			// fills the arrays with '0's
	
	nums[0] = 1000;			// calls nums.operator[](0); returns 'value[index] = 1234'
	nums[3] = 2000;

	std::cout << nums << std::endl;

	Array<int,100> nums2 {1}; 	// initializing and array size 100  with '1's
	std::cout << "the size of num2 is:" << nums2.get_size() << std::endl;
	std::cout << nums2 << std::endl; // uses overloader << stream operator to printout the array

	Array <std::string, 10> string_arr(std::string{"Frank"});  //initialize with "frank"
	std::cout << "the size of num2 is:" << string_arr.get_size() << std::endl;
	std::cout << string_arr << std::endl;

	string_arr[0] = std::string{"new Text"};
	std::cout << string_arr << std::endl;

	string_arr.fill("X");		//fill with 'x's
	std::cout <<string_arr << std::endl;
	
	return 0;
}