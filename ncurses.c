/* Ncurses example. still broken after quit looses terminal control 
 * requires gcc -Wall -pedantic c_queue2.c -o test -lncurses to compile
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>

int main() {
	
	 WINDOW * mainwin, * childwin;
    int      ch;
 
 
    /*  Set the dimensions and initial
	position for our child window   */
 
    int      width = 23, height = 7;
    int      rows  = 25, cols   = 80;
    int      x = (cols - width)  / 2;
    int      y = (rows - height) / 2;
 
 
    /*  Initialize ncurses  */
 
    if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }
 
 
    /*  Switch of echoing and enable keypad (for arrow keys)  */
 
    noecho();
    keypad(mainwin, TRUE);
 
 
    /*  Make our child window, and add
	a border and some text to it.   */
 
    childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 4, "Move the window");
    mvwaddstr(childwin, 2, 2, "with the arrow keys");
    mvwaddstr(childwin, 3, 6, "or HOME/END");
    mvwaddstr(childwin, 5, 3, "Press 'q' to quit");
 
    refresh();
 
 
    /*  Loop until user hits 'q' to quit  */
 
    while ( (ch = getch()) != 'q' ) {
 
		switch ( ch ) {
	
		case KEY_UP:
			clear();
			if ( y > 0 )
			--y;
			childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 4, "Move the window");
    mvwaddstr(childwin, 2, 2, "with the arrow keys");
    mvwaddstr(childwin, 3, 6, "or HOME/END");
    mvwaddstr(childwin, 5, 3, "Press 'q' to quit");
 
    refresh();
 
			break;
	
		case KEY_DOWN:
			clear();
			if ( y < (rows - height) )
			++y;
			childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 4, "Move the window");
    mvwaddstr(childwin, 2, 2, "with the arrow keys");
    mvwaddstr(childwin, 3, 6, "or HOME/END");
    mvwaddstr(childwin, 5, 3, "Press 'q' to quit");
 
    refresh();
 
			break;
	
		case KEY_LEFT:
			if ( x > 0 )
			--x;
			break;
	
		case KEY_RIGHT:
			if ( x < (cols - width) )
			++x;
			break;
	
		case KEY_HOME:
			x = 0;
			y = 0;
			break;
	
		case KEY_END:
			x = (cols - width);
			y = (rows - height);
			break;
	
		}
	
		/* this is deprecated as per bug 2006 
		* use the new version below
		*/
		// mvwin(childwin, y, x);


		// move(y,x); 
		// printw("%d, %d", y,x);
		wrefresh(childwin);
		
		// refresh();
		
    }
 
 
    /*  Clean up after ourselves  */
 
    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();
	
 

	return 0;
}