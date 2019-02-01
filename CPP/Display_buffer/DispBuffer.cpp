/* Display GUI 
 *
 * MEthod 1 - Jagged array 
 *  Two Dimensional array is essentially an array of pointers to arrays, which can be initialized in a loop like:
 *  int **a = new int*[rowcount];
 * 
 * for (int i = 0; i < rowcount; ++i) {
 * 		a[i] = new int[100 * (sizeof(int))]
 * }
 * 
 * a[0] ----> a[0][0]  a[0][1]  a[0][2]
 * a[1] ----> a[1][0]  a[1][1]  a[1][2]
 * a[2] ----> a[2][0]  a[2][1]  a[2][2]
 * 
 * 
 * rember to free heap memory!!!
 * for (int i=0; i < rowcount; ++i) {
 * 		delete [] a[i]; // delete each sub-array 
 * }
 * delete []a; // delete the main array
 * 
 *   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
 * 0                 |			          
 * 1                 |
 * 2                 |
 * 3                 |
 * 4                 |
 * 5                 V
 * 6---------------> x
 * 7
 * 8
 * 9
 * 10
 * 
 * 
 * method 2 - prefered method. one contiguous space in memory.
 *  	     create a contiguous block of memory and mod the value 
 * 			 by column count to sepearate printout.
 *          - single dump printout, better performance. not fragmented in memory.
 * 
 * 	*note arrays are {yRow,xColum}, or array[iRow][jColumn] not tradition math {xCol,yRow}
 *  10 x 10 = 100 cells, to access cell ie {yRow8, xCol5}
 *  also arrays is zero indexed 0-99 rows and columns
 *  ___________________________________________ 
 * 	|use formula = yRow * max_column + xCol or |
 * 	|			array[iRow*max_columns + jCol] |
 *  |__________________________________________|
 * 				= (7 * 10) + 5 
 *              = 75th cell in heap allocated address
 *  char *buffer = new char*[(row * column) * (sizeof(char))];
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>

#ifndef _DISPBUFFER_H_
#define _DISPBUFFER_H_
class DispBuffer {
private:
	// need a way to track last cursor position, 
	int x;
	int y;
	// char **screenBuffer;
	char *scrBuffer; 	// Screen Buffer
	char *rulBuffer; 	// buffer with ruler
	int colMax;
	int rowMax;
	int totalBufferSize; //colMax * rowMax 
	int lastPosition[2]; // last cursor position 
	

public:
	DispBuffer(int colCount, int rowCount); // set somekinda of 2d array in heap memory.
	~DispBuffer();

	void bufferWriteLine(std::string s);		//write to array
	void bufferWriteLine(std::string s, int offset_x); // start position on x offset
	void setCursorPosition(int x, int y);
	void resetCurorPosition();


	//getters
	int getCursorX();	// get the current cursor position
	int getCursorY();	
	void dumpBuffer();  		// dump the current buffer output. with ruler
	void dumpBuffer_print();
	void writeChar(char data, int x, int y);
	void searchString();			//search for word or char and returns [col][row] all instances that occur   

};
#endif //_DISPBUFFER_H_

DispBuffer::DispBuffer(int colCount, int rowCount): x{0}, y{0}, scrBuffer{nullptr} {
	this->rowMax = rowCount;
	this->colMax = colCount;
	totalBufferSize = (colMax * rowMax);

	/*Method 2- Two dimensional array - contiguous memory 
	 * Creates a single [] in memory of the total number of cells x*y*/
	scrBuffer = new char[(rowCount * colMax) * (sizeof(char))];

	// add newline to end of each row
	
	for (int i =0; i< totalBufferSize ; i ++) {
		if (i >=0 && i %colMax == 0) {			// **greater or equal zero!! important
			std::cerr << "cell: " << i << std::endl;
			scrBuffer[i] = '\n';  // 0-(n-1) index 
		} 
	}
	
	if (scrBuffer != nullptr) {
		std::cout << "screen Buffer created!\n"
					<< "rows: " << rowMax<<"\n"
					<<"col: " << colMax <<"\n"
					<<"Total size: " << totalBufferSize << std::endl; 

	}

	
}

