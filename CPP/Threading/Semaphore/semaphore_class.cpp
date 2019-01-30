/* Semaphore class
 * https://riptutorial.com/cplusplus/example/30142/semaphore-cplusplus-11
 * #include <mutex>
#include <condition_variable>
        
class Semaphore {
public:
    Semaphore (int count_ = 0)
    : count(count_) 
    {
    }
    
    inline void notify( int tid ) {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cout << "thread " << tid <<  " notify" << endl;
        //notify the waiting thread
        cv.notify_one();
    }
    inline void wait( int tid ) {
        std::unique_lock<std::mutex> lock(mtx);
        while(count == 0) {
            cout << "thread " << tid << " wait" << endl;
            //wait on the mutex until notify is called
            cv.wait(lock);
            cout << "thread " << tid << " run" << endl;
        }
        count--;
    }
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chorno>

class Semaphore {
private:
	std::mutex sema_mutex;
	std::condition_variable sema_cv;
	int count;

public:
	Semaphore(): count{0} {}
	~Semaphore() {}

	void notify(int tid) {   		// notify - increment
		std::unique_lock<std::mutex>u_lock(sema_mutex) // attempt to acuqire lock before accessing count
		count++;
		std::cout << "Thread: " << tid << " notify() acquired " std::endl;

		// notify the waiting thread
		cv.notify_one();
	}

	void wait(int tid) {			// wait -decrement
		std::unique_lock<std::mutex>u_lock(sema_mutex);
		while (count == 0) { 		// all threads are busy, wait here
			std::cout << "Thread: " << tid<< " wait " << std::endl;
			//wait on the mutex until notify is called
			cv.wait(lock);
			std::cout << "Thread " << tid << " run" << std::endl;
		}
		count--;
	}

}


class Threadq {
private:
	std::mutex m_mutex;
	std::condition_variable cv;
	bool read = false;
	int current = 0;
public:
	void 
}

