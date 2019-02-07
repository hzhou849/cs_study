/* Threadpool - semaphore version 
 * alex's version threadpool version
 * stores functions inside a queue and the threadpool takes jobs from that queue
 * may need modifctions??.
*/

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
	std::mutex sema_mutex;
	std::condition_variable condVar;
	unsigned long count = 0; 	//initialized as locked.

public:
	void notify() {
		std::lock_guard<decltype(sema_mutex)> lock (sema_mutex);
		//std::lock_guard<std::mutex> lock_var (sema_mutex); // alt method
		++count;
		condVar.notify_one();
	}

	void wait() { // takes ownership (decrementing  the semaphore)
		std::unique_lock<decltype(sema_mutex)> ulock(sema_mutex);
		while(!count) 	{
			// Handle spurious wake-ups
			condVar.wait(ulock);
		}	
		--count; 
			
	}

	bool try_wait() {
		std::lock_guard<decltype(sema_mutex)> lock (sema_mutex);
		if (count) {
			--count;
			return true;
		}
		return false;
	}
};

class Threadpool {
private:
	std::vector<std::thread*> threads;
	std::queue < std::function<void()> >  tasks;
	std::mutex tp_mutex;
	Semaphore workSemaphore;
	void workLoop();

public:
	Threadpool();		// constructor
	void addWork(std::function<void()>);
};

//Constructor
Threadpool::Threadpool() {
	for (int i=0; i < 3; i++){
		std::thread *t = new std::thread(&Threadpool::workLoop, this);
		this->threads.push_back(t);
	}
}

void Threadpool::workLoop() {
	while (true) {
		this->workSemaphore.wait();
		this->tp_mutex.lock();
		std::function<void()> work = this->tasks.front(); 	//data type is std::function<void()> variable
		this->tasks.pop();
		this->tp_mutex.unlock();
		work();

	}
}

void Threadpool::addWork(std::function<void()> work) {
	this->tp_mutex.lock();
	this->tasks.push(work);
	this->tp_mutex.unlock();
	this->workSemaphore.notify();
}

void notMain(); // function prototype

int main() {
	notMain();
	std::this_thread::sleep_for(std::chrono::seconds(20));
	return 0;
}

void notMain() {
	Threadpool tp;
	int i=0;

	tp.addWork([&i]() {		// closures  keeps i variable alive after scope
		std::cout << "Thread " << std::this_thread::get_id() << " is sleeping.." <<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		i++;
		std::cout << "Thread " << std::this_thread::get_id() << " done sleeping." << std::endl;
		std::cout << i << std::endl;
	});

	tp.addWork( [&i]() {
		std::cout << "Thread " << std::this_thread::get_id() << " is sleeping.." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		i++;
		std::cout << "Thread " << std::this_thread::get_id() << " done sleeping." << std::endl;
		std::cout << i << std::endl;
	});

	tp.addWork([&i]() {
		std::cout << "Thread " << std::this_thread::get_id() <<" is sleeping..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(7));
		i++;
		std::cout <<"Thread " << std::this_thread::get_id() << " done sleeping." << std::endl;
		std::cout << i << std::endl;
	});
}