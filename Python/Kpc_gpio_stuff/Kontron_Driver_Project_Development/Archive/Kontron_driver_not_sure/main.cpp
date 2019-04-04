// Copyright 2017 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

/***************************************************************
 * Kontron Fan speed driver - v1.0.0
 * 
 **************************************************************/

#include <sys/types.h>
#include <chrono>
#include <iostream>
#include <string>
#include <array>
#include <thread>

#include "DeviceDriver.h"


int main (int argc, char ** argv)
{
    DeviceDriver driver;

    std::uint32_t version = driver.getFirmwareVersion();
    std::printf("ite8516 firmware version: %02x.%02x.%02x.%02x\n",
        (version >> 24) & 0xFF, (version >> 16) & 0xFF, (version >> 8) & 0xFF, (version >> 0) & 0xFF);

    std::array<uint32_t, Device::NUM_GPIO> states;
    states.fill(0);

    for (DeviceDriver::GpioChannelIndex i = 0; i <Device::NUM_GPIO; ++i)
    {
        if(driver.canSetGpioDirection(i, DeviceDriver::GpioDirection::INPUT))
        {
            driver.setGpioDirection(i, DeviceDriver::GpioDirection::INPUT);
        }
        std::uint32_t state = driver.getGpioInput(i);
        std::printf("GPIO %2d in = %d\n", i, state);
        states[i] = state;
    } 

    while (true)
    {
        for (DeviceDriver::GpioChannelIndex i = 0; i< Device::NUM_GPIO; ++i)
        {
            std::uint32_t state = driver.getGpioInput(i);
            if(state != states[i])
            {
                std::printf("GPIO %2d in = %d\n", i, state);
                states[i] = state;
            }
        }
    }
}
