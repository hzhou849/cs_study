#ifndef _SEMAPHORE_HPP_
#define _SEMAPHORE_HPP_

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "syncstream.hpp"


class Semaphore {
private:
	// int key_threshold;					// how many keys available before processing
	std::mutex sem_mutex;				// mutex
	std::condition_variable sem_cv;		// condition variable
	int count;							// counter of available "keys"
public:
	Semaphore():count {0} {}
	~Semaphore(){}

	void notify() {		// increment
		std::unique_lock<std::mutex>u_lock(sem_mutex); // atttempt to acquire lock before accessing count
		count++;
		
		
		// Notify the waiting thread
		sem_cv.notify_one();
	}

	void wait(std::thread::id tid) { 	// decrement
		std::unique_lock<std::mutex>u_lock(sem_mutex); // attempt to acquire lock
		while(count == 0) { 		// handles spurious wakes ups
			synced(std::cout) << "Thread: " << tid << " waiting..." << std::endl;
			sem_cv.wait(u_lock);	// wait on the mutex until notify is called.
			synced(std::cout) << "Thread: "<< tid << " lock acquired..running " << std::endl;
		}	
		count--;
	}
};

#endif //_SEMAPHORE_HPP_

