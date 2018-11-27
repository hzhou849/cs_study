#include <iostream>

using namespace std;    // Use the entire std namespace
using std::cin;         // Use only what you need
using std::cout;
using std::endl;

int main() {
   
    //PREFIX - pre increment
    int counter {10};
    int result {};

    result = ++counter;
    cout << "Counter: "<< counter << endl;
    cout << "result: "<< result << endl;

    //Postfix - post increment
    int counter2 {10};
    int result2 {};

    result2 = counter2++; // 10 gets assigned first to result2 then increments to 11
    cout << "Post_Counter2: " << counter2 << endl;
    cout << "result2: " << result2 << endl<<endl;
    

    // ANOTHER EXample
    int counter3 {10};
    int result3 {};

    cout << "Counter3: " << counter3 <<endl;
    result3 = ++counter3 + 10; // 1)increment counter first then add 10 so shoudl be 21
    // result3 = counter3++ + 10; // answer is 20 bc postfixed
    cout << "Counter3: " << counter3 << endl;
    cout << "result: " << result3 << endl;




    return 0;
}