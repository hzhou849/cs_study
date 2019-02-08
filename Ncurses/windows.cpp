/* 
 *
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/printw.html
 */

int main() {
	wprintw(win, "Hi There !!!");
    wrefresh(win);
// As you will see in the rest of the document, naming of functions follow the same convention. For each function there usually are three more functions.

    printw(string);        /* Print on stdscr at present cursor position */
    mvprintw(y, x, string);/* Move to (y, x) then print string     */
    wprintw(win, string);  /* Print on window win at present cursor position */
                           /* in the window */
    mvwprintw(win, y, x, string);   /* Move to (y, x) relative to window */
                                    /* co-ordinates and then print         */
	return 0;
}