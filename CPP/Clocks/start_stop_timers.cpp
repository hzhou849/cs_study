

int main() {

// calling the fucntion struct object (from main() )
std::future<std::string> fileResult = std::async(DataFetcher(), "Data");



	/* Method 1- Single Thread execution
	* in this example execute both fetchDataFromDB() and fetchDataFromFile() = 10secs
	*/

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now(); // Get start time


	
	std::string dbData = fetchDataFromDB("Data");
	std::string fileData = fetchDataFromFile("Data");

	auto end = std::chrono::system_clock::now(); // Get end time

	auto diff = std::chrono::duration_cast < std::chrono::seconds> (end -start).count(); // count() returns the number of ticks for this duration
	std::cout << "Single Thread - Total time take: " << diff << " Seconds" << std::endl;

	//combine the data
	std::string data = dbData + " :: " + fileData;

	//printing the combined data
	std::cout << "Data = " << data << std::endl;
