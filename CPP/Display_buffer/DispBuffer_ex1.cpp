
#include <iostream>
#include <string>

int main() {
	int rowCount = 100;
	int columnCount=100;
	char **a = new char*[rowCount];
	void *ptr= nullptr;
	
	char const *str = new char[10 +1]; // +1 for null terminator
	str = "ta-dah";

	str = "adfasf";


	std::cout << str << std::endl;
	// strcpy(str, "somethingelse");
	std::cout << str << std::endl;
	
	for (int i=0; i < rowCount; i++){
		a[i] = new char [columnCount *(sizeof(char))];
	}

	a[0][0] = 'a';
	a[0][1] = 'b';
	a[1][1] ='c';
	a[0][2] = '\0' ;
	//print array
	for (int i =0; i< 5; i++) {
		
		for (int j=0; j < 5; j++){
			ptr= static_cast<void*>(std::addressof(a[i][j]));
			// std::cout << "a["<<i << "]" << "[" << j<<"]: " << a[i][j]<< " "<< ptr<< " "; // debug statement
			// std::cout << static_cast<void*>(std::addressof(a[i][j])); // get the address of
			std::cout << a[i][j];
			if ( (j==4) ) 
				std::cout <<std::endl;
		}
	}

	
	



	// free memory
	for (int i=0; i < rowCount; i++) {
		delete [] a[i];
	}
	delete [] a;
	
}