// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.



inline std::size_t MappedIoAddress::getSize() const noexcept
{
    return m_size;
}

inline std::uintptr_t MappedIoAddress::getPort() const noexcept
{
    return m_port;
}


