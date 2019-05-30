#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

/* Condition_app.hpp */
#ifndef _CONDITION_APP_
#define _CONDTIION_APP_

class Condition_app {
private:
	std::mutex m_mutex;
	std::condition_variable m_condVar;
	bool m_bDataLoaded;

public:
	Condition_app();
	void loadData();
	bool isDataLoaded();
	void mainTask();
};

#endif //_CONDITION_APP_


/* Condition_app.cpp */
Condition_app::Condition_app() {
	m_bDataLoaded = false;
}

void Condition_app::loadData() {
	//Sleep thread to simulate load
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "Loading data..." << std::endl;

	//Lock guard used here because it will terminate on its own once out of scope
	std::lock_guard<std::mutex> guard (m_mutex); // Lock the data structure
	m_bDataLoaded = true;						// set flag to true;
	m_condVar.notify_one();						// notify the condition variable

}

bool Condition_app::isDataLoaded() {
	return m_bDataLoaded;
}

void Condition_app::mainTask() {
	std::cout << "handshake...." << std::endl;

	//Acquire the lock
	std::unique_lock<std::mutex> u_lock(m_mutex);
	/* Start waiting for the Condition variable to get signaled.
	 * Wait() will internally release the lock and make the thread block
	 * as soon as  the CondVar gets signaled, resume the thread and
	 * acquire the lock and check if the condition is met or not.
	 * If condition is met, continue. Else, wait and repeat procedure.
	 
	 * std::bind(<function to pass>, <object Instance>)
	 * m_condVar.wait(u_lock); // this can work too if you dont' want to rely on isDataLoaded() to be the signal
	 * 
	 * wait(arg2 overload) isDataLoaded() is used to ignore spurious(false positive) awakenings while waiting
	 * for a specific condition to become true. 
	 */

	m_condVar.wait(u_lock, std::bind(&Condition_app::isDataLoaded, this)); // Thread will block
	std::cout << "Processing the data loaded" << std::endl;
}

int main() {
	Condition_app capp;
	std::thread thread1(&Condition_app::mainTask, &capp);
	std::thread thread2(&Condition_app::loadData, &capp);

	thread2.join();
	thread1.join();

	return 0;
}




/* Main Driver class */