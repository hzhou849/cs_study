/* Semaphore class
 * My version
 * https://riptutorial.com/cplusplus/example/30142/semaphore-cplusplus-11
 
https://thispointer.com/c11-how-to-create-vector-of-thread-objects/

1
2
// Create a vector of threads
std::vector<std::thread> vecOfThreads;
Now let’s create a std::function<> object that we will pass to thread object as thread function i.e.

C++

// Create a function object
std::function<void()> func = []() {
					//Do Some Important Work
					// .....
					//Print Thread ID
					std::cout << "From Thread ID : "<<std::this_thread::get_id() << "\n";
					};
1
2
3
4
5
6
7
// Create a function object
std::function<void()> func = []() {
					//Do Some Important Work
					// .....
					//Print Thread ID
					std::cout << "From Thread ID : "<<std::this_thread::get_id() << "\n";
					};
Now let’s create 2 thread objects using this std::function objects i.e.


std::thread th1(func);
std::thread th2(func);
1
2
std::thread th1(func);
std::thread th2(func);

modify to put a global counter to see how many counts there are and how they chnage

=============================================================================
Structure

class Semaphore {
	std::mutex m_mutex;
	std::condition variable cv;
	int count=0;

	void notify() {
		std::unique_lock u_lock(m_mutex); //acquire unique lock
		count++;						  // increment counter
		cv.notify_one();				 // notify conditon variable u_lock
	}

	void wait() {
		1) acquire unique lock.
		2) while (count == 0)			// if count is 0 standby thread
			cv.wait(u_lock);
		count--; 						//decrement counter
	}
}


*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

/* Semaphore Class */
class Semaphore {
private:
	std::mutex sema_mutex;
	std::condition_variable sema_cv;
	int count;

public:
	Semaphore(): count{0} {}
	~Semaphore() {}

	void notify(std::thread::id tid) {   		// notify - increment
		// std::cout << "Notify() : thread " << tid << std::endl;
		std::unique_lock<std::mutex>u_lock(sema_mutex); // attempt to acuqire lock before accessing count
		count++;
		std::cout << "Notify() Thread: " << tid << " notify() acquired "<< std::endl;

		// notify the waiting thread
		sema_cv.notify_one();
	}


	/*wait for the notify to be called */
	void wait(std::thread::id tid) {			// wait -decrement
		std::unique_lock<std::mutex>u_lock(sema_mutex); // this unique_lock is so thread can read the count value
		while (count == 0) { 		// (handles spurious wake ups)all threads are busy, wait here
			std::cout << "Thread: " << tid<< " wait " << std::endl;
			//wait on the mutex until notify is called
			sema_cv.wait(u_lock); //wait for the actually
			std::cout << "Thread " << tid << " run" << std::endl;
		}
		count--;
	}

};


/* Threadpool class */
class Threadpool {
private:
	std::vector<std::thread*> threads; 		//vector that holds thread pointer
	std::queue<int> q_tasks;
	std::mutex tp_mutex;					//local mutex used to sync pushing work
	Semaphore threadpoolSema;						//Create  a semaphore object
	void fetchWork();		

public:
	Threadpool(); 						//default constructor
	~Threadpool();
	void addWork(int data);				//add "work" to queue
	void joinThreads();
};

Threadpool::Threadpool() {
	// Create thread and pushback into vector
	for (int i=0; i<3; i++) {
		std::thread *t = new std::thread(&Threadpool::fetchWork, this);
		this->threads.push_back(t); 		
	}
}

void Threadpool::addWork(int data) {
	this->tp_mutex.lock();			//acquire mutex to PUSH work into queue
	this->q_tasks.push(data);
	this->tp_mutex.unlock();		// release the mutex so the next avail thread can access the queue
	this->threadpoolSema.notify(std::this_thread::get_id());			// notify threads there is work available increment the semaphore
}

/* This is the work processing thread for the threadpool*/
void Threadpool::fetchWork(){
	while (true) {
		int current_int;					//temp int var to hold value feteched from queue created on stack to be destroyed after task completed

		this->threadpoolSema.wait(std::this_thread::get_id());

		this->tp_mutex.lock();
		current_int = this-> q_tasks.front();
		this->q_tasks.pop();
		this->tp_mutex.unlock();
		//simulate processing
		std::cout << "START->Thread: " << std::this_thread::get_id() << " int: "<<"["<<current_int<<"]"<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(current_int));
		std::cout << "FINSIHED ->Thread: " << std::this_thread::get_id() << " int: "<<current_int<<std::endl;
		

	}
}

void Threadpool::joinThreads() {
	for (auto th: threads) {
		th->join();
	}
}

Threadpool::~Threadpool(){}

int main() {
	Threadpool tp; // create threadpool object

	tp.addWork(10);
	tp.addWork(3);
	tp.addWork(5);
	tp.addWork(2);
	tp.addWork(8);
	tp.addWork(2);
	// std::this_thread::sleep_for(std::chrono::seconds(100)); // sleep the main thread so the program doesn't end prematurely
	
	tp.joinThreads();
}