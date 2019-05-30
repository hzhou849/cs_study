// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#include "MappedIoAddress.h"
#include "Error.h"
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>



std::uintptr_t MakePort(const std::uintptr_t physical_address, const std::size_t size)
{
    std::uintptr_t result = mmap_device_io(size, physical_address);
    if (result == MAP_DEVICE_FAILED && errno == EPERM)
    {
       MappedIoAddress::requestIoPrivileges();
        result = mmap_device_io(size, physical_address);
    }
    if (result == MAP_DEVICE_FAILED)
    {
   //     throw einstein::os::info::Error("mmap_device_io", errno, __FILE__, __LINE__);
    }
    return result;
}



MappedIoAddress::MappedIoAddress(const std::uintptr_t physical_address, const std::size_t size) :
    m_port(MakePort(physical_address, size)),
    m_size(size)
{
}

MappedIoAddress::~MappedIoAddress()
{
    munmap_device_io(m_port, m_size);
}

void MappedIoAddress::requestIoPrivileges()
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

