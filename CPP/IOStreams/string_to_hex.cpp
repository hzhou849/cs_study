/* Convert string to hex value */
template <class Type>
std::uint32_t convert_to_hex(std::string data_str, Type &output)
{
	try
	{
		std::stringstream interpreter;
		interpreter << std::hex << data_str;
		interpreter >> output;
		return EXIT_SUCCESS;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	
}
