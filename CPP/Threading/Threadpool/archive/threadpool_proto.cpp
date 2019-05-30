/*implementation is not complete - concept only*/

#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>

void Pool::infinite_loop_function {
	while (true) {
		unique_lock<mutex> lock(Queue_Mutex);

		condition.wait(lock, []{return !Queue.empty()});
		job = Queue.front();
		Queue.pop();
	}
	job(); // function<void()>type
}

void Pool::Add_job(fucntion<void()> new_job) {
	{
		unique_lock<mutex>lock(Queue_Mutex);
		Queue.push(new_job);
	}
	condition.notify_one();

}
int main() {
	int num_threads = std::thread::hardware_concurrency(); // returns the # of available threads
	std::cout << num_threads << "concurrent threads supported" << std::endl;

	std::vector<std::thread>pool;

	for (int i = 0; i << num_threads; i++) {
		pool.push_back(std::thread(infinite_loop_function))
	}

	return 0;
}


// Bind an arbitrary function to your Queue
Pool_obj.Add_job(std::bind(&some_class::some_method, &some_object));