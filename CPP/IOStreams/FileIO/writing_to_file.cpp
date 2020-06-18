/* C++ writing to file
 *
 * Output file  FSTREAM OFSTREAM
 * 
 * steps:
 * 1) #include <fstream>
 * 2) Declare fstream or ofstream object
 * 3) connect it to a file (opens for writing)
 * 4) write data to the file via the stream
 * 5) close the stream - flushes any buffers that have not been written out yet.
 * 
 * by default, c++ will create the file if does not exist,
 * if does exist, file will be overwritten.
 * 
 * 
 * fstream - Read and Write object:
 * ---------------
 * std::fstream out_file {"../myFile.txt", std::ios::out};
 * std::fstream out_file {"../myFile.txt", std::ios::out | std::ios::binary}; // binary mode
 * 
 * ofstream - write/output only
 * ----------------------------
 * std::ofstream out_file {"../myFile.txt"}; //std::ios::out is optional, since it is default write only
 * std::ofstream out_file {"../myFile.txt", std::ios::binary};  //binary mode
 * 
 * ***write one char at a timeuse .put(char c);
 * 
 * Opening file modes:
 * -------------------
 * A) Truncation (discard contents when opening) -DEFAULT 
 * std::ofstream out_file("../myfile.txt", std::ios::trunc);
 * 
 * B) Append on each write
 * std::ofstream out_file("../myfile.txt", std::ios::app);
 * 
 * C) seek to end of stream when opening (append to end)
 *    - used when we want to open a file that exists and 
 *      sets the initial position of the next write to the end of file.
 *    - but we are free to move around and random access
 * 
 * std::ofstream out_file("../myfile.txt", std::ios::ate);
 * 
 * 
 * example1:
 * std::ofstream out_file;
 * std::string filename;
 * std::cin >> filename; //get the name of file
 * 
 * out_file.open(filename);
 * or
 * out_file.open(filename, std::ios::binary);
 * 
 * 
 * error checking:
 * if (out_file.is_open()) {		// returns boolean 
 * 		//do something
 * } else{
 * 		// terminate
 * }
 * 
 * or 
 * if (out_file)  // just check the object
 * 
 * 
 * closing a file: - flushes any remaining buffers
 * ---------------
 * out_file.close()
 * 
 */
#include <iostream>
#include <fstream> // required for filestreams
#include <string>
//writing to a file
int main() {
	int num {100};
	int total {222.455};
	std::string name {"blah"};

	std::ofstream out_file;
	//note: std::endl flush out any unwritten buffers
	out_file << num << "\n" << total << "\n" << name <<"\n" << std::endl;

	//example 2: copies one file to another
	std::ifstream in_file{"../myFile.txt"}; //open file for read
	std::ofstream out_file{"../copy.txt"}; // create file for write

	if (!in_file){		//check if file is open
		std::cerr << "File open error" << std::endl;
		return -1;
	}

	if (!out_file) { 	// check if file is open
		std::cerr << "File create error" << std::endl;
		return -1;
	}

	/* Method 1 - line buffer */
	std::string line_buffer {};
	while (std::getline(in_file, line_buffer)) // read a line
		out_file << line_buffer << std::endl;	// write a line
	
	/*method 2 - one character at a time */
	char c;
	while (in_file.get(c))	// read a char
		out_file.put(c);	//write a char

	// close the streams
	in_file.close();
	out_file.close();


}
