/* Condition variable tester
 *
 * 
 */

#include <iostream>
#include <thread>
// #include <functional>
#include <mutex>
#include <condition_variable>


class Application {
private:
	std::mutex m_mutex;
	std::condition_variable m_condVar;
	bool m_bDataLoaded;

public:
	Application();
	~Application();
	
	void loadData();
	bool isDataLoaded();
	void mainTask();
	void mainTask_condition();
};

// Constructors
Application::Application(): m_bDataLoaded {false} {}
Application::~Application(){}

void Application::loadData() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "Loading data.." << std::endl;

	// Lock the Data structure
	std::lock_guard<std::mutex> guard(m_mutex); 

	// set the flag to true --> Data is loaded
	m_bDataLoaded = true;
	std::cout << "Load cycle finished." << std::endl;

	//required if using condtion variable, otherwise comment out
	m_condVar.notify_one();	//notify the condition variable.
}
bool Application::isDataLoaded () {
	
	return false;
}

/*Traditional mutex lock/unlock
 * Although this is a simple implementation, it is highly inefficient,bc of the constant polling 
 * By using condition variable, you are not polling 
 * */

void Application::mainTask() {
	std::cout << "Checking for load status.." << std::endl;

	// Acquire the lock
	m_mutex.lock();

	// check if flag is set to true
	while (m_bDataLoaded != true) {
		std::cout << "waiting for data to be loaded..." << std::endl;
		
		// the problem here is the wasted cpu cycles of constant locking/unlocking of the mutex will slow the thread
		m_mutex.unlock(); // Release the lock to give loadDta
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sleep for 100ms to allow loadData() to have a chance 
		m_mutex.lock(); // this lock is for the while condition to read the m_bDataLoaded variable
	}

	m_mutex.unlock(); // Release the lock;
	std::cout << "process the loaded data" << std::endl;
}

/* Using a condition variable instead */
void Application::mainTask_condition () {
	std::cout << "waiting for notify condition_var" << std::endl;

	// Acquire the lock
	//Unique lock allows for lock/unlock, perfect for condition variable checks
	std::unique_lock<std::mutex> u_lock (m_mutex);

	// std::bind of &Application::isDataLoaded is added as a redundacy check 
	//to ensure m_bDataLoaded is true as well in order to ensure conditon is 
	// truly met. optional???
	m_condVar.wait(u_lock, std::bind(&Application::isDataLoaded, this)); //wait for isDataLoaded to become true. 'this' refers to this instance
	std::cout << "process the loaded data." << std::endl;




}




int main() {
	Application app;

	std::thread thread_1(&Application::mainTask_condition, &app);
	std::thread thread_2(&Application::loadData, &app);

	thread_1.join();
	thread_2.join();

	return 0;
}


