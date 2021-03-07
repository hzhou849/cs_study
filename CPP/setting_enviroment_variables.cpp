	
to set enviorment variables. LIke the TERM to change terminal mode,
you need to use putenv() and getenv() from C++ #include <cstlib>

putenv(const_cast<char *>("TERM=qansi"));  // set enviroment variable
	std::system("sh -c 'echo testing'");
	std::systsem("sh -c 'echo $TERM'");
	char *envar =  getenv("TERM"); // get Enviroment variable


std::system("sh -c 'echo testing'");
	std::system("sh -c 'echo $TERM'");
	char *envar =  getenv("TERM"); // get Enviroment variable

	// if TERM is already set to qansi do nothing
	// use strcmp to comapre strings 
	if (!strcmp(envar, "qansi"))
	{
		std::cout << "Terminal already set: " << envar << std::endl;
	}
	else
	{
		putenv(const_cast<char *>("TERM=qansi"));  // set enviroment variable
		char *envar2 =  getenv("TERM"); // get Enviroment variable
		std::cout << "Terminal is now configured! from: " << envar << " to: "<<envar2 << std::endl;

	}
