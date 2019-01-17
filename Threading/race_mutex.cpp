#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

/* Race condition, in this scenario if the mutex is commented, you can see the thread race will become 
   unpredictable, but with the mutex, it will run in an orgainized thread execution.
   thread 1 and thread 2 both share the data variable and will race to be the first to retrieve it. 
   with the mutex, it will be organized.
*/
#ifndef _COUNTER_H_
#define _COUNTER_H_

// Counter.hpp
class Counter {
private:
	int data;
	std::mutex mutexObj;		// create a mutex object
public:
	Counter();
	int getData();
	void addData(int value);
};

#endif //_COUNTER_H_

//Counter.cpp
Counter::Counter(): data{0} {}

int Counter::getData() {
	return data;
}

void Counter::addData(int value) {
	for (int i=0; i < 100; i++) {
		mutexObj.lock(); // acquire the mutex lock
		this->data = value;
		std::cout << "data: " << data << std::endl;
		mutexObj.unlock(); //release the mutex
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
};

// int runTest(int element) {
// 	Counter countObj;
// 	std::thread thread1(&Counter::addData, &countObj, element);
// 	std::thread thread2(&Counter::addData, &countObj, element+1);
// 	std::this_thread::sleep_for(std::chrono::microseconds(700));
// 	thread1.join();	// wait for thread to rejoin.
// 	thread2.join();

// 	return 0;
// }

int main() {
	int max = 100;

	// the order will not be exact, but every cycle will include one of each thread 
	Counter countObj;
	std::thread thread1 (&Counter::addData, &countObj, 1);
	std::thread thread2 (&Counter::addData, &countObj, 2);
	std::thread thread3 (&Counter::addData, &countObj, 3);
	std::thread thread4 (&Counter::addData, &countObj, 4);

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	return 0;
}


