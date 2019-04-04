#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>

class Semaphore {
private:
	std::mutex sem_mutex;
	std::condition_variable sem_cv;
	int count;

public:
	Semaphore(): count {0} {}
	~Semaphore() {}

	void notify (std::thread::id tid) {
		std::unique_lock<std::mutex>u_lock(sem_mutex); // attemp to acquire lock before accessing count
		count++;
		std::cout << "Notify() Thread: " << tid << " notified() lock acquired" << std::endl;

		//notify the waiting thread
		sem_cv.notify_one();
	}

	void wait(std::thread::id tid) {
		std::unique_lock <std::mutex>u_lock(sem_mutex);
		while (count == 0) {		//handles spurious wake ups
			std::cout << "Thread: " << tid << " wait" << std::endl;
			sem_cv.wait(u_lock);	// wait on the mutex until notify is called.
			std::cout << "Thread" << tid << " run" << std::endl;
		}
		count--;
	} 
};


/* Threadpool class */
class Threadpool {
private:
	std::vector <std::thread*> vec_thread; // using pointers so we don't copy the threads itself into the vector
	std::queue <std::function <void()> > q_tasks;
	std::mutex tp_mutex;
	Semaphore semObject;
	void workLoop();
public:
	Threadpool();
	~Threadpool();
	void addwork( std::function <void()> );
};

//Constructor
Threadpool::Threadpool() {
	for (int i=0; i<3; i++) {	// Create 3 loops
		//create a thread passing ptr of function workLoop(), this instance 
		std::thread *t = new std::thread(&Threadpool::workLoop, this);
		this->vec_thread.push_back(t);
	}
}

Threadpool::~Threadpool() {
	for (auto temp_thread: vec_thread) {
		temp_thread->join(); // join the threads  temp_thread is a ptr so '->' not '.'
		delete temp_thread;		// free the pointer memory.
	}
}

/* Constant loop of threads. but sits in waiting until semaphore gets incremented */
void Threadpool::workLoop() {
	while(true) {
		this->semObject.wait(std::this_thread::get_id()); //
		this->tp_mutex.lock();

		std::function<void()> work = this->q_tasks.front(); //fetch work from queue threadsafe operation
		this->q_tasks.pop();
		this->tp_mutex.unlock();
		work();
		std::cout << "Processing thread: " << std::this_thread::get_id() << std::endl;
	}
}

void Threadpool::addwork(std::function<void()> work) {
	this->tp_mutex.lock(); // try to lock queue
	this->q_tasks.push(work);
	this->tp_mutex.unlock();
	this->semObject.notify(std::this_thread::get_id());
}


template <typename T1, typename T2>
void testerF1(T1 arg1, T2 arg2) {
	std::cout << "T1: " << arg1 << " T2: " << arg2 << std::endl;
}

void testerF2(std::string s) {
	std::cout << "TesterF2: " << s << std::endl;
}

int main() {
	Threadpool tp;
	int i = 999; // arbitrary number for arg passing

	// Lambda attached to tp.addwork is the fucntion 
	// of work pushed into the queue. 
	tp.addwork([&i]() {
		// pass this entire block as a lambda function as addwork(func arg)
		std::cout << "Main Thread: " << std::this_thread::get_id() << " is sleeping.." << std::endl;
		std::cout << "This arg is only passed into this lambda scop " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		testerF1(i, "ttf1");

	});

	// to pass direct function, use std::bind 
	tp.addwork(std::bind(testerF2, "s")); 
	return 0;
}
