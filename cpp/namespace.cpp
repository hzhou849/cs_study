#include <iostream>

using namespace std;    // Use the entire std namespace
using std::cin;         // Use only what you need
using std::cout;
using std::endl;

int main() {
	int fav_number;
    int num1;
    double num2;

	std::cout<<"Enter your favourite number btwn 1 and 100: "<<std::endl;

	std::cin >>fav_number;

	std::cout<<"excellent"<<std::endl; //flush buffer and print out.
	std::cout<<"that is my fav " << fav_number << "too!" << std::endl;

    std::cout<<"Enter integer"<<std::endl;
    std::cin >>num1>>num2;              //if entered 10.5 the 0.5 will overflow into num2 bc there is something in the buffer
    cout<<"YOu entered: "<<num1<<endl;
    cout<<"endted: "<<num2<<endl;
	return 0;
}