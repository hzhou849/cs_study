#include <cstdlib>
#include <iostream>
#include <ncurses.h>
// Conflict undef move
#include <chrono>
#undef move
// Conflict undef move
#include <thread>
#undef move
/* add extra libraries in project properties ->QNX c/c++ projects->categores-> select extra libraries and qnx look for
 * libncurses.a or any other so file
 * Make sure you 
 * #undef move conflicts in order to get this to work in momentics ide qnx 6.6
 */
int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	WINDOW *w_main = initscr();

	move(5,5);
	printw("working");

	refresh();
	getch();
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));


	endwin();
	return EXIT_SUCCESS;
}
