
class DispBuffer {
private:
	int x;
	int y;

public:
	DispBuffer(); // set somekinda of 2d array in heap memory.
	~DispBuffer();

	void bufferWrite();		//write to array
	void setCursorPosition(int x, int y);
	void resetCurorPosition();


	//getters
	void getCursorPosition();	// get the current cursor position
	void dumpBuffer();  		// dump the current buffer output.
	char* pointer(int column, int row); // pass x y and return the ptr value
	void searchString();			//search for word or char and returns [col][row] all instances that occur   

};
