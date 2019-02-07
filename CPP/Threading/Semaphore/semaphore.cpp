/*
 * Semaphore example, c++
 * compile: g++ -std=c++11 semaphoe.cpp
 * https://austingwalters.com/multithreading-semaphores/
 * 
 * In computer science, particularly in operating systems, a semaphore is a variable 
 * or abstract data type that is used for controlling access, by multiple processes, to
 *  a common resource in a parallel programming or a multi user environment.
 *
 * More or less semaphores C++11 are used for is keeping track of how many resources 
 * are currently available for use at a given time. This usually (almost always) applies 
 * to how many threads are currently available to the operating system. 
 * 
 * 
 * More straight forward a semaphore is simply a counter, used to keep track of 
 * how many of a particular resource you have available. If for example, we would like to use a 
 * semaphore to print the thread number, we would do something like below (represented visually):
 * 
 * It is fairly clear there could have been a race condition, however with the use of the following lines:
 *  {
 * 		while(num != current || !ready){ cv.wait(lck); }
 * 		current++;
 * }
 * We only allowed the thread who’s number matched the variable “current” to run. 
 * This enabled the threads to be printed in order with the use of semaphores C++11!
 * 
 * The code above, using semaphores c++11 is much nicer and easier than using the POSIX library, 
 * but it is about as easy (just far less readable) to use POSIX. 

 * std::unique_lock
 * The class unique_lock is a general-purpose mutex ownership wrapper allowing deferred locking, 
 * time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.
 * 
 * - you take ownership of a semaphore with a wait operation aka decrementing the semaphore? abstractly p
 * - you release ownership of a semaphore, incrementing the semaphore.
 * 
 * https://riptutorial.com/cplusplus/example/30142/semaphore-cplusplus-11
 * 
 * Abstract:
 * 	- the idea of the semaphore is to keep track of the resources available. you are tracking the tasks (ie incrementing adding task)
 *  - decrementing when processing. So the Threads know there will be work if the count variable is greater than zero. see 
 * 		semaphore_class.cpp
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m_mutex;			//mutex for critical section
std::condition_variable cv; // condition variable for critical seciton
bool ready = false;			// Tell threads to run
int current = 0;			// current count

// Prints the thread id/ max number of threads 
void print_num(int num, int max) {
	std::unique_lock<std::mutex>u_lock(m_mutex);
	
	//if the thread num is not the current counter, wait until the corrrect thread accesses this function
	// without portion of code, a thread race will occur
	while (num !=current || !ready) {
		cv.wait(u_lock);
	}
	current++;
	std::cout << "Thread" << num +1 << " / " << max << "current count is: " << current << std::endl;

	// Notify next threads to check if it is their turn 
	cv.notify_all();
}

// Changes ready to true, and begins the threads printing
void run () {
	std::unique_lock<std::mutex>u_lock(m_mutex); // attempt to acquire the lock
	ready = true; // since threads will read this value, we want to lock it first
	cv.notify_all(); // kick off the threads
}

int main() {
	int threadnum = 15;
	std::thread threads[15]; // convert to vector for more flexibility

	/* spawn thread num threads */
	for (int id = 0; id < threadnum; id ++ ) {
		threads[id] = std::thread(print_num, id, threadnum); // creates the threads and have them wait on standby for notify call
	}

	std::cout << "\nRunning " << threadnum <<  "in parallel: \n" << std::endl;

	run(); // Allows thread to run

	/* Merge all threads to the main thread */
	for (int id = 0; id < threadnum; id++) {
		threads[id].join();
	}

	// std::cout << "\nCompleted semaphore example!\n";
	// std::cout << std::endl;
	
	return 0;
}




