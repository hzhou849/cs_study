/* AsyncIO std::async
  *
  * 
  * Required package:
  * #include <future>
  * 
  * std::future<type> futureObj = std::async("");
  * 
  * Rule of thumb,
 * 		use AsyncIO if you want somethings done, but don't really care when they are done,
  * std::async() is a STL that accepts a callback( ie. function or function object) as an argument and potentially executes
  * them asynchronously
  * 
  * template<class Fn, class.. args>
  * future<typename result_of<Fn(Args...)>::type> async (launch policy, Fn&&, Args&&...args);
  * 
  * std::async returns a std::future<T> that stores value returned by function object executed by std::async(). 
  * args expected by function can be passed to std::async() as arguments after the function pointer argument.
  * 
  * 
  * Launch Policies - control the asynchronous behavious 
  * 
  * 1)std::launch::async
  * 	- guarantees the asynchronous behaviour ie. passed function will be executed on a seperate thread
  * 	- it automatically creates a thread (or piicks from internal threadpool) and a promise object for us.
  * 	- then passes the std::promise object to thread function and returns the associated std::future object.
  * 	- when passed arg function exits, its value will be set in this promise object and return value will be 
  *       available in std::future object.
  * 
  * 2)std::launch::deferred
  *  	- Non asynchronous behaviour ie.Function will be called when other thread will call get() 
  *       on future to access the shared state
  * 
  * 3) std::launch::async | std::launch::deferred
  * 	- default mode
  * 	- it can either run asynchronously or not depending on system load at the moment.
  * 
  * passable objects:
  * Function pointer
  * Function object
  * Lambda function
  * 
  * //calling std::async with a lambda function
                                                                                   *	std::future<std::string> resultFromDB = std::async([] (std::string recvdData){
  *			std::this_thread::sleep_for(std::chrono::seconds(5));
  *			
  *			return "DB_" + recvdData;
  *		}, "Data");
  * 
  * 
  * 
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <future>

std::string fetchDataFromDB(std::string recvdData) {
	// Make sure that fuction takes 5 seconds to complete
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//Do stuff like creating DB connection and fetch data
	return "DB_" + recvdData;
}

std::string fetchDataFromFile(std::string recvdData) {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return "FILE_" + recvdData;
}
/*  Calling std::async with fucntion object as callback */
struct DataFetcher {
	std::string operator() (std::string recvdData) {
	std::this_thread::sleep_for(std::chrono::seconds(5)); 
	}
};


int main() {

// calling the fucntion struct object (from main() )
std::future<std::string> fileResult = std::async(DataFetcher(), "Data");



	/* Method 1- Single Thread execution
	* in this example execute both fetchDataFromDB() and fetchDataFromFile() = 10secs
	*/

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now(); // Get start time
	std::string dbData = fetchDataFromDB("Data");
	std::string fileData = fetchDataFromFile("Data");

	auto end = std::chrono::system_clock::now(); // Get end time

	auto diff = std::chrono::duration_cast < std::chrono::seconds> (end -start).count(); // count() returns the number of ticks for this duration
	std::cout << "Single Thread - Total time take: " << diff << " Seconds" << std::endl;

	//combine the data
	std::string data = dbData + " :: " + fileData;

	//printing the combined data
	std::cout << "Data = " << data << std::endl;





	/* Method 2 - Async method 
	*
	* since both those fetch function are independant of each other, there is no
	* reason to have them run one after the other (waste of time). 
	* by running them parallel, we can save time
	* one way is to create a new thread pass a promise as an argument to thread function and
	* fetch the data associated std::future object in calling thread...
	* but the easier way is to use std::async!
	* */

	std::chrono::system_clock::time_point start2 = std::chrono::system_clock::now();
	std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Dataadf"); // std::async automatically returns a std::future<type> object

	std::string fileData2 = fetchDataFromFile("Dataasdgfas"); // using this main thread to run

	std::string dbData2 = resultFromDB.get();	// Fetch Data from DB (will block til data is available in future<std::string> object

	auto end2 = std::chrono::system_clock::now(); // end time
	auto diff2 = std::chrono::duration_cast<std::chrono::seconds> (end2-start2).count();
	std::cout << "\nTotal Time Taken = " << diff2 << " Seconds" << std::endl;

	std::string data2 = dbData2 + " :: " + fileData2;	// combine the data
	std::cout << "Async method - Data = " << data2 << std::endl;



	return 0;

}



