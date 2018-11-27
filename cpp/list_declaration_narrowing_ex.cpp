#include <iostream>

using namespace std;    // Use the entire std namespace
using std::cin;         // Use only what you need
using std::cout;
using std::endl;

int main() {
   
   
    /*list declaration allows narrowing check 
     *
     * main.cpp:12:42: error: narrowing conversion of ‘9966217342047006033I128’ from ‘__int128’ to ‘long int’ inside { } [-Wnarrowing]
     * long var_a{11111111111111111110077777};
     * prevents narrowing ie from long to in or in this case
     * _int128 to int 64
     */
    long var_a{11111111111111111110077777};
    std::cout<< "var_a:"<< var_a << endl;

    

    return 0;
}