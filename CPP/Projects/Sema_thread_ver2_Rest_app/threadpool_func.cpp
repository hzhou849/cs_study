
/* Threadpool class 
 * 
 * basic function passing, NO ARGSS
 * 
*/



#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <queue>
// #include "semaphore.hpp"

/* Semaphore class 
 *
 * 
*/
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

class Semaphore {
private:
	std::mutex sm_mutex;
	std::condition_variable sm_cv;
	int count;

public:
	Semaphore(): count {0} {}
	~Semaphore() {}

	void notify () {
		std::unique_lock<std::mutex>u_lock(sm_mutex); // attemp to acquire lock before accessing count
		count++;
		// std::cout << "Notify() Thread: " << tid << " notified() acquired" << std::endl;

		// notify the waiting thrad
		sm_cv.notify_one();
	}

	void wait(std::thread::id tid) {
		std::unique_lock<std::mutex>u_lock(sm_mutex);
		while (count == 0) {	// handles spurious wake ups
			std::cout << "Thread: " << tid << " wait" << std::endl;
			sm_cv.wait(u_lock); 	// wait on the mutex until notify is called.
			std::cout << "Thread: " << tid << " run" << std::endl;
		}

		count --;
	}
};



class Threadpool {
private:
	std::vector <std::thread*> threads;			// vector that holds thread pointer
	std::queue < std::function<void()> > q_tasks; //create a queue containter of std::function type items
	std::mutex tp_mutex;						// local mutex used to sync pushing work 
	Semaphore tpSemaphore;						// Create a semaphore object
	void workLoop();

public:
	Threadpool();			//constructor
	void addWork(std::function<void()>);		// accepts a function as an arg

};

//Constructor
Threadpool::Threadpool() {
	for (int i=0; i < 3; i++) {
		std::thread *t = new std::thread(&Threadpool::workLoop, this);
		this->threads.push_back(t);
	}
}

/* Threadpool loop */
void Threadpool::workLoop() {
	while (true) {
		this->tpSemaphore.wait(std::this_thread::get_id());

		// access the queue, assign the next element(function) to the temp_func
		this->tp_mutex.lock();
		std::function<void()> temp_func = this->q_tasks.front();
		this->q_tasks.pop();
		this->tp_mutex.unlock();

		temp_func();	// execute the fucntion from the queue
	}
}

void Threadpool::addWork(std::function<void()> work ) {
	this->tp_mutex.lock();
	this->q_tasks.push(work);
	this->tp_mutex.unlock();
	this->tpSemaphore.notify();
}

// tester function to be passed
void tester1(int arg1, std::string arg2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(8000));
	std::cout << "tester1 function finished." << std::endl;
}
void tester2(int arg1, std::string arg2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::cout << "tester2 function finished." << std::endl;

}
void tester3(int arg1, std::string arg2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "tester3 function finished." << std::endl;
}
void tester4(int arg1, std::string arg2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	std::cout << "tester4 function finished." << std::endl;
}

int main() {
	Threadpool tp;

	
	// need  a placeholder as there is no thread variable yet
	tp.addWork(tester1); // I want to pass an argument here
	tp.addWork(tester2);
	tp.addWork(tester3);
	tp.addWork(tester4);
		
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}

