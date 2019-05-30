#include <iostream>
#include "Test_Device.h"

Test_Device::Test_Device() 
    : eeprom_content {3.0} {

}

Test_Device::~Test_Device() {

}

void Test_Device::input(double data){
    std::cout << "Test_Device input: " << data << std::endl;
}

void Test_Device::output(double data) {
    std::cout << "Test_Device output: " << data << std::endl;
}