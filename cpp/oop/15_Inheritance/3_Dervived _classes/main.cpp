/* 17-2 Deriviing classes from exiting class
 *
 */

#include <iostream>
#include "Device.h"
#include "Test_Device.h"

int main() {
    // Use the Device class
    std::cout << "\n ===Device================" << std::endl;
    Device dev{};
    dev.input(2000.0);
    dev.output(100.0);
    std::cout << std::endl;

	// works the same with a pointer.
    Device *p_dev {nullptr};
    p_dev = new Device();
    p_dev->input(1000.0);
    p_dev->output(500.0);
    delete p_dev;

    // use the test_device sub class
    std::cout << "\n======Test_Device==========="<<std::endl;
    Test_Device test_dev{};
    test_dev.input(2000.0);
    test_dev.output(500);
    std::cout<<std::endl;

    Test_Device *p_test_dev {nullptr};
    p_test_dev = new Test_Device();
    p_test_dev->input(1000);
    p_test_dev->output(200);
    delete p_test_dev;

    


    return 0;
}