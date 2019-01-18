
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>



class Application {
private: 
	std::mutex mtx;
	std::condition_variable cond_var;
	bool load_flag;
	bool thread_flag;
	bool exit_flag;
	int input_data;
public:
	Application();
	~Application();

	void mainTask();	// waits for data load
	void loadData();
	void gen_thread(std::function <void (int) > ptr); // threadpool	
	bool get_flag();
	void set_exit_flag();
	
	
};

// Constructors
Application::Application(): load_flag{false}, thread_flag{false}, exit_flag{false} {}
Application::~Application(){
	std::cout << "Destructor called" << std::endl;
	exit_flag = true;

}


void Application::mainTask() {
	std::cout << "waiting for notify condition var"<<std::endl;

	//create unique lock wrApplicationer - all critical code below this point
	std::unique_lock<std::mutex> u_lock(mtx);

	cond_var.wait(u_lock, std::bind(&Application::get_flag, this)); // 'this' is this object instance
	std::cout << "signal recevied." << std::endl;
}

void Application::loadData () {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	// lock_guard is used for single instance RAII, 
	std::lock_guard <std::mutex>lock(mtx); 
	
	//set the flag to true
	load_flag = true;

	//notify the condition variables
	cond_var.notify_all();
}


void Application::gen_thread(std::function <void(int) > ptr_func) {  // note this 'ptr' only takes one 1 parameter
	
	while(!exit_flag) {
		// give another thread a chance, notice this placement must be at the top not bottom of this code block
		// bc when the while loop resets, it immediately reacquires the lock before the next thread can get it.
		// this sleep allows the other thread to get the thread in a race.
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
		std::unique_lock<std::mutex>u_lock(mtx);
		cond_var.wait(u_lock, std::bind(&Application::get_flag, this));
		ptr_func(999); // task function()
		// u_lock.unlock();
		cond_var.notify_all();		
	}

		

}
bool Application::get_flag() {return load_flag;}

void Application::set_exit_flag() {exit_flag = true;}



void task(int thread_num, int data) {
	// for (int i=0; i<2; i++) {
	// 	std::cout << "Processing task.. Thread:" << thread_num << " B:"<< data << std::endl;
	// }
	std::cout << "Processing task.. Thread:" << thread_num << " B:"<< data << std::endl;

	// staggered sleep time to simulate different processing times.
	if (thread_num == 1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	} else if (thread_num == 2) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} else {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}


int main() {
	Application a_obj;

	//test case 1:
	// std::thread thread1(&Application::mainTask, &a_obj);
	// std::thread thread2(&Application::loadData, &a_obj);

	
	// thread1.join();
	// thread2.join();
	
	// test case 2:
	// std::vector<std::thread>vec_threads;	// vector to hold all created threads
	// for (int i=0; i<vec_threads.size(); i++) {
	// 	vec_threads.push_back(std::thread(&Application::gen_thread, &a_obj));
	// }

	// // Multiple join from vectors
	// for (unsigned int i=0; i < vec_threads.size(); i++) {
	// 	vec_threads.at(i).join(); 
	// }

	// Test case 3:
	// First thread to acquire the mutex will process the task in this thread race.
	//As you can see, the function we give to callit only accepts one parameter. 
	//But we want to give it a function that has 2 parameters. So we use bind() to say 
	//"use whatever paramter callit provides as the 1st param, and use 20 as the 2nd param".
	//use std::placeholders_<value> if you don't want the pass the actual arg values now.

	std::thread thread1(&Application::gen_thread, &a_obj, std::bind(task, 1, std::placeholders::_1 )); // create the thread
	std::thread thread2(&Application::gen_thread, &a_obj, std::bind(task, 2, std::placeholders::_1)); 
	std::thread thread3(&Application::gen_thread, &a_obj, std::bind(task, 3, std::placeholders::_1)); 

	// std::thread thread2(&Application::gen_thread, &a_obj, std::bind(task, std::placeholders::_1, std::placeholders::_2));
	// std::thread thread1(&Application::gen_thread, &a_obj, std::bind(task, 99,56)); // if you want to pass parameters yourself. recving function <void()>funct

	// std::thread thread3 (&Application:: loadData, &a_obj);
	a_obj.loadData();


	for (int i=0; i < 100; i++) {
		std::cout << "main thread running" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}


	// Cleanup signal flag to close
	a_obj.set_exit_flag(); 
	thread1.join();
	std::cout << "thread1.join()" <<std::endl;
	thread2.join();
	thread3.join();
	


	return 0;
}



