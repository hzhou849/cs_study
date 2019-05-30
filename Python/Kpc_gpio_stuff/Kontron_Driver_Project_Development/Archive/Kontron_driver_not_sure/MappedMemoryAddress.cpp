// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#include "einstein/os/io/MappedMemoryAddress.h"
#include "einstein/os/info/Error.h"
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>

namespace
{

int MakeProtection(const einstein::os::io::DeviceAccess access)
{
    int flags = PROT_NOCACHE;
    switch (access)
    {
    case einstein::os::io::DeviceAccess::NONE:
        flags |= PROT_NONE; //SUPPRESS: Useless Assignment
        //REASON: kept for readability and completeness
        break;
    case einstein::os::io::DeviceAccess::READ:
        flags |= PROT_READ;
        break;
    case einstein::os::io::DeviceAccess::WRITE:
        flags |= PROT_WRITE;
        break;
    case einstein::os::io::DeviceAccess::READ_WRITE:
        flags |= PROT_READ | PROT_WRITE;
        break;
    default:
        throw std::runtime_error("invalid access");
    }
    return flags;
}

void * MakePort(const std::uintptr_t physical_address, const std::size_t size, const int protection)
{
    void * result = mmap_device_memory(nullptr, size, protection, 0, physical_address);
    if (result == MAP_FAILED && errno == EPERM)
    {
        einstein::os::io::MappedMemoryAddress::requestIoPrivileges();
        result = mmap_device_memory(nullptr, size, protection, 0, physical_address);
    }
    if (result == MAP_FAILED)
    {
        throw einstein::os::info::Error("mmap_device_memory", errno, __FILE__, __LINE__);
    }
    return result;
}

}

namespace einstein
{
namespace os
{
namespace io
{

MappedMemoryAddress::MappedMemoryAddress(const std::uintptr_t physical_address, const std::size_t size,
                                         const DeviceAccess access
                                        ) :
    m_port(MakePort(physical_address, size, MakeProtection(access))),
    m_size(size)
{

}

MappedMemoryAddress::~MappedMemoryAddress()
{
    munmap_device_memory(reinterpret_cast<void *>(m_port), m_size);
}

void MappedMemoryAddress::requestIoPrivileges()
{
    int result = procmgr_ability(0, PROCMGR_AID_IO | PROCMGR_AID_EOL);
    if (result != EOK)
    {
        throw einstein::os::info::Error("procmgr_ability", result, __FILE__, __LINE__);
    }

    result = ThreadCtl_r(_NTO_TCTL_IO, 0);
    if (result != EOK)
    {
        throw einstein::os::info::Error("ThreadCtl_r(_NTO_TCTL_IO)", result, __FILE__, __LINE__);
    }
}

}
}
}
