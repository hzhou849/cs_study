/*
 *
 *  Getopt 
 * g++ -std=c++11 main.cpp -o main
 * 
 */

#include <getopt.h>
#include <iostream>



int num = -1;
bool is_beep = false;
float sigma  = 2.034;
std::string write_file = "default_write.txt";


void PrintHelp()
{
	std::cout <<
		"--num <n>:				Set the number of program\n"
		"--beep:				Beep the user\n"
		"--sigma <val>:			Set sigma of program\n"
		"--writeFile <fname>:	File to write to\n";
	std::exit(1);
}

void ProcessArgs(int argc, char** argv)
{
	
	const char* short_opts = "opn:bs:w:h";
	const option long_opts[] ={
		{"option1", no_argument, nullptr, 'o'},
		{"option2", no_argument, nullptr, 'p'},
		{"num", required_argument, nullptr, 'n'},
		{"beep", no_argument, nullptr, 'b'},
		{"sigma", required_argument, nullptr, 's'},
		{"writeFile", required_argument, nullptr, 'w'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, no_argument, nullptr, 0}  // required for false options

	};
	
	while (true)  // can also use this version for one line:  while ( (ch = getopt(argc, argv, "cwdrt1\r") ) != -1)
	{
		const auto opt =  getopt_long(argc, argv, short_opts, long_opts, nullptr);  // or just int opt=0 to initialize;

		if (-1 == opt)
			break;
		
		switch (opt)
		{
			case 'o':
			{
				char* var;
				int var2;
				std::cout << "OPTION 1 selected. Enter character:" << std::endl;
				std::cin >> var;
				std::cout << "var2: " << std::endl;
				std::cin >> var2;
				std::cout << "var: " << var << "var2: " << var2<< std::endl;
				break;

			}
			
			case 'p':
			{
				std::cout << "OPTIon 2 selected" << std::endl;
				break;
			}

			case 'n':
			{
				num = std::stoi(optarg);
				std::cout << "Num set to: " << num << std::endl;
				break;
			}

			case 'b':
			{
				is_beep = true;
				std::cout << "Beep is set to true\n";
				break;
			}
			
			case 's':
				sigma = std::stof(optarg);
				std::cout << "Sigma set to: " << sigma << std::endl;
				break;

			case 'w':
				write_file = std::string(optarg);
				std::cout << "Write file set to: " << write_file << std::endl;
				break; 

			/* Any of the 3 options below trigger help */
			case 'h': // -h or --help
			case '?': // unrecognized option

			default:
				PrintHelp();
				break;
		}


	}
}
int main(int argc, char **argv)
{
	ProcessArgs(argc, argv);
	return 0;
}


