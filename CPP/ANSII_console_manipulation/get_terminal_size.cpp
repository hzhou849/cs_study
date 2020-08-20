/* Get the size of the terminal window */


#include <sys/ioctl.h>  // required for winsize struct
#include <utility>	// required for this as well for the struct item

function()
{	
	struct winsize term_info;

	// get the terminal max values
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_info);

	std::uint16_t start_y = term_info.ws_row;
	std::uint16_t start_x = term_info.ws_col;

	std:: cerr << "Rows: " << start_y << " Col: " << start_x << std::endl;
}
