#include <iostream>

using namespace std;    // Use the entire std namespace
using std::cin;         // Use only what you need
using std::cout;
using std::endl;

int main() {
    cout<<"char: " << sizeof(char) <<" bytes" << endl;
    cout<<"int: " << sizeof(int) <<" bytes" << endl;
    cout<<"short: " << sizeof(short) <<" bytes" << endl;
    cout<<"unsigned int: " << sizeof(unsigned int) <<" bytes" << endl;
    cout<<"long int: " << sizeof(long int) <<" bytes" << endl;
    cout<<"long long int: " << sizeof(long long int) <<" bytes" << endl;
    cout<<"float: " << sizeof(float) <<" bytes" << endl;
    cout<<"long double: " << sizeof(long double) <<" bytes" << endl;
	return 0;
}