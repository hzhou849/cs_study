/* C++ Reading from a text file 
 * 
 * steps:
 * 1) #include <fstream>
 * 2) Declare an fstream or ifstream object
 * 3) Connect it to a file on your file system (opens it for reading)
 * 4) Read data from stream
 * 5) close the stream
 * 
 * 
 * i) fstream class - open for both Read/Write 
 *    // initialize and assign
 *    						args:{<location>, <mode (input)>}
 *    std::fstream in_file {"../myfile.txt", std::ios::in};
 *    
 *    // open for reading in binary mode
 *    std::fstream in_file {"../myfile.txt", std::ios::in | std::ios::binary};
 *    
 *    
 * ii) ifstream - used for read only.
 * 						2nd arg optional since this is read only
 * 		std::ifstream in_file {"../myfile.txt", std::ios::in(optional)};
 * 
 *		 //binary mode
 * 		std::ifstream in_file {"../myfile.txt", std::ios::binary};
 * 
 * iii) example - open file when we don't know name yet
 * 
 * 	    std::ifstream in_file;
 * 	    std::string filename;
 * 	    std::cin >> filename; //get the file name
 * 	    
 * 	    infile.open(filename);
 * 	    or 
 * 	    infile.open(std::ios::binary);
 *     
 *     
 *      Check if file is open successfully: (is_open)
 *      - either use this is_open()
 *      - or test the filestream object itself.
 * 
 * 		if (in_file.is_open() || in_file) {
 * 				//read from it
 * 		} else {
 * 			//file could not open
 * 			//terminate or try again?
 * 		}
 * 
 * iv) Close a file stream
 * 	in_file.close();
 * 
 * 
 * Reading from a file
 * -----------------------
 * 	 - use the stream extractor >> operator
 *   - stops after whitespace 'blah basdf adfadf'
 * 
 * 	- ie similar to cin
 * 
 * 		int num{};
 * 		double total {};
 * 		std::string name {};
 * 
 * 		in_file >> num;
 * 		in_file >> total >> name;
 * 	// you can combine streams extractions
	in_file >> num >> double_num >> string_text;
 * 
 * Read entire line from line:
 * ----------------------------
 * 	ex1;
 * 		std::string line{};
 * 		std::getline(in_file, line);
 * 
 * Read a whole file - all lines:
 * ------------------------------
 * 	std::ifstream in_file{../myfile.txt"}; 	//open file
 * 	std::string line {};
 * 	
 * 	in (!in_file) { 	//error checking
 * 			std::cerr << "File open error" << std::endl;
 * 			return 1;
 * 	} 
 * 	
 * //method 1 using eof() - may not work in mac/linux properly; win ok
 * // linux and mac handlel EOF a little different - test first
 * 
 * 	while (!in_file.eof()) {			// while not end of file check
 * 		std::getline(in_file, line)		//read the line
 * 		std::cout << line << std::endl; // display the line
 * 	}
 * 
 * //method 2 - embedded the getline itself  into the loop
 *  - **USE this method if above doesn't work. 
 *   this works bc if the getline() is successful, run loop else, quit
 * 	while (std::getline{in_file, line}) {
 * 		std::cout << line << std::endl;
 * 	}
 * 	
 * 	in_file.close();			//close the file
 * 
 * Read a one character at a time: - unformatted input
 * get(char c);
 * ------------------------------
 * - processes characters unformatted, will read and interpret
 *   newlines, and whitespace, output will look just like getline
 * char c;
 * while (in_file.get(c)) //read a character at a time
 * 		std::cout << c;
 * 	

 */ 


