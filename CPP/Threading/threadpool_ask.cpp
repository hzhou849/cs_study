/* Threadpool algorithm v1.2
 * 1) dynamically bind the queue to automatically process whatever you put into the queue.
 *    - ie {1, "string" , &function_pointer,etc...}
 * 2) make a buffer class to add to output. 
 * 3) use virtual functions to allow dynamic overload of perhaps???
 */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "Queue.hpp"

class Threadpool {
private:
	std::mutex m_mutex;
	std::condition_variable cond_var;
	bool load_flag;
	bool thread_flag;
	bool exit_flag;
	int input_data;
public:
	Queue* process_q;
	Threadpool();
	~Threadpool();

	//overloaded member functions to handle different data types.
	// void gen_thread(int threadNumber); // no args
	// void gen_thread(std::function <void> ptr); // takes function
	void gen_thread(std::function <void (int) >task_proc_tr); //threadpool takes function with single arg value

	void addTask(int element);
	bool tp_get_q_status();
	void tester();
	void killThread();
	int addTask2(int element);

	
};

// Constructors 
Threadpool::Threadpool(): load_flag{false}, exit_flag{false} {
		// Queue process_q{5}; // create a queue fo size 5
		process_q = new Queue(5);
		


}
Threadpool::~Threadpool() {
	delete process_q;
	std::cout << "Destructor called.." << std::endl;
}

void Threadpool::gen_thread(std::function <void (int)> task_proc_ptr) {

	while (!exit_flag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200)); // allow another thread to process.
		std::unique_lock<std::mutex>u_lock(m_mutex);
		cond_var.wait(u_lock, std::bind(&Threadpool::tp_get_q_status, this)); // check if Queue::has_work is true

		task_proc_ptr(123456);
		process_q->dequeue();
		process_q->display();
		cond_var.notify_all();

	}
	
}

void Threadpool::addTask (int element) { // must be void class to see output, if has return type will not printout.
	if (element == 0)
		std::cout << "invalid element entry." <<std::endl;
		// return -1;
	this->process_q->enqueue(element);
	// this->process_q->display();
	// std::cout<< "this ran" << std::endl;

	// std::cout << process_q << std::endl;
	// return 0;
}

bool Threadpool::tp_get_q_status() {
	bool value = process_q->has_work();
	std::cout << std::boolalpha;
	// std::cout << value << std::endl;
	return value;
}

void task_processor(int thread_num, int data) {
	std::cout << "processing task.. Thread: " << thread_num << " data: " << data<<  std::endl;
}

void Threadpool::tester() {
	process_q->enqueue(1);
	// process_q->display();
}

void Threadpool::killThread() {
	std::cout<< "attempting to kill all" << std::endl;
	exit_flag = true;
	cond_var.notify_all();
}

// int Threadpool::addTask2 (int element) { // must be void class to see output, if has return type will not printout.
// 	if (element == 0)
// 		std::cout << "invalid element entry." <<std::endl;
// 		return -1;
// 	this->process_q->enqueue(element);
// 	this->process_q->display();
// 	std::cout<< "this ran" << std::endl;

// 	std::cout << process_q << std::endl;
// 	return 0;
// }

int main() {
	Threadpool tp_obj;
	std::cout << "tp_get_q_status state now" << tp_obj.tp_get_q_status() << std::endl;
	// tp_obj.addTask(22);
	// tp_obj.tester();
	// std::cout << tp_obj.tp_get_q_status() << std::endl;
	// 1st arg '1' will automatically be passed through gen_thread -> task_processor()
	std::thread thread1(&Threadpool::gen_thread, &tp_obj, std::bind(task_processor, 1,std::placeholders::_1 )); // create a placeholder for arg2
	std::thread thread2(&Threadpool::gen_thread, &tp_obj, std::bind(task_processor, 2,std::placeholders::_1 ));
	tp_obj.addTask(22);
	tp_obj.addTask(23);
	std::cout << "state now: " << tp_obj.tp_get_q_status() << std::endl;


	tp_obj.killThread();
	// std::bind(&Threadpool::tp_get_q_status, this)) thread will not close until this condition is met too 
	thread1.join();
	thread2.join();
	
	return 0;
}