DispBuffer::~DispBuffer(){
	/* For method 1 only */
	// // delete the arrays
	// for (int i=0; i <row; i++) {
	// 	delete [] a[i];
	// }
	std::cout << "destructor freeing memory" << std::endl;
	// delete the pointers to the array
	delete [] scrBuffer;
}
void DispBuffer::dumpBuffer(){
	std::cout << scrBuffer << std::endl;
}


void DispBuffer::dumpBuffer_print() {
	int yAxisRuler = 0;

	/*Print the rulers X-Axis columns counter */
	std::cout << "  ";
	for (int i =0; i < colMax; i++) {
		if (i < 10){ // for ruler number < 10 (bc single char spacing)
			std::cout <<std::setw(2)<<" " << i <<"";
		} else {
			std::cout <<std::setw(1)<< " " << i <<"";
		}

		if (i != 0 && i % colMax == 0) 
			std::cout << std::endl;
	}
	std::cout << std::endl; // extra line btwn x-axis ruler for ease of readability

	/*Print the Y-Axis rows counter' & dump the screen buffer */
	// std::cout<<totalBufferSize << std::endl;
	for (int i=0; i < totalBufferSize; i++ ){
		// std::cout << "mod: "<<i% colMax << std::endl;
		// if (scrBuffer[i] == '\n') { //  (char)0
		// 	scrBuffer[i] = '#'; //''
		// }
		//on every new line, print the y_axis ruler
		// if ((i !=0) && (i % colMax== 0)) {
		// 	std::cout << std::endl;
		// }
		if(i % colMax == 1) {
			std::cout<<std::setw(3) <<std::left<<yAxisRuler;
			yAxisRuler++; // increment ruler by 1
		}
		if (scrBuffer[i] == '\0') { //  (char)0
			std::cout << std::setw(3)<<std::left<<" " <<"";			// fills with '*' characters
		}else if (scrBuffer[i] == '\n'){
			std::cout << std::setw(3) << std::left<<"\'\\n'" << "\n";		// fills '\n' with '#'
		}else {
			std::cout << std::setw(3)<<std::left<<scrBuffer[i] <<"";

		}
	}
	// carriage return for the console
	std::cout << std::endl;

}

/* formula: (rowY * colMax + xCol) = cellPosition */
void DispBuffer::writeChar(char data, int x, int y) {
	int cellPosition = 0;
	cellPosition = (y * this->colMax + x);

	this->scrBuffer[cellPosition] = data;
}
int DispBuffer::getCursorX() {
	return x;
}

void DispBuffer::writeLine() {

}




//Driver class
int main() {

	DispBuffer db(25, 25);
	// main image loop
	while(true){
		//  set teh initial positions
		std::cout <<"\033[50A";// order of this matters, you wnat to move the cursor up then save the position
		std::cout << "\033[s"; // save cursor position
		std::cout <<"\033[2J"; // clear the screen
		std::cout <<"\033[u"; //restor cursor position
		db.writeChar('#', 5, 2);
		db.writeChar('^',3,2);
		db.writeChar('|', 3, 3);
		for (int i =0; i< 25; i++) {
			std::cout <<"\033[50A";
			std::cout << "\033[s"; // save cursor position
			std::cout <<"\033[2J"; // clear the screen
			std::cout <<"\033[u"; //restor cursor position
				db.writeChar('\0', 5, 2+i-1);
				db.writeChar('\0', 3+i-1, 2+i-1); // cannot overwrite 0,0 you overwrote the '\n' char
				db.writeChar('\0', 3+i-1, 3+i-1);
				db.writeChar('#', 5, 2+i);
				db.writeChar('^',3+i,2+i);
				db.writeChar('-', 3+i,3+i);
			db.dumpBuffer_print();
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}
	
}

