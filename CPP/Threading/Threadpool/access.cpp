#include <iostream>
#include "Queue.hpp"

class Access {
public:
	int value;
	friend class Queue;
	Access();
	~Access();

	void test_function();
};

Access::Access(): value{0} {}
Access::~Access(){}

void Access::test_function() {
 	Queue q{5};
	q.enqueue(31);
	q.enqueue(44);
}

int main() {
	int value;
	
	Access a;
	a.test_function();
	return 0;
}