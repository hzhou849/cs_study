/* Ncurses example
 *
 * TO COMPILE: 
 *  g++ -I. -Wall -std=c++11   -o main ncurses.cpp  -lncurses
 *  ** -lncurses directive flag must be added to the end of the compile line. 
 *     this is because object files and libraries are linked in order in a single pass.
 * 
 * initscr() - starts Ncurses mode, must be used to enable ncurse, may also clear terminal on execution
 * refresh() - NOTE: only updates the portion of where changes occured improves perfomance, but need to be careful
 * 
 * raw() and cbreak()  - disable line buffering. in raw() mode, char are directly passed to the program
 * 					     w/o generating a signal. 
 * 						- cbreak()  mode, these control characters are interpreted as any other character by the terminal driver
 * echo() noecho()	   - controls echoing of characters typed by the user to the terminal. ie supressing uneccessary echoing while
 * 						taking input from the user through getch()
 * 
 * keypad()				- enables readings of F1, F2.. arrow keys etc..  Do (stdscr, TRUE) to enable this feature for regular
 * 						  screen  (stdscr). 
 * 
 * halfdelay() 			- used to enable half-delay mode, similar to cbreak() mode in that chars typed are immediately available
 * 						 to program. However, it waits for 'X' tenths of a second for input and the returns ERR if no input is 
 * 						available. ie a timeout for password input.
 */
#include <iostream>
#include <ncurses.h>

int main() {
	/* Example 1 */
	// initscr();			// start Ncurses mode
	// printw("Hello world!!");		// prints to a buffer window called stdscr at (y,x) or [0,0] by default.

	// refresh();						//dump the stdscr buffer to our actual screen
	// getch();						// 

	// endwin();						// End curses mode - frees memory  and switches back to terminal mode.

	/*version 2*/
	int ch;
	initscr();				// start curses mode
	raw();					// Line buffering disabled
	keypad(stdscr, TRUE);		// enable function keys F1, F2 etc..
	noecho();					// Don't echo() while we do getch

	printw("Type any character to see in bold\n");
	ch = getch();				//If raw() was not used, we would have to press enter before it gets to the program

	if (ch == KEY_F(1))		{	// keypad enable for this to work
		printw("F1 key pressed"); // w/o noecho() some ugly escape chars might have been printed on the screen
	} else {
		printw("The pressed key is ");
		attron(A_BOLD);			// Enable Bold attribute
		printw("%c\n", ch);
		attroff(A_BOLD);		// turn off Bold attribute
	}

	refresh();					// print it on to the real screen
	std::cout << "press anykey to exit" << std::endl;
	getch();					// Wait for user input
	endwin();					// End curses mode





	return 0;
}