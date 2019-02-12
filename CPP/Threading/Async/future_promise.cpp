/* Async IO -  Future Promise
 * 
 * 
 * Need for future/promise
 * in tradition threading with mutex if we wanted to get a value
 * we would have used a condition variable, mutex and a pointer.
 * 3 items involved to return one value, while this worked, if we
 * tried to sync multiple different values, the problem will become
 * more complex. This introduces a simpler solution for returning values 
 * from threads
 */

#include <iostream>
#include <thread>
#include <future>

void initializer(std::promise<int> * promObj) {
	std::cout << "Inside Thread" << std::endl;
	promObj->set_value(35);	// set the promise object value
}

int main() {
		std::promise<int>  promiseObj;
		/* Every std::promise object  has an associated future object through 
		 * which others can fetch the value set by promise 
		 * 
		 * */
		std::future<int> futureObj = promiseObj.get_future(); // link the promise object to this future object
		
		std::thread th(initializer, &promiseObj);// now main thread will pass the promiseObj to thread 2


		/* NOTE: this will block */
		int val = futureObj.get(); // Main thread will fetch the value set by Thread2 in std::promise through std::future get function

		std::cout << "returned value: " << val << std::endl;
		th.join();
		

	return 0;
}

