/* This example demonstrates the problem with passing references in threads if not 
 * managed properly. C++ will duplicate the object pass as its own instance for the scope 
 * of the thread, which can lead to different data in the main thread if merged back.
 */

#include <iostream>
#include <thread>

void threadCallback(int const & x) {
    // int &y = const_cast<int &>(x);
    int &y = const_cast<int &>(x); // const_cast used data to variable (y) that is not a const
                                    // so we can modify it.
    y++;
    std::cout << "Inside Thread x = " << x << std::endl;
}

// incorrect way to pass reference
// int main() {
//     int x = 9;
//     std::cout << "In Main thread: Before thread start x = " << x << std::endl;
//     std::thread threadObj(threadCallback, x);
//     threadObj.join();
//     std::cout << "In Main Thread: After Thread joins x = " << x << std::endl;
//     return 0;
// }

// correct way
int main() {
    int x = 9;
    std::cout << "In Main thread: Before thread start x = " << x << std::endl;

	// using std::ref(x) will pass the actual reference not create a copy
    std::thread threadObj(threadCallback,std::ref(x));
    threadObj.join();
    std::cout << "In Main Thread: After Thread joins x = " << x << std::endl;
    return 0;
}