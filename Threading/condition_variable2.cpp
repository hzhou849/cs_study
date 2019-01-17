
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>



class App {
private: 
	std::mutex mtx;
	std::condition_variable cond_var;
	bool load_flag;
public:
	App();
	~App();

	void mainTask();	// waits for data load
	void loadData();	
	bool get_flag();
	
};

// Constructors
App::App(): load_flag{false} {}
App::~App(){}


void App::mainTask() {
	std::cout << "waiting for notify condition var"<<std::endl;

	//create unique lock wrapper - all critical code below this point
	std::unique_lock<std::mutex> u_lock(mtx);

	cond_var.wait(u_lock, std::bind(&App::get_flag, this)); // 'this' is this object instance
	std::cout << "signal recevied." << std::endl;
}

void App::loadData () {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	// lock_guard is used for single instance RAII, 
	std::lock_guard <std::mutex>lock(mtx); 
	
	//set the flag to true
	load_flag = true;

	//notify the condition variables
	cond_var.notify_one();
}

int main() {
	// App a_obj;
	// std::thread thread1(&App::mainTask, &a_obj);
	// std::thread thread2(&App::loadData, &a_obj);

	
	// thread1.join();
	// thread2.join();



	return 0;
}



bool App::get_flag() {
	return load_flag; 
}
