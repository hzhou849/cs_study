/* Two Dimensional array on Heap
 *
 * https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
 * 
 *  TODO:
 * 1) Create second swap buffer to alternate
 * 2) add cstring - writeLine accepts str arg or const char* arg
 *    - if using std::string s, use s.at(i)
 * 3) store x,y coordinates in std::pair <int, int> array[100]; 
 * 
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
 * USE THIS METHOD!!!
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