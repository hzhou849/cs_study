/*
 * Stream manipulators
 * 
 * to use the manipulators you must #include <iomanip>
 * c++ streams have many useful member fucntiosn used to control formatting
 * can be used in both I/O streams
 * can be used as member fucntion or as a manipulato:
 * ie:
 * 	std::cout.width{10}; // member function
 * std::cout << std::setw{10}; // manipulato
 * 
 * when we manipulate a stream for formatting, sometimes the settings will be set for:
 * 1) the remainder of the program
 * 2) only affect the next object placed in the stream 
 * 3) or the  effect is immediate
 * 
 * 
 * Common stream manipulators
 * Boolean 
 * 	-boolalpha, noboolalpha // display true false or 1, 0
 * 
 * Integer - dec, hex, oc, showbase (show base prefix), noshowbase, showpos(show positive symbol), noshowpos, uppercase, nouppercase
 * 
 * Floting point - fixed, scientific, setprecision, showpoint, noshowpoint, showpos, noshowpos
 * 
 * Field width, justificiation and fill - setw, left, right, internal, setfill
 * 
 * others - endl, flush (flush out any stream buffers, doesn't use newline), skipws(skip whitspace), noskipws, ws
 * 
 */ 