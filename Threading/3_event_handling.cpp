/* Event -Handling,
 *
 * In this scenario Thread 1 will keep checking until thread 2 value changes and thread1 
 * will continue processing.
 * 
 * the problem with this is the wasted cpu cycles in main task while loop
 * constantly locking and unlocking the mutex 
 */

#include <iostream>
#include <thread>
#include <mutex>

class Application {
private:
    std::mutex m_mutex;
    bool m_bDataLoaded;
public:
    Application() { m_bDataLoaded = false;}
   
    void loadData() {
        // make This thread sleep for 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // Lock the Data structure
        std::lock_guard<std::mutex> guard(m_mutex);
        //set the flag to true --> Data is loaded
        m_bDataLoaded = true;
        std::cout << "Loading Data from XML" << std::endl;
    }

    void mainTask() {
        std::cout << "Do some handshaking" << std::endl;

        // Acquire the lock
        m_mutex.lock();
        //****critical section start******
        //check if the flag is set to true?

        while (m_bDataLoaded != true) {
            std::cout << "waiting for data to be loaded..." << std::endl;
            // the problem here is the wasted cpu cycles and locking/unlocking the mutex
            // making this thread slow.
            m_mutex.unlock();   //Release the lock to give loadData
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sleep for 100ms
            m_mutex.lock();     // Acquire the lock
        }
        //****critical section end******
        m_mutex.unlock(); // Release the lock
        std::cout << "process the loaded data" << std::endl;
    }
};

int main() {
    Application app;
    std::thread thread_1(&Application::mainTask, &app);
    std::thread thread_2(&Application::loadData, &app);

    thread_2.join();
    thread_1.join();

    return 0;
}