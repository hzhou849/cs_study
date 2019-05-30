
/* Threadpool passing functions with 
 * PROPER Version
 *args into a queue for later processing at run-time 
 *
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

/* Threadpool class */
class Threadpool {
private:
	std::vector <std::thread*> threads;		// using ptrs so we don't copy the threads itself into the queue just the address.
	std::queue < std::function <void()> > tasks;
	std::mutex tp_mutex;
	Semaphore workSemaphore;
	void workLoop();
public:
	Threadpool();
	~Threadpool();
	void addWork(std::function <void()>);

};

Threadpool::Threadpool() {
	for (int i =0; i<3; i++) {
		std::thread *t = new std::thread(&Threadpool::workLoop, this);
		this->threads.push_back(t);
	}
}


// void Threadpool::joinThreads() {
// 	for (auto th: threads) {
// 		th->join();
// 	}
// }

Threadpool::~Threadpool() {
	for (auto th: threads) {
		th->join();		//join the thread
		delete th;		// free the pointer memory.
	}
}


void Threadpool::workLoop() {
	while (true) {
		this->workSemaphore.wait(std::this_thread::get_id());
		this->tp_mutex.lock();
		std::function<void()> work = this->tasks.front();	//fetch work from queue
		this->tasks.pop();
		this->tp_mutex.unlock();
		work();
	}
}

void Threadpool::addWork(std::function<void () > work) {
	this->tp_mutex.lock();
	this->tasks.push(work);
	this->tp_mutex.unlock();
	this->workSemaphore.notify();
}

template <typename T1, typename T2>
void testerF1(T1 arg1,T2 arg2 ) {
	std::cout << "T1: "<< arg1<<" T2: " <<arg2  << std::endl;
}

void testerF2( std::string s) {
	std::cout << "testerF2: " << s << std::endl;
}
int main() {
	Threadpool tp;
	int i=99;
	/* lambda attached to the tp.addwork si the function of work pushed into the queue. */
	tp.addWork([&i]() {
		// all code added into the queue
		std::cout << "Thread: " << std::this_thread::get_id() << "is sleeping.." << std::endl;
		std::cout << "this arg is only passed into this lambda scope" << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		testerF1(i, "ttf1");
	});

	return 0;
}