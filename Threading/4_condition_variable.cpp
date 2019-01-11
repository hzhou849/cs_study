/* Threading - Condition variables
 *
 * 
 * https://thispointer.com/c11-multithreading-part-7-condition-variables-explained/
 * std::unique_lock - more complex and good for condition variable
 *  - use with condition variable
 *  - has other features that allow it to be constructed w/o locking the mutex
 *    immediately but to build the RAII wrapper 
 * 
 * std::lock_guard - good if you only need to use it once.
 *  - also provides a convenient RAII wrapper, but cannot lock multiple mutexes safely.
 *  - can be used when you need a wrapper for a limited scope (eg. member function) 
 * 
 * The difference is that you can lock/unlock a std::unique_lock. The std::lock_guard will
 * be locked only once on construction and unlocked on destruction.
 * 
 * Condition variable 
 *  - is a kind of Event  used for signaling between two or more threads.
 *  - A mutex is required
 * 
 *  member function of std::condition_variable are:
 *  wait()          - wait for signal
 *                  - This will atomically release the attached mutex, block the current
 *                    thread, and add it to the list of threads waiting on current condition variable.
 *                    Thread will unblock when the notify() is called on that condition variable.
 *                  - wait will reacq the mutex lock and checks the condition is met or not, if not
 *                    it will release the lock, block the thread and goes into waiting
 * 
 *  notify_one()    - if any threads are waiting for same conditional variable 
 *                    object then notify_one unblocks one fo the waiting threads
 * 
 *  notify_all()    - if any threads are waiting on same conditional variable
 *                    object then notify_all unblocks all of the waiting threads.
 * 
 */

#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

//using namespace std::placeholders;

class Application {
private:
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    bool m_bDataLoaded;
public:
    Application() {m_bDataLoaded = false; }
    
    void loadData() {
        // Make this thread sleep to simulate load
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout <<"Loading data..." <<std::endl;

        // Lock_guard is used here because it will terminate on its own once out of scope.
        std::lock_guard<std::mutex> guard (m_mutex);    // Lock the data structure
        m_bDataLoaded = true;       // set the flag to true (data is loaded)
        m_condVar.notify_one();       // notify the condition variable.
    }

    bool isDataLoaded() {
        return m_bDataLoaded;
    }

    void mainTask() {
        std::cout << "Do some handshaking" << std::endl;

        // Acquire the lock
        std::unique_lock<std::mutex> u_lock(m_mutex);

        /* Start waiting for the Condition variable to get signaled.
         * Wait() will internally release the lock and make the thread block
         * as soon as  the CondVar gets signaled, resume the thread and
         * acquire the lock and check if the condition is met or not.
         * If condition is met, continue. Else, wait and repeat procedure.
            
         * std::bind(<function to pass>, <object Instance>)
         * m_condVar.wait(u_lock); // this can work too if you dont' want to rely on isDataLoaded() to be the signal
         * 
         * wait(arg2 overload) isDataLoaded() is used to ignore spurious(false positive) awakenings while waiting
         * for a specific condition to become true. 
         */
        m_condVar.wait(u_lock, std::bind(&Application::isDataLoaded, this)); // 'this' refers to this instance of object
        std::cout << "Processing the data loaded"<<std::endl;
    }
};

int main() {
    Application app;
    std::thread thread1(&Application::mainTask, &app);
    std::thread thread2(&Application::loadData, &app);
    
    thread2.join(); // loadData finishes first so it can be merged first.
    thread1.join();

    return 0;
}