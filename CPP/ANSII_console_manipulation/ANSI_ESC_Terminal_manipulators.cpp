How to use the terminal manipulators
https://tldp.org/HOWTO/Bash-Prompt-HOWTO/x361.html

can also use \x1b = \033 if you prefer hex

//    - get current position: not sure to to extract this for c code use
      - "\x1b[6n";
// // - Position the Cursor:
// //   \033[<L>;<C>H
// //      Or
// //   \033[<L>;<C>f

// //   puts the cursor at line L and column C.
// // - Move the cursor up N lines:
// //   \033[<N>A

// // - Move the cursor down N lines:
// //   \033[<N>B

// // - Move the cursor forward N columns:
// //   \033[<N>C

// // - Move the cursor backward N columns:
// //   \033[<N>D

// // - Clear the screen, move to (0,0):
// //   \033[2J
// // - Erase to end of line:
// //   \033[K

// // - Save cursor position:
// //   \033[s
// // - Restore cursor position:
// //   \033[u

// COLOR KEY:

Black       0;30     Dark Gray     1;30
Blue        0;34     Light Blue    1;34
Green       0;32     Light Green   1;32
Cyan        0;36     Light Cyan    1;36
Red         0;31     Light Red     1;31
Purple      0;35     Light Purple  1;35
Brown       0;33     Yellow        1;33
Light Gray  0;37     White         1;37


//example of how to use dynamically  either wiht cout or sstream.
void Disp_buffer::con_write_str(std::string s, std::uint32_t offset_y, std::uint32_t offset_x)
{
	// // Order of this execution matters, adjust numbers as needed
	// std::cout << "\033[50A"; 	// move cursor up 50 rows?
	// std::cout << "\033[s";   	// Save the cursor position
	// std::cout << "\033[2J";  	// Clear the screen
	// std::cout << "\033[u";		// Restore the cursor position
	// // std::cout <<"\[\033[0;36m\]"; // Cyan colour? may not be supported.
	// // std::cout <<"\[\033[1;37m\]"; // bold grey?
	// // std::cout <<"\033c";			//rese

	std::stringstream osst;
	std::string temp_str;

	osst << "\033[" << offset_y <<"B";
	temp_str =osst.str(); 
	std::cout << temp_str << "TERMINAL TESTER: " << s << offset_x << std::endl;
	
	for (int i=0; i<10; i++)
	{
		std::cout << '\33' << '[' << i << 'C' << " testingC" <<std::flush;
		std::cout << '\x1b' << '[' << i << 'B' << " testingB" <<std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
	// std::cout << "\033[20B"
	


}
