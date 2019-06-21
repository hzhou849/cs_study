/* boost::program_options 
 * a boost version of the getopt
 * 
 * option w shows how to implement hex input from command line
 * 
 */

#include <iostream>
#include <boost/program_options.hpp> // reaquired boost package

namespace po = boost::program_options; // if a shorthand alias is preferred.

/* Try catch version */
int main(int argc, const char * argv[])
{
    // Declare the supported options
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce this message")
            ("write,w", po::value<std::string>(), "Write value (ex: -w 0xffff), Read is default")
            ("otp,o",  "specifies One-Time-Programmable memory, RAM is default")
            ("bank,b",     po::value<std::uint16_t>(), "Bank (0-3)")
            ("register,r", po::value<std::uint16_t>(), "Register (0-7)")
            ("verbose,v", "verbose");


	// **** IMPORTANT placement of the try statement must be placed here for the above stuff
	// to live in catched scope
	try{		
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		

		// If specifying OPT, then bank & register is required
		if (vm.count("otp"))
		{
			if (!vm.count("bank") || !vm.count("register") || vm.count("help"))
			{	std::cout << "Must specify a bank value 0-3.\n" << std::endl;
				std::cout << desc << std::endl;
				return EXIT_SUCCESS;
			}
		}
		else if (!vm.count("register") || vm.count("bank") || vm.count("help"))
		{
			std::cout << "Must specify a register value 0-7\n" << std::endl;
			std::cout << desc << std::endl;
			return EXIT_SUCCESS;
		}
			
		std::uint16_t bank = 0;		// default is 0 for RAM write.
		if (vm.count("bank"))
		{
			bank = vm["bank"].as<std::uint16_t>() & 0x03;  				// Mask bank and reg to prevent access  (0-3 banks)
		}
		std::uint16_t reg = vm["register"].as<std::uint16_t>() & 0x07; // Mask register access (0-7)
		bool otp = vm.count("otp");



		// debug cout
		std::cout << "debug bank: " << std::hex << static_cast<std::uint16_t>(bank) << ", reg: "
							<< std::hex << static_cast<std::uint16_t>(reg) << std::endl;

		// Create Pga308 object
		Pga308 pga;


		// If doing a write... else default is read
		if (vm.count("write"))
		{
			if (vm["write"].empty())
			{
				std::cout << "Write -w option requires a data value" << std::endl;
				std::cout << desc << std::endl;

				return EXIT_SUCCESS;
			}
		
			std::uint16_t writeData;
			std::stringstream interpreter; 				// used for string to hex conversion

			// convert string to hex number
			interpreter << std::hex << vm["write"].as<std::string>();
			interpreter >> writeData;


			pga.write(otp, bank, reg, writeData); 		// Write the data		
		}
		else 
		{
			pga.read(otp, bank, reg);					// Perform read operation
		}
	return EXIT_SUCCESS;
	}
	catch (po::error &e)  
	{	
		std::cout << "catched" << std::endl;
		std::cout << e.what() <<"\n" << std::endl;
		std::cout << desc << std::endl;
		// return EXIT_SUCCESS;
	}
}

// #include <iostream>
// #include <boost/program_options.hpp> // reaquired boost package

// // namespace po = boost::program_options; // if a shorthand alias is preferred.

// int main(int argc, const char * argv[])
// {
// 	//Declare the supported options
// 	boost::program_options::options_description desc ("Allowed options usage: \t1) set -o -b (0-1) first then \n\t\t\t2) -o -r (0-7)");
// 	desc.add_options()
// 	// no spaces after , comma
// 	("help,h", 	"produce this message")
// 	("write,w", 	boost::program_options::value<std::uint16_t>(), "Write, Read is default")
// 	("otp,o",		"Specifies One-Time-Programmable memory, RAM is default")
// 	("bank,b",		boost::program_options::value<std::uint16_t>(), "Bank (0-3)")
// 	("register,r", 	boost::program_options::value<std::uint16_t>(), "Register(0-7)")
// 	("hextest,x", boost::program_options::value<std::string>(), "hex value (0h - ffffh")
// 	("verbose,v", "verbose");

// 	boost::program_options::variables_map vm;
// 	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm); //Stores in 'vm' all options that are defined in 'options'. 
// 	boost::program_options::notify(vm);

// 	// If specifying OPT, then bank & register is required
// 	//vm.count() checks to see if option is present returns boolean 0 or 1 T/F
// 	std::cout << "opt: " << vm.count("opt") << std::endl;
// 	if (vm.count("otp"))
// 	{
// 		std::cout << "register " << vm.count("register") <<" "<< "bank: " << vm.count("bank")  << " " << vm.count("help")<<std::endl;
// 		if (!vm.count("bank") || !vm.count("register") || vm.count("help"))
// 		{
// 			std::cout << "usage: 1) set -o -b (0-1) first then \n\t2) -o -r (0-7)" << std::endl;
// 			std::cout << desc << std::endl;
// 			return EXIT_SUCCESS;
// 		}
// 		else if (!vm.count("register") || vm.count("bank") || vm.count("help"))
// 		{
// 			std::cout << desc << std::endl;
// 			return EXIT_SUCCESS;
// 		}

// 	}

// 	std::uint16_t bank =0;
// 	if (vm.count("bank"))
// 	{
// 		bank =  vm["bank"].as<std::uint16_t>() & 0x03;	//.as is a cast
// 	}

// 	if (vm.count("hextest"))
// 	{
// 		std::uint16_t hexValue;
// 		std::stringstream interpreter;

// 		interpreter << std::hex << vm["hextest"].as<std::string>();
// 		interpreter >> hexValue;

// 		std::cout << std::hex << std::showbase <<"hex entered:" << hexValue << std::endl;
// 		std::cout << std::dec << "decimal: " << hexValue << std::endl; 
// 		return EXIT_SUCCESS;
// 	}

// 	std::uint16_t reg = vm["register"].as<std::uint16_t>() & 0x07;
// 	bool otp = vm.count("otp");

// 	std::cout << "bank: " << std::hex << static_cast<std::uint16_t>(bank) << ", reg: "
// 						  << std::hex << static_cast<std::uint16_t>(reg) << std::endl;
	
// 	return EXIT_SUCCESS;
// }

