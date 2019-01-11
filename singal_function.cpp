/*
 * Signal handling 
 * 1	- SIGABRT
		Abnormal termination of the program, such as a call to abort.
 * 2	- SIGFPE
 * 		An erroneous arithmetic operation, such as a divide by zero or an operation resulting in overflow.
 * 
 * 3	- SIGILL - Detection of an illegal instruction.
 * 
 * 4	- SIGINT - Receipt of an interactive attention signal.
 * 
 * 5	SIGSEGV - An invalid access to storage.
 * 
 * 6	SIGTERM - A termination request sent to the program.
 * 
 * Whatever signal you want to catch in your program, 
 * you must register that signal using signal function and associate it with a signal handle
 * 
 * raise() - You can generate signals by function raise(), which takes an integer 
 * 			signal number as an argument and has the following syntax.
 * */

#include <iostream>
#include <csignal>
#include <chrono>
#include <thread>

void signalHandler (int signum) {
	std::cout << "Interrupt signal(" << signum << ") received." << std::endl;

	// cleanup and close up stuff here
	// terminate program

	exit(signum);
}

int main() {
	int i = 0;

	// register signal SIGINT and signal handler
	signal(SIGINT, signalHandler);

	while(++i) {
		std::cout << "Sleeping..." << std::endl;
		if (i == 3) {
			raise(SIGINT);// trigger the interrupt signal
		}
		std::chrono::milliseconds timespan(1000);
		std::this_thread::sleep_for(timespan);
	}

	return 0;
}

