#include <iostream>
#include <thread>
#include <vector>

// Counter.hpp
#ifndef _COUNTER_HPP_
#define _COUNTER_HPP_

class Counter {
private:
    int data;
public:
    Counter()
        :data(0) {
        }
    int getData() {
        return data;
    }

    void addData(int value) {
        for (int i=0; i < value; ++i) {
            data++;
        }
    }
};

#endif _COUNTER_HPP_

/*test function 
 *Creates counterObject and then 5 threads to increment the counter executed simultaneously,but not thread safe
 * which will cause unpredicatable results.
 * */
int runTest() {
    Counter countObj;
    std::vector<std::thread> threads; // create a vector to hold all the threads
    
    for (int i=0; i< 5; i++) {
        // to access class member function, pass the member function as callback function and pass pointer to object as 2nd argument
        threads.push_back(std::thread(&Counter::addData, &countObj, 1000)); // issues arise from passing references bc 
    }

    // wait for all the threads to join
    for (int i=0; i< threads.size(); i++) {
        threads.at(i).join();    // same as threads.obj_array[i].join()
    }

    return countObj.getData();
}

/* Driver class */
int main() {
    int value =0;
    for (int k =0; k < 1000; k++) { // 5 threads each increment 10 times, 5*10 = 50 times
        if ((value = runTest()) != 5000) {
            std::cout << "Error at: " << k << "Value" << value << std::endl;
        }
    }

    return 0;
}

