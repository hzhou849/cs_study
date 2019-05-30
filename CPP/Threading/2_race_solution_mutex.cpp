/*
 * Mutex example. Same problem as previous code, but now made
 * thread safe by adding mutex to lock one designated thread to complete
 * the critcal section of code that we want to execute atomically.
 * 
 * std::lock_guard
 * - lock_guard is a class template which implements the RAII
 *   (Resource aquisition is initialization) for mutext.
 *  It wraps the mutex inside it's object and locks the attached
 *  mutex in its constructor. When its destructor is called it 
 *  releases the mutex.
 */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
/*Counter.hpp */

#ifndef _COUNTER_HPP_
#define _COUNTER_HPP_

#endif _COUNTER_HPP_

class Counter {
private:
    int data;
    std::mutex mutexObj; // create a mutex object 
public:
    Counter() :data(0) {}
    int getData() {return data;}

    // version1 - using regular mutex
    // void addData(int value) {
    //     mutexObj.lock();    // acquire the mutex lock
    //     for(int i=0; i < value; i++) {
    //         data++;
    //     }
    //     mutexObj.unlock();
    // }

    // VERSION 2 - with std::lock_guard
    void addData(int value) {
        std::lock_guard<std::mutex> lockGuard(mutexObj); // make the wrap the mutext in lockGuard
        for (int i=0; i<value; i++) {
            //If some exception occurs at this
            //point, the desctructor of lockguard
            //will be called due to stack unwinding.
            data++;
        }
        //Once the function exits, the destructor
        //of lockGuard Object will be called.
        //In destructor it unlocks the mutex.
        
    }
};

int runTest() {
    Counter countObj;
    std::vector<std::thread> threads; // create vector to hold all the threads
    for (int i=0; i<5; i++) {
        threads.push_back(std::thread(&Counter::addData, &countObj, 1000));
    }

    // wait for all the threads to join
    for (int i=0; i<threads.size(); i++) {
        threads.at(i).join(); // same as threads.obj_array[i].join()
    }
    return countObj.getData();
}

/* Driver Class */
int main() {
    int value =0;
    int totalCount=0;

    // run 1000 tests - some will fail bc of unstable thread races
    for (int k=0; k <1000; k++ ) {
        value = runTest();
        if ((value = runTest()) != 5000) {
           
            std::cout << "Error at: " << k << " Value" << value << std::endl;
        } else {
            std::cout << "test# pass " << k <<" " <<value << std::endl;
            totalCount++;
        }
    }

    if (totalCount == 1000){
        std::cout << "all tests passed." <<std::endl;
    } else {
        std::cout << "failure in one of the tests" << std::endl;
    }
}