// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.



#include <cstddef>
#include <cstdint>


/// Helper class for MappedIoDevice. Should not be used directly.
/// \author Jan Tully
class MappedIoAddress
{
public:
    MappedIoAddress(const std::uintptr_t physical_address, const std::size_t size);
    ~MappedIoAddress();

    std::size_t getSize() const noexcept;
    std::uintptr_t getPort() const noexcept;

    static void requestIoPrivileges();

private:
    const std::uintptr_t m_port;
    const std::size_t m_size;
};



#include "MappedIoAddress-inl.h"


