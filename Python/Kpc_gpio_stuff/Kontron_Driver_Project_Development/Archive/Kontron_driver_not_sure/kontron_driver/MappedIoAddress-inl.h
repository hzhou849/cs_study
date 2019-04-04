// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#ifndef EINSTEIN_OS_IO_MAPPEDIOADDRESS_INL_H
#define EINSTEIN_OS_IO_MAPPEDIOADDRESS_INL_H

namespace einstein
{
namespace os
{
namespace io
{

inline std::size_t MappedIoAddress::getSize() const noexcept
{
    return m_size;
}

inline std::uintptr_t MappedIoAddress::getPort() const noexcept
{
    return m_port;
}

}
}
}

#endif //EINSTEIN_OS_IO_MAPPEDIOADDRESS_INL_H
