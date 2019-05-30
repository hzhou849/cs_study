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

	void notify (std::thread::id tid) {
		std::unique_lock<std::mutex>u_lock(sm_mutex); // attemp to acquire lock before accessing count
		count++;
		std::cout << "Notify() Thread: " << tid << " notified() acquired" << std::endl;

		// notify the waiting thrad
		sm_cv.notify_one();
	}

	void wait(std::thread::id tid) {
		std::unique_lock<std::mutex>u_lock(sm_mutex);
		while (count == 0) {	// handles spurious wake ups
			std::cout << "Thread: " << tid << " wait" << std::endl;
			sm_cv.wait(u_lock); 	// wait on the mutex until notify is called.
			std::cout << "Thread " << tid << " run" << std::endl;
		}

		count --;
	}
};
