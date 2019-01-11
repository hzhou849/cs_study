#include <iostream>
#include "Device.h"

// Constructors
Device::Device() 
    : mem_content{0.0}, name {"default Device"}{

    
}


Device::~Device() {

}

void Device::input(double data) {
    std::cout << "Data input: " << data << std::endl;
}

void Device::output (double data) {
    std::cout << "Data outpu: " << data << std:: endl;
}