// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#ifndef EINSTEIN_OS_IO_MAPPEDIODEVICE_H
#define EINSTEIN_OS_IO_MAPPEDIODEVICE_H

#include "DeviceAccess.h"
#include "MappedIoAddress.h"
#include "AssertAligned.h"
//#include <hw/inout.h>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace einstein  //SUPPRESS: Code Before #include
//REASON:   Including the implementation of inline methods at the end of the file is required by
//          the coding standard.
{
namespace os
{
namespace io
{

/// Provides access to hardware that uses memory based I/O operations.
/// Wraps the OS's mmap_device_io and acquires required privileges.
/// \tparam Access Specifies how the device is going to be accessed (read, write or both).
/// \author Jan Tully
template <DeviceAccess Access>
class MappedIoDevice
{
public:
    /// Constructor.
    /// \param[in] physical_address The physical address of a device interface.
    /// \param[in] size The width of the memory interface.
    /// \throw info::Error If an error occurred.
    MappedIoDevice(const std::uintptr_t physical_address, const std::size_t size);

    /// \return Access mode as passed as template parameter.
    DeviceAccess getAccess() const noexcept;

    /// \return Width of the I/O interface as passed to the constructor.
    std::size_t getSize() const noexcept;

    /// Performs a read operation on the device.
    /// \tparam T Type of data that is to be read.
    /// \param[in] offset Offset in bytes relative to the start of the provided physical address.
    /// \param[out] result Buffer where the result can be stored
    /// \throw std::logic_error On internal errors.
    /// \throw info::Error If an error occurred while requesting privileges.
    template <class T>
    void read(const std::size_t offset, T * result);

    /// Performs a read operation on the device.
    /// \tparam T Type of data that is to be read.
    /// \param[in] offset Offset in bytes relative to the start of the provided physical address.
    /// \return Data read from device interpreted as T.
    /// \throw std::logic_error On internal errors.
    /// \throw info::Error If an error occurred while requesting privileges.
    template <class T>
    T read(const std::size_t offset);

    /// Performs a read operation on the device.
    /// \param[in] offset Offset in bytes relative to the start of the provided physical address.
    /// \param[in] size Size of the result buffer.
    /// \param[out] result Buffer where the result can be stored
    /// \throw std::logic_error On internal errors.
    /// \throw info::Error If an error occurred while requesting privileges.
    void read(std::size_t offset, std::size_t size, void * result);

    /// Performs a write operation on the device.
    /// \tparam T Type of data that is to be written.
    /// \param[in] offset Offset in bytes relative to the start of the provided physical address.
    /// \param[in] value Data that is to be written to the device.
    /// \throw std::logic_error On internal errors.
    /// \throw info::Error If an error occurred while requesting privileges.
    template <class T>
    void write(const std::size_t offset, const T & value);

    /// Performs a write operation on the device.
    /// \param[in] offset Offset in bytes relative to the start of the provided physical address.
    /// \param[in] size Size of the data buffer..
    /// \param[in] value Data that is to be written to the device.
    /// \throw std::logic_error On internal errors.
    /// \throw info::Error If an error occurred while requesting privileges.
    void write(std::size_t offset, std::size_t size, const void * value);

private:
    void getPrivileges();

    const MappedIoAddress m_base;
    bool m_has_privileges;
};

}
}
}

#include "MappedIoDevice-inl.h"

#endif //EINSTEIN_OS_IO_MAPPEDIODEVICE_H
