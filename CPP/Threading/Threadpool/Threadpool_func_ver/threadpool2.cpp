#include <iostream>
#include <thread>
#include <mutex>
#include "semaphore.h"

class Thread_proc {
private:
	Semaphore sem;
	std::mutex tp_mutex;
	void processor();
	int counter;
public:
	Thread_proc();
	~Thread_proc();
}

// Constructor
Thread_proc::Thread_proc() {
	int counter =0;
	std::thread t1 = new std::thread(&Thread_proc::processor, this);
	std::thread t2 = new std::thread(&Thread_proc::processor, this);

}

Thread_proc::~Thread_proc() {
	t1.join();
	t2.join();
}

void Thread_proc::processor() {
	while (true) {
		std::thread::id tid = std::this_thread::get_id();
		sem.wait(tid);

		//if semaphore allows resume
		tp_mutex.lock(); // lock to access the counter variable
		counter++;

	}

	
}

	