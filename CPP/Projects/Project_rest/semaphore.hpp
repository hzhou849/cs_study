#ifndef _SEMAPHORE_HPP_
#define _SEMAPHORE_HPP_

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
	std::mutex sema_mutex;
	std::condition_variable sema_cv;
	int count;
public:
	Semaphore(): count {0} {}
	~Semaphore() {}

	// Notify() - increment
	void notify(std::thread::id tid) {
		std::unique_lock<std::mutex>u_lock(sema_mutex);	 // attempt to acquire lock before accessing count
		count++;
		std::cout << "Notify() Thread: " << tid <<  "Notify() acquired " << std::endl;

		// Notify the next available waiting thread
		sema_cv.notify_one();
	}

	// wait() - decrement
	void wait(std::thread::id tid) {
		std::unique_lock<std::mutex>u_lock(sema_mutex); //this unique_lock is so thread can read the count value
		while (count == 0) { //handles spurious wake ups
			std::cout << "Thread: " << tid << " wait " << std::endl;

			// wait on the mutex until notify is called
			sema_cv.wait(u_lock); // wait for notify?
			std::cout << "Thread " << tid << " run" << std::endl; 
		}
		count--;
	}
};


#endif //_SEMAPHORE_HPP_