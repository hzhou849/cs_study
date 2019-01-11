/* 17-7 Redefining Base class methods
 * 
 */

//Device.hpp
#include <iostream>

#ifndef _DEVICE_H_
#define _DEVICE_H_
class Device {
    friend std::ostream &operator<<(std::ostream &os, const Device &device);
protected:
    double data;
public:
    Device();
    Device(double data);
    void input(double write);
    void hash(double read);
};

#endif // _DEVICE_H_


//Device.cpp

//#include "Device.hpp"
Device::Device()
    :Device{0.0} {    // Delegating constructor
}

Device::Device(double data)
    :data{data}     {   // 0.0 from no args constructor    
}

void Device::input(double write) {
    if (write > 0) {
        data += write;
    } else {
        std::cout << "write is zero" << std::endl;
    }
}

void Device::hash (double key) {
    if (data-key >=0) 
     data -= key;
    else
        std::cout<<"data insufficient" << std::endl;

}


std::ostream &operator <<(std::ostream &os, const Device &device) {
    os << "Device value" << device.data;
    return os;
}