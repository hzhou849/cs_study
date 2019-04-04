// Copyright 2017 Covidien LP
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by express written agreement with Covidien.

#ifndef EINSTEIN_KONTRON_DRIVER_DEVICE_H
#define EINSTEIN_KONTRON_DRIVER_DEVICE_H

#include "MappedIoDevice.h"

namespace einstein
{
namespace kontron_driver
{

/// \addtogroup library_kontron_driver
/// @{

/// \file Device.h

/// \brief Class to access device registers
class Device
{
public:

    /* command values */
    
    using Command = std::int32_t;

    static constexpr Command CMD_NONE           = 0x00;

    /* command values used for version information */

    static constexpr Command CMD_INFO           = 0x01;
    static constexpr Command CMD_INFO2          = 0x02;

    /* command values used for CPU health information */

    static constexpr Command CMD_GET_CPUTEMP    = 0x20;
    static constexpr Command CMD_GET_12V        = 0x28;
    static constexpr Command CMD_GET_AUTOTEMP   = 0x16;
    static constexpr Command CMD_SET_AUTOTEMP   = 0x17;

    /* command values used for WatchDog information */
    
    static constexpr Command CMD_SET_WATCHDOG   = 0x08;

    /* command values used for FAN information */

    static constexpr Command CMD_SET_FANMODE    = 0x11;
    static constexpr Command CMD_GET_FANRPM     = 0x1d;
    static constexpr Command CMD_GET_FANPWM     = 0x12;
    static constexpr Command CMD_SET_FANPWM     = 0x13;
    static constexpr Command CMD_GET_FANSPEED   = 0x14;
    static constexpr Command CMD_SET_FANSPEED   = 0x15;
    static constexpr Command CMD_GET_FANDIV     = 0x18;
    static constexpr Command CMD_SET_FANDIV     = 0x19;

    /* command values used for GPIO information */

    static constexpr Command CMD_GPIO_GETDIR    = 0x30;
    static constexpr Command CMD_GPIO_SETDIR    = 0x31;
    static constexpr Command CMD_GPIO_GET       = 0x32;
    static constexpr Command CMD_GPIO_SET       = 0x33;
    static constexpr std::uint32_t NUM_GPIO     = 18;
    
    enum GpioSetdirFlag : std::uint8_t
    {
        GPIO_SETDIR_INPUT   = 0x00,
        GPIO_SETDIR_OUTPUT  = 0x01,
        GPIO_SETDIR_PULLUP  = 0x08
    };

    /// \brief Class constructor, creates access to device IO region
    Device();

    /// \brief Default destructor
    ~Device() = default;

    /// \brief Reads data register
    std::uint8_t readData();

    /// \brief Writes data register
    void writeData(std::uint8_t data);

    /// \brief Writes command register
    void writeCommand(Command command);

private:

    /* IO region information */

    /// starting address of the device IO region
    static constexpr std::uintptr_t DEVICE_IO_BASE = 0x020C;
    /// number of bytes accessed in the device IO region
    static constexpr std::size_t DEVICE_IO_LENGTH = 2;

    /* register indices */

    /// Index offset of the data register from DEVICE_IO_BASE. Used for input and output
    static constexpr std::size_t DATA_REGISTER_OFFSET = 0;
    /// Index offset of the status register from DEVICE_IO_BASE. Used for input
    static constexpr std::size_t STATUS_REGISTER_OFFSET = 1;
    /// Index offset of the command register from DEVICE_IO_BASE. Used for output
    static constexpr std::size_t COMMAND_REGISTER_OFFSET = 1;

    /* status bits */

    /// Value of the status register that indicates OBF flag
    static constexpr std::uint8_t STATUS_OBF = 0x01;
    /// Value of the status register that indicates IBF flag
    static constexpr std::uint8_t STATUS_IBF = 0x02;
    /// Value of the status register that indicates BMODE flag
    static constexpr std::uint8_t STATUS_BMODE = 0x80;

    /* methods to handle status flags */

    /// \brief Waits for OBF flag to be set, so that data can be read from the controller's output buffer
    std::uint8_t waitForObfSet();

    /// \brief Waits for IBF flag to clear, so that data can be written to the controller's input buffer
    std::uint8_t waitForIbfCleared();

    /// \brief Waits for BMODE flag to clear, so that commands can be written to the controller
    std::uint8_t waitForBmodeCleared();

    /* methods to access registers */

    /// \brief Reads raw value from the data register
    std::uint8_t readDataRegister();

    /// \brief Reads raw value from the status register
    std::uint8_t readStatusRegister();

    /// \brief Writes raw value to the data register
    void writeDataRegister(std::uint8_t data);

    /// \brief Writes raw value to the command register
    void writeCommandRegister(Command command);

    einstein::os::io::MappedIoDevice<einstein::os::io::DeviceAccess::READ_WRITE> m_io;
};

/// @}

}
}

#endif
