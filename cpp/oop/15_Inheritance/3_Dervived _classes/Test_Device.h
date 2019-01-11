#ifndef _TEST_DEVICE_H_
#define _TEST_DEVICE_H_

#include "Device.h"

class Test_Device:public Device {
public:
    double eeprom_content;

    Test_Device();
    ~Test_Device();

    void input(double data);
    void output(double data);

};
#endif  // _TEST_DEVICE_H_