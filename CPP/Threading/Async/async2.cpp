/* Async version 2
 *
 *  
 *
 */

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

class TaskProcessor {
public:
	TaskProcessor();
	~TaskProcessor();

	std::string fetchDataFromDB(std::string rcvdData);
	std::string fetchDataFromFile(std::string rcvdData);
};

TaskProcessor::TaskProcessor() {}
TaskProcessor::~TaskProcessor() {}

std::string TaskProcessor::fetchDataFromDB(std::string rcvdData) {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "DB done processor" << std::endl;
	return "DB_ " + rcvdData;
}

std::string TaskProcessor::fetchDataFromFile(std::string rcvdData) {
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "File processing done" << std::endl;
	return "FILE_ " + rcvdData;
}

int main() {
	TaskProcessor tp;

	// start the timer.
	std::chrono::system_clock::time_point timer_start = std::chrono::system_clock::now();

	std::string db_data = tp.fetchDataFromDB("dbTester");
	std::string file_data = tp.fetchDataFromFile("fileTester");



	//stop the timer - using 'auto' for shorthand
	auto timer_end = std::chrono::system_clock::now(); 
	auto timer_elapsed = std::chrono::duration_cast<std::chrono::seconds> (timer_end - timer_start).count(); // count() returns ticks.
	std::cout << "\nExecution time elapsed: " << timer_elapsed <<

	std::cout << db_data<< " "<<file_data << std::endl;


}

