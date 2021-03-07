class Test 
{
public:
	Test(): data{0}
	{
		std::cout << "Test Constructor.." << data << std::endl;
	}

	Test (int data): data{data}
	{
		std::cout << "Test Constructor overloaded" << std::endl;
	}

	int get_data() const {
		return data;
	} 

	// Overload the ostream operator
	friend std::ostream& operator << (std::ostream& os, const Test& test)
	{
		os << "test overloaded:  " << test.data;
		return os;
	}
	
	~Test() 
	{
		std::cout << "Deleting object..." << std::endl;
	}

private:
	int data;
	
};

// std::ostream& std::operator<<(std::ostream& os, const Test& test)
// {
// 	os << "test" << test.get_data();
// 	return os;
// }


int main() 
{
	/*Raw Pointers */
	// Test t1{1000};
	Test *t1 = new Test{1000}; // heap allcoation
	// delete t1; 					// free heap allocation
	std::cout << "data os overload: " << *t1 <<std::endl;
