// Copyright 2017 Covidien LP
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by express written agreement with Covidien.

#include "einstein/kontron_driver/Device.h"

#include "einstein/kontron_driver/exceptions/KontronDeviceException.h"

namespace einstein
{
namespace kontron_driver
{

Device::Device() :
    m_io(DEVICE_IO_BASE, DEVICE_IO_LENGTH)
{
}

std::uint8_t Device::readData()
{
    waitForObfSet();
    return readDataRegister();
}

void Device::writeData(std::uint8_t data)
{
    waitForIbfCleared();
    writeDataRegister(data);
}

void Device::writeCommand(Command command)
{
    waitForBmodeCleared();
    writeCommandRegister(command);
}

std::uint8_t Device::waitForObfSet()
{
    constexpr std::size_t NUM_ATTEMPTS = 10000;
    for (std::size_t i = 0; i < NUM_ATTEMPTS; ++i)
    {
        auto status = readStatusRegister();
        if ((status & STATUS_OBF) != 0)
        {
            return status;
        }
    }
    throw exceptions::KontronDeviceException("ITE8516 timed out while waiting for OBF flag to be set");
}

std::uint8_t Device::waitForIbfCleared()
{
    constexpr std::size_t NUM_ATTEMPTS = 10000;
    for (std::size_t i = 0; i < NUM_ATTEMPTS; ++i)
    {
        auto status = readStatusRegister();
        if ((status & STATUS_IBF) == 0)
        {
            return status;
        }
    }
    throw exceptions::KontronDeviceException("ITE8516 timed out while waiting for IBF flag to be cleared");
}

std::uint8_t Device::waitForBmodeCleared()
{
    constexpr std::size_t NUM_ATTEMPTS = 10000;
    std::uint8_t status = waitForIbfCleared();

    for (std::size_t i = 0; i < NUM_ATTEMPTS; ++i)
    {
        writeCommandRegister(CMD_NONE);
        waitForIbfCleared();
        readDataRegister();
        status = readStatusRegister();
        if ((status & STATUS_BMODE) == 0)
        {
            return status;
        }
    }
    throw exceptions::KontronDeviceException("ITE8516 timed out while waiting for BMODE flag to be cleared");
}

std::uint8_t Device::readDataRegister()
{
    return m_io.read<std::uint8_t>(DATA_REGISTER_OFFSET);
}

std::uint8_t Device::readStatusRegister()
{
    return m_io.read<std::uint8_t>(STATUS_REGISTER_OFFSET);
}

void Device::writeDataRegister(std::uint8_t data)
{
    m_io.write<std::uint8_t>(DATA_REGISTER_OFFSET, data);
}

void Device::writeCommandRegister(Command command)
{
    m_io.write<Command>(COMMAND_REGISTER_OFFSET, command);
}

}
}
