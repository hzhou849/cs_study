// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#ifndef EINSTEIN_OS_IO_MAPPEDIODEVICE_INL_H
#define EINSTEIN_OS_IO_MAPPEDIODEVICE_INL_H

namespace einstein
{
namespace os
{
namespace io
{

template <DeviceAccess Access>
inline MappedIoDevice<Access>::MappedIoDevice(const std::uintptr_t physical_address, const std::size_t size) :
    m_base(physical_address, size),
    m_has_privileges(false)
{

}

template <DeviceAccess Access>
inline DeviceAccess MappedIoDevice<Access>::getAccess() const noexcept
{
    return Access;
}

template <DeviceAccess Access>
inline std::size_t MappedIoDevice<Access>::getSize() const noexcept
{
    return m_base.getSize();
}


template <DeviceAccess Access>
inline void MappedIoDevice<Access>::getPrivileges()
{
    if (!m_has_privileges)
    {
        MappedIoAddress::requestIoPrivileges();
        m_has_privileges = true;
    }
}


template <DeviceAccess Access>
inline void MappedIoDevice<Access>::read(std::size_t offset, std::size_t size, void * result
                                        ) //SUPPRESS: Function Too Long
//REASON: The function exceeds the limit by 5 lines. Shortening the function would impact readability.
{
    using AccessPermitted = typename std::conditional<
        Access == DeviceAccess::READ || Access == DeviceAccess::READ_WRITE, std::true_type, std::false_type>::type;
    static_assert(AccessPermitted::value, "no read access permitted");

    getPrivileges();

    std::uintptr_t address = m_base.getPort() + offset;

    auto advance = [&result, &address, &size](const std::size_t advance_by_bytes)
    {
        result = static_cast< std::uint8_t *>(result) + advance_by_bytes;
        address += advance_by_bytes;
        size -= advance_by_bytes;
    };

    {
        const std::size_t before = std::min(size, sizeof(std::uint32_t) - address % sizeof(std::uint32_t));
        switch (before)
        {
        case 0:
        case sizeof(std::uint32_t):
            break;
        case sizeof(std::uint16_t):
            *static_cast<std::uint16_t *>(result) = in16(address);
            advance(sizeof(std::uint16_t));
            break;
        case sizeof(std::uint8_t):
            *static_cast<std::uint8_t *>(result) = in8(address);
            advance(sizeof(std::uint8_t));
            break;
        case sizeof(std::uint8_t) + sizeof(std::uint16_t):
            *static_cast<std::uint8_t *>(result) = in8(address);
            advance(sizeof(std::uint8_t));
            *static_cast<std::uint16_t *>(result) = in16(address);
            advance(sizeof(std::uint16_t));
            break;
        default:
            throw std::logic_error("MappedIoDevice read invalid (before)");
        }
    }

    if (size >= sizeof(std::uint32_t))
    {
        const std::size_t full = size / sizeof(std::uint32_t);
        in32s(result, full, address);
        advance(full * sizeof(std::uint32_t));
    }

    {
        const std::size_t after = size;
        switch (after)
        {
        case 0:
            break;
        case sizeof(std::uint16_t):
            *static_cast<std::uint16_t *>(result) = in16(address);
            break;
        case sizeof(std::uint8_t):
            *static_cast<std::uint8_t *>(result) = in8(address);
            break;
        case sizeof(std::uint16_t) + sizeof(std::uint8_t):
            *static_cast<std::uint16_t *>(result) = in16(address);
            advance(sizeof(std::uint16_t));
            *static_cast<std::uint8_t *>(result) = in8(address);
            break;
        default:
            throw std::logic_error("MappedIoDevice read invalid (after)");
        }
    }
}

template <DeviceAccess Access>
template <class T>
inline void MappedIoDevice<Access>::read(const std::size_t offset, T * result)
{
    read(offset, sizeof(T), result);
}

template <DeviceAccess Access>
template <class T>
inline T MappedIoDevice<Access>::read(const std::size_t offset)
{
    T return_value = T();
    read(offset, sizeof(T), &return_value);
    return return_value;
}

template <DeviceAccess Access>
inline void MappedIoDevice<Access>::write(std::size_t offset, std::size_t size, const void * value
                                         ) //SUPPRESS: Function Too Long
//REASON: The function exceeds the limit by 4 lines. Shortening the function would impact readability.
{
    using AccessPermitted = typename std::conditional<
        Access == DeviceAccess::WRITE || Access == DeviceAccess::READ_WRITE, std::true_type, std::false_type>::type;
    static_assert(AccessPermitted::value, "no write access permitted");

    getPrivileges();

    std::uintptr_t address = m_base.getPort() + offset;

    auto advance = [&value, &address, &size](const std::size_t advance_by_bytes)
    {
        value = static_cast<const std::uint8_t *>(value) + advance_by_bytes;
        address += advance_by_bytes;
        size -= advance_by_bytes;
    };

    {
        const std::size_t before = std::min(size, sizeof(std::uint32_t) - address % sizeof(std::uint32_t));
        switch (before)
        {
        case 0:
        case sizeof(std::uint32_t):
            break;
        case sizeof(std::uint16_t):
            out16(address, *static_cast<const std::uint16_t *>(value));
            advance(sizeof(std::uint16_t));
            break;
        case sizeof(std::uint8_t):
            out8(address, *static_cast<const std::uint8_t *>(value));
            advance(sizeof(std::uint8_t));
            break;
        case sizeof(std::uint8_t) + sizeof(std::uint16_t):
            out8(address, *static_cast<const std::uint8_t *>(value));
            advance(sizeof(std::uint8_t));
            out16(address, *static_cast<const std::uint16_t *>(value));
            advance(sizeof(std::uint16_t));
            break;
        default:
            throw std::logic_error("MappedIoDevice write invalid (before)");
        }
    }

    if (size >= sizeof(std::uint32_t))
    {
        const std::size_t full = size / sizeof(std::uint32_t);
        out32s(value, full, address);
        advance(full * sizeof(std::uint32_t));
    }

    {
        const std::size_t after = size;
        switch (after)
        {
        case 0:
            break;
        case sizeof(std::uint16_t):
            out16(address, *static_cast<const std::uint16_t *>(value));
            break;
        case sizeof(std::uint8_t):
            out8(address, *static_cast<const std::uint8_t *>(value));
            break;
        case sizeof(std::uint16_t) + sizeof(std::uint8_t):
            out16(address, *static_cast<const std::uint16_t *>(value));
            advance(sizeof(std::uint16_t));
            out8(address, *static_cast<const std::uint8_t *>(value));
            break;
        default:
            throw std::logic_error("MappedIoDevice write invalid (after)");
        }
    }
}

template <DeviceAccess Access>
template <class T>
inline void MappedIoDevice<Access>::write(const std::size_t offset, const T & value)
{
    write(offset, sizeof(T), &value);
}

}
}
}

#endif //EINSTEIN_OS_IO_MAPPEDIODEVICE_INL_H
