/* std::packaged_task
 *
 * 	Required:
 * 	#include <future>
 * 
 * std::packaged_task< RETURN_TYPE (DATA_TYPE) > varName (functionPass);
 * std::future<dataType> results = varName.get_future();
 * 
 * - is a class template and represents async task.
 * 	- encapsulates:
 * 		1) A callable entity ie function, lambda functino or function object(struct).
 * 		2) A shared state that stores the value returned or thrown by associated callback.
 * 
 * 
 * 		Rule of thumb,
 * 		use AsyncIO if you want somethings done, but don't really care when they are done,
 * 		and packaged_task if you want to wrap things up in order to move around to ie 
 * 		other threads or call them later.
 * 	
 * 		
 */

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// simulate load function data fetcher
std::string getDataFromDB(std::string token) {
	//do something
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::string data = "Data fetched from DB by Filter ::  " + token;
	std::cout << "getDataFromDB done processing..." << std::endl;

	return data;
}
double process2 (double value) {
	std::this_thread::sleep_for(std::chrono::seconds(4));
		std::cout << "process2 done processing..." << std::endl;

	double data = value;
	return data;
}

/* Method 1 - package a function as arg */
// int main() {

// 	// Create a packaged_task<> that encapsulated the callback ie a function.
// 	std::packaged_task<std::string (std::string) > task(getDataFromDB);

// 	std::packaged_task<double (double)> task2(process2);

// 	//Fet the associated future<> from packaged_task<>
// 	std::future<std::string> result = task.get_future(); // future objects

// 	std::future<double> result2 = task2.get_future();			// future objects


// 	//pass the packaged_tas to processing thread to run asynchronously
// 	std::thread t1(std::move(task), "Arg");
// 	// std::thread t1(&task, "Arg");
	
// 	std::thread t2(std::move(task2), 2.782);

// 	//Fetch the result of packaged_task<> ie the return value by getDataFromDB()
// 	std::string data = result.get();	// *remember this will block
// 	double data2 = result2.get();



// 	// Merge the threads
// 	t1.join();
// 	t2.join();


// 	std::cout << data << " | " <<data2<< std::endl;

// 	return 0;

// }

/* Method 2 -   Using lambda in packaged_task */
// int main() {
// 	// Create a packaged_task<> that encapsulated a lambda functino
// 	std::packaged_task<std::string (std::string)> task([] (std::string token){
// 			//embedded lambda function do whatever
// 			std::string data = "Data from " + token;
// 			return data;
// 		});


// 	//Fetch the associated future<> from packaged_task<>
// 	std::future<std::string> result = task.get_future();

// 	//pass the packaged_task to thread to run asynchronously
// 	std::thread th(std::move(task), "Argxx");

// 	th.join(); // merge the threads

// 	//Fetch the result of packaged_task<> ie returned value by getDataFromDB()
// 	std::string data = result.get();
// 	std::cout << data << std::endl;

// 	return 0;
// }


/* Method 3 - passing function object (Structs) */

struct DBDataFetcher {
	std::string operator() (std::string token) { //operator () overload
		//Do stuff from fetchData
		std::string data = "Data from  " + token;
		return data;
	}
};

int main() {
	std::packaged_task<std::string (std::string)> task (std::move( DBDataFetcher() ) );
	std::future<std::string> result = task.get_future();

	// create a thread to do the process the packaged_task
	std::thread th(std::move(task), "method3");

	th.join(); // merge thread
	std::string data = result.get(); // Fetch the results 


	std::cout << data << std::endl;
}