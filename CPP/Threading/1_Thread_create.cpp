/* From https://thispointer.com/ */

#include <iostream>
#include <thread>
#include <chrono>

void thread_function() {
    for (int i=0; i <100; i++){
        std::cout << "thread executing function" << std::endl;
    }
    std::cout << "done" << std::endl;
}

/*  Time helper sleep function */
// n = seconds
void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout<<"pause for " << n << "seconds ended." << std::endl;
}

int main() {
    int var;
    std::thread threadObj (thread_function);
    threadObj.detach(); // this will serperate the thread but cannot rejoin - becareful

   
    //rejoin the sppawned thread back into main Thread
    std::cout << "Closing main thread..." <<"Thread id: " << threadObj.get_id()<<std::endl;
    //threadObj.join();
    std::cout << "Closing main thread..." <<"Thread id: " << threadObj.get_id()<<std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(2)); // allow threads to finish
    pause_thread(1);
    return 0;
}
