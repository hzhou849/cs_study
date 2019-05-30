/* IO STREAMS
 *
 * 	your program can send data to your devices
 * 	ie hardware, physical, hd, console, keyboard or virtual devices ie connection to webserver
 * - c++ provides a stream abstraction to work with IO devices
 * - C++ uses streams as an interface between program and input and output devices.
 * - stream is an interface that is independent of actual devices.
 *    from a programmer's perspective we can code to the stream and not worry about the actual device 
 * 	  connected to the stream
 * - a stream is exactly what you would expect, its a Sequence of bytes
 * - Input stream provides data to the program
 * - Output stream receive data from the program
 * 
 *  [input device ] --> [input stream] ---
 * 										  |
 * 										  v
 * 									[Program]
 * 										  |
 * 	[output Device] <-- [output stream]---
 * 
 * Common IO stream header files:
 * 1)iostream - provides definition for formatted input/output from/to streams
 * 2)fstream - Provides definition for formated input /output from /to file streams
 * 3) iomanip - provices definitions for manipulators used to format stream I/O
 * 			    allows us to format io steams in specific ways
 * 
 * common used stream classes:
 * ios		- provides basic support for formatted / unformatted I/O operations. Base class for most other classes
 * 
 * ifstream	- provides for high level input operations on file based streams
 *			 if you want to write to file you would declare you object as ofstream
 
 * ofstream - high level output operations on file based systems
 * 				if you want to write to file you would declare you object as ofstream
 * 
 * fstream - high level I/O operations on file based streams
 * 				dervived from ofstream and ifstream
 * 				=if we want to do read and write on the same file.
 * 
 * stringstream 	- provides highlevel I/O operations on memory based strings
 * 					derivided from istringstream and ostringstream
 * 
 * 
 * Global stream objects
 * - global objects initalizd before main executes
 * - best practice is to use cerr for error messages and clog for log messages.
 * 
 * cin		- standard input stream - by default connected to the standard input device(keyboard); 
 * 			buffered stream meaning input from cin won't be automatic until user pressed enter
 * 
 * cout		- std. output stream - default connected to statnd output device (console)
 *			 buffered stream meaning output only occurs when stream buffer fills up, use std::endl;
 *			or we flush the stream.
 *
 *
 *			Unbuffered meaning we get in/output from them as needed
 * cerr 	- std. error stream - default connected to standard error device (console)	
 * 				instance of ostream (unbuffered)
 * 
 * clog - std. log stream - default connected to standard log device (console)	
 * 				instance of ostream (unbuffered)
 * 
 * 
 * you can redirect IO ie bash >> << to redirect a stream 
 */ 