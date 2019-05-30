/* C++ Generic classes/ Class templates 
 *
 * -the class template is a generic blueprint the compiler uses
 *  to create specialized classs, thats what meta-programming is all about
 * -Allows plugging-in any data type
 * -Compiler generates athe appropriate class from the blueprint
 * 
 *	//example1:
 *	//we have a class with with name and an integer
 *	
 *	class Item {
 *	private:
 *		std::string name;
 *		int value;	
 * 	public:
 * 		Item(std::string, int value)
 * 			:name{name}, value {value} {
 * 		}
 * 		std::string get_name() const {return name;}
 * 		int get_value() const {returh value;}	
 * 	};
 * 
 * 	but now we like our Item class to hold a different 
 *  type of data other than a string, what can we do?
 * 
 * 	REmember:
 * 	-we can't overload class names
 *  - we don't want to use dynamic polymorphism
 * 
 * 	we can use class template to write the blueprint
 * 
 * //generic class item
 * template <typename T>		// tells the compiler this is a template class
 * class Item {
 * private:
 * 		std::string name;
 * 		T value;		 	// placeholder for generics
 * public:
 * 		Item(std::string name, T value)
 * 			:name{name}, value {value} {
 * 		}
 * 		std::string get_name() const {return name;}
 * 		T get_value() const {return value;}
 * 
 * };
 *
 * To Create instances of items: - compiler will take care of generating
 * --------------------------------
 * 	Item<int> item1 {"name", 1};
 * 	Item<double> item2 {"House", 1000.0};
 * 	Item<std::string> item3 {"Frank", "Boss"};
 * 	std::vector<Item<int>> vec;		// vector that holds items object of type int
 * 
 * 	example2: - different types
 * ----------------------------
 * 	template <typename T1, typename T2>
 * 	struct My_Par {
 * 		T1 first;
 * 		T2 second;
 * 	};
 * 
 * My_pair <std::string, int> p1 {"Frank", 100};
 * My_par <int, double> p2 {124, 13.5};
 * std::vector<My_pair<int, double>> vec;
 * 
 * std::pair - this 'My_pair' concept already exists only 2 items
 * -------------------------------------------------
 * #include <utility>
 * std::pair <std::string, int> p1 {"frank", 100};
 * std::cout << p1.first;		// frank
 * std::cout << p2.second;		//100
 * 
 * see also TUPLE - allows fixed # of elements of anytype
 * 
 * 
 * // template if no args constuctor
 * class bitConvert
{
private:
	uint8_t mask;
	std::string binaryValue;

public:
	bitConvert();
	~bitConvert();
	

template <typename T>  ** here is the template
	void convertHex ( T inputHex );
	
};

#endif //_BITCONVERT_

bitConvert::bitConvert()
{
	// initialize values
	this->mask = 1;			
	this->binaryValue = "";
}

bitConvert::~bitConvert()
{

}

template <typename T>  ** here is the template
void  bitConvert::convertHex ( T inputHex  )
	{
		int size = ( sizeof (T) * 16 ) -1;		// 2 bytes 0-15
		std::cout << "size of T: " << size << std::endl;

		T temp;
		int counter = 0;
		for (int i = size; i >=0; i-- )			// popping off MSB first
		
	}
 */ 

#include <iostream>
#include <string>
#include <vector>

#include <iostream>

template <typename T> //  if the constuctor doesn't need args, 
//move this line to the generic fucntion
class Gqueue {
private:
	short *start;
	T	  *value;	// passing pointer to the object not copying
	short *eq;
	short *dq;
	int bufferSize;
public:
	Gqueue(int b);
	void init2();
	~Gqueue();
};

/*  *** when you have seperate method definitons, 
 * you MUST incldue template declearation in each method definition
*/
template <typename T>  // re-declare
Gqueue<T>::Gqueue(int b) 
	:start{nullptr},value{nullptr}, eq{nullptr}, dq{nullptr}, bufferSize{b} {

}
template <typename T> // re-declare
Gqueue<T>::~Gqueue() {
	// de-allocate heap queue
	delete[] start;
}
template <typename T> // re-declare
void Gqueue<T>::init2() {
	std::cout << " init" << std::endl;
}


//Template classes are typically completely contained in header files
// in item.h, there is no item.cpp associated with it.

//item.h
template<typename T>
class Item {
private:
	std::string name;
	T value;
public:
	Item (std::string name, T value)
		:name{name}, value {value} {

	}
	std::string get_name() const {return name;}
	T get_value() const {return value;}
};

template <typename T1, typename T2>
struct My_Pair {
	T1 first;
	T2 second;
};


int main() {
	
	// Example 1
	Item <int> item1 {"Frank", 100};
	std::cout << item1.get_name() << " " << item1.get_value() << std::endl;

	Item <std::string> item2 {"frank", "professor"};
	std::cout << item2.get_name() << "" << item2.get_value() << std::endl;

	//Item <datatype> var
	// in this case the data type is the Item object
	Item < Item <std::string> >item3 {"frank", {"c++", "professor"}};
	std::cout << item3.get_name() << " "	// "frank"
			<< item3.get_value().get_name()  // T2 holds an item object. so T2 == .get_value() which has a get_name() and get_value() 
			<< item3.get_value().get_value() // think T2=get_value() or T2=get_value().get_value() 
			<<std::endl;

	
	// Vectors
	std::vector<Item<double>> vec {};
	vec.push_back(Item<double> ("device1", 100.0));
	vec.push_back(Item<double> ("device2", 200.0));
	vec.push_back(Item<double> ("device3", 300.0));

	for (const auto &item: vec) {
		std::cout << item.get_name() << "" << item.get_value() << std::endl;
	}

	// exampl3
	My_Pair <std::string, int> p1 {"frank", 100};

	std::cout << p1.first << p1.second << std::endl;
	return 0;
